#include "../header/serial.h"
#include <stdio.h>
#include <string.h>
#include <windows.h>

static HANDLE hSerial = NULL;

static float fuel_inicio_volta = -1.0f;
static int   ultima_volta      = -1;
static float fuel_por_volta    = 0.0f;

int serial_open(const char *porta) {
    hSerial = CreateFileA(
        porta,
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Erro ao abrir %s\n", porta);
        return 0;
    }

    DCB dcb = {0};
    dcb.DCBlength = sizeof(DCB);
    GetCommState(hSerial, &dcb);
    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity   = NOPARITY;
    SetCommState(hSerial, &dcb);

    COMMTIMEOUTS timeouts = {0};
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    /* Reseta estado de telemetria ao abrir nova sessao */
    fuel_inicio_volta = -1.0f;
    ultima_volta      = -1;
    fuel_por_volta    = 0.0f;

    printf("Porta %s aberta com sucesso!\n", porta);
    return 1;
}

void serial_close(void) {
    if (hSerial && hSerial != INVALID_HANDLE_VALUE) {
        CloseHandle(hSerial);
        hSerial = NULL;
        printf("Porta serial fechada.\n");
    }
}

void serial_send_rpm(int rpm) {
    if (!hSerial || hSerial == INVALID_HANDLE_VALUE) return;

    char  buffer[32];
    DWORD bytes_escritos;
    DWORD len;

    len = (DWORD)snprintf(buffer, sizeof(buffer), "RPM:%d\n", rpm);

    if (!WriteFile(hSerial, buffer, len, &bytes_escritos, NULL) ||
        bytes_escritos != len) {
        printf("Erro ao enviar RPM.\n");
    }
}

/* Lista portas COM via registro do sistema — instantaneo, sem tentar abrir */
void serial_listar_portas(void) {
    printf("\nPortas COM disponiveis:\n");

    HKEY hKey;
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                      "HARDWARE\\DEVICEMAP\\SERIALCOMM",
                      0, KEY_READ, &hKey) != ERROR_SUCCESS) {
        printf("  Nenhuma porta encontrada.\n");
        return;
    }

    char  nome[256];
    char  valor[256];
    DWORD i = 0;
    DWORD nomeLen, valorLen, tipo;
    int   encontrou = 0;

    while (1) {
        nomeLen  = sizeof(nome);
        valorLen = sizeof(valor);

        LONG ret = RegEnumValueA(hKey, i++,
                                 nome,  &nomeLen,
                                 NULL,  &tipo,
                                 (BYTE *)valor, &valorLen);

        if (ret == ERROR_NO_MORE_ITEMS) break;
        if (ret != ERROR_SUCCESS)       continue;

        /* valor = "COM3", nome = "\Device\ProlificSerial0" etc. */
        printf("  %-6s  (%s)\n", valor, nome);
        encontrou = 1;
    }

    RegCloseKey(hKey);

    if (!encontrou) printf("  Nenhuma porta encontrada.\n");
}

void serial_escolher_porta(char *porta_out, size_t porta_out_len) {
    serial_listar_portas();

    int num = 0;
    int valido = 0;

    while (!valido) {
        printf("\nDigite o numero da porta (ex: 3 para COM3, 0 para cancelar): ");

        if (scanf("%d", &num) != 1) {
            /* limpa buffer em caso de entrada invalida */
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        if (num == 0) {
            porta_out[0] = '\0';
            printf("Cancelado.\n");
            return;
        }

        if (num >= 1 && num <= 256) {
            valido = 1;
        } else {
            printf("Numero fora do intervalo (1-256). Tente novamente.\n");
        }
    }

    snprintf(porta_out, porta_out_len, "COM%d", num);
    printf("Porta selecionada: %s\n", porta_out);
}

static void calcular_fuel_por_volta(SPageFilePhysics *ph, SPageFileGraphic *gr) {
    int volta_atual = gr->completedLaps;

    /* primeira leitura */
    if (ultima_volta == -1) {
        ultima_volta      = volta_atual;
        fuel_inicio_volta = ph->fuel;
        return;
    }

    /* detectou nova volta */
    if (volta_atual != ultima_volta) {
        float consumo = fuel_inicio_volta - ph->fuel;

        /* so atualiza se o consumo for positivo e realista */
        if (consumo > 0.0f && consumo < 10.0f) {
            fuel_por_volta = consumo;
        }

        ultima_volta      = volta_atual;
        fuel_inicio_volta = ph->fuel;
    }
}

float serial_get_fuel_por_volta(void) {
    return fuel_por_volta;
}

void serial_send_telemetry(SPageFilePhysics *ph, SPageFileStatic *st, SPageFileGraphic *gr) {
    if (!hSerial || hSerial == INVALID_HANDLE_VALUE) return;

    calcular_fuel_por_volta(ph, gr);

    /* Converte wide strings de tempo para multibyte */
    char cur_time[32] = {0};
    char best_time[32] = {0};
    WideCharToMultiByte(CP_UTF8, 0,
                        gr->currentTime, -1,
                        cur_time, sizeof(cur_time),
                        NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0,
                        gr->bestTime, -1,
                        best_time, sizeof(best_time),
                        NULL, NULL);

    char  buffer[2048];
    DWORD bytes_escritos;
    DWORD len;

    len = (DWORD)snprintf(buffer, sizeof(buffer),
        "MOD:DASH|"
        "POS:%d|LAP:%d|NLAP:%d|"
        "FUEL:%.1f|MXF:%.1f|FPV:%.2f|"
        "RPM:%d|MXR:%d|"
        "GER:%d|"
        "SPD:%.1f|"
        "BRK:%d|"
        "CTIM:%s|BTIM:%s|"
        "TT0:%.1f|TT1:%.1f|TT2:%.1f|TT3:%.1f|"
        "TW0:%.1f|TW1:%.1f|TW2:%.1f|TW3:%.1f|"
        "ABS:%.2f|TC:%.2f\n",

        gr->position, gr->completedLaps, gr->numberOfLaps,
        ph->fuel, st->maxFuel, fuel_por_volta,
        ph->rpms, st->maxRpm,
        ph->gear,
        ph->speedKmh,
        (int)(ph->brake * 100),
        cur_time, best_time,
        ph->tyreCoreTemperature[0], ph->tyreCoreTemperature[1],
        ph->tyreCoreTemperature[2], ph->tyreCoreTemperature[3],
        ph->tyreWear[0], ph->tyreWear[1],
        ph->tyreWear[2], ph->tyreWear[3],
        ph->abs, ph->tc
    );

    if (!WriteFile(hSerial, buffer, len, &bytes_escritos, NULL) ||
        bytes_escritos != len) {
        printf("Erro ao enviar telemetria.\n");
    }
}
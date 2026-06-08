#include "../header/shift_light.h"
#include "../../serial/header/serial.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

void shiftlight_run(AcSharedMemory *ac) {
    char porta[16] = {0};

    serial_escolher_porta(porta, sizeof(porta));

    if (porta[0] == '\0') return; /* usuario cancelou */

    if (!serial_open(porta)) {
        printf("Erro ao abrir a porta serial!\n");
        system("pause");
        return;
    }

    Sleep(2000); 
    printf("Enviando dados para o ESP32...\n");
    printf("Pressione qualquer tecla para parar.\n\n");
    Sleep(1000);

    while (!kbhit()) {
        /*
        
        printf("=== SHIFTLIGHT ESP32 ===\n");
        printf("Porta  : %s\n", porta);
        printf("RPM    : %d / %d\n", ac->ph->rpms, ac->st->maxRpm);
        printf("Marcha : ");

        switch (ac->ph->gear) {
            case 0:  printf("R\n"); break;
            case 1:  printf("N\n"); break;
            default: printf("%d\n", ac->ph->gear - 1); break;
        }
        */

        system("cls");
        printf("\nPressione qualquer tecla para parar.\n");

        serial_send_telemetry(ac->ph, ac->st, ac->gr);

        Sleep(50);
    }

    getch();
    serial_close();
}
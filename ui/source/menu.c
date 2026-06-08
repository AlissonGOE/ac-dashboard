#include "../header/menu.h"
#include <stdio.h>
#include <conio.h>
#include <windows.h>

void menu(AcSharedMemory *ac) {
    int opcao = 0;

    while (opcao != 10) {
        system("cls");
        printf("=======MENU PRINCIPAL=======\n");
        printf("[1]: Telemetrias do Motor\n");
        printf("[2]: Telemetrias dos Pneus\n");
        printf("[3]: Telemetrias da Suspensao\n");
        printf("[4]: Telemetrias do Veiculo\n");
        printf("[5]: Telemetrias da Carroceria\n");
        printf("[6]: Telemetrias da Sessao\n");
        printf("[7]: Telemetrias Auxiliares\n");
        printf("[8]: Shiftlight ESP32\n");
        printf("[9]: Dashboard ESP32\n");
        printf("[10]: Fechar Programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                while (!kbhit()) {
                    system("cls");
                    motor_print(ac->ph, ac->st);
                    printf("\nPressione qualquer tecla para voltar ao menu...\n");
                    Sleep(16);
                }
                getch();
                break;

            case 2:
                while (!kbhit()) {
                    system("cls");
                    pneus_print(ac->ph, ac->st);
                    printf("\nPressione qualquer tecla para voltar ao menu...\n");
                    Sleep(16);
                }
                getch();
                break;

            case 3:
                while (!kbhit()) {
                    system("cls");
                    suspensao_print(ac->ph, ac->st);
                    printf("\nPressione qualquer tecla para voltar ao menu...\n");
                    Sleep(16);
                }
                getch();
                break;

            case 4:
                while (!kbhit()) {
                    system("cls");
                    veiculo_print(ac->ph, ac->st);
                    printf("\nPressione qualquer tecla para voltar ao menu...\n");
                    Sleep(16);
                }
                getch();
                break;

            case 5:
                while (!kbhit()) {
                    system("cls");
                    carroceria_print(ac->ph, ac->st);
                    printf("\nPressione qualquer tecla para voltar ao menu...\n");
                    Sleep(16);
                }
                getch();
                break;

            case 6:
                while (!kbhit()) {
                    system("cls");
                    sessao_print(ac->ph, ac->st, ac->gr);
                    printf("\nPressione qualquer tecla para voltar ao menu...\n");
                    Sleep(1000);
                }
                getch();
                break;

            case 7:
                while (!kbhit()) {
                    system("cls");
                    auxiliares_print(ac->ph, ac->st);
                    printf("\nPressione qualquer tecla para voltar ao menu...\n");
                    Sleep(16);
                }
                getch();
                break;

            case 8:
                shiftlight_run(ac);
                system("pause");
                break;

            case 9:
                serial_send_telemetry(ac->ph, ac->st, ac->gr);
                system("pause");
                break;

            case 10:
                printf("Encerrando Programa...\n");
                Sleep(1000);
                break;

            default:
                printf("Opcao Invalida!\n");
                system("pause");
                break;
        }
    }
}
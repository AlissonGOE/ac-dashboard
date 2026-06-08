#include "../header/pneus.h"
#include <stdio.h>

void pneus_print(SPageFilePhysics *ph, SPageFileStatic *st){
    printf("=== PNEUS ===\n");
    printf("           FL      FR      RL      RR\n");
    printf("Pressao  : %.1f   %.1f   %.1f   %.1f PSI\n", ph->wheelsPressure[0], ph->wheelsPressure[1], ph->wheelsPressure[2], ph->wheelsPressure[3]);
    printf("Temp     : %.1f   %.1f   %.1f   %.1f C\n",   ph->tyreCoreTemperature[0], ph->tyreCoreTemperature[1], ph->tyreCoreTemperature[2], ph->tyreCoreTemperature[3]);
    printf("Desgaste : %.1f   %.1f   %.1f   %.1f\n",     ph->tyreWear[0], ph->tyreWear[1], ph->tyreWear[2], ph->tyreWear[3]);
    printf("Sujeira  : %.1f   %.1f   %.1f   %.1f\n",     ph->tyreDirtyLevel[0], ph->tyreDirtyLevel[1], ph->tyreDirtyLevel[2], ph->tyreDirtyLevel[3]);
    printf("Slip     : %.2f   %.2f   %.2f   %.2f\n",     ph->wheelSlip[0], ph->wheelSlip[1], ph->wheelSlip[2], ph->wheelSlip[3]);
    printf("Carga    : %.1f   %.1f   %.1f   %.1f\n",     ph->wheelLoad[0], ph->wheelLoad[1], ph->wheelLoad[2], ph->wheelLoad[3]);
    printf("Camber   : %.2f   %.2f   %.2f   %.2f\n",     ph->camberRAD[0], ph->camberRAD[1], ph->camberRAD[2], ph->camberRAD[3]);
}

void pneus_send(SPageFilePhysics *ph){
    printf("\nPNEUS_SERIAL");
}
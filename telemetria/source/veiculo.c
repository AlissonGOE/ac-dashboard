#include "../header/veiculo.h"
#include <stdio.h>

void veiculo_print(SPageFilePhysics *ph, SPageFileStatic *st){
    printf("=== VEICULO ===\n");
    printf("Carro        : %ls\n",  st->carModel);
    printf("Pista        : %ls\n",  st->track);
    printf("RPM Max      : %d\n",   st->maxRpm);
    printf("Combustivel  : %.1f L\n", st->maxFuel);
    printf("Potencia Max : %.1f\n", st->maxPower);
    printf("Torque Max   : %.1f\n", st->maxTorque);
    printf("Temp Ar      : %.1f C\n", st->airTemp);
    printf("Temp Pista   : %.1f C\n", st->roadTemp);
} 

void veiculo_send(SPageFilePhysics *ph){
    printf("\nVEICULO_SERIAL");
}
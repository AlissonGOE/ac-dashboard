#include "../header/carroceria.h"
#include <stdio.h>


void carroceria_print(SPageFilePhysics *ph, SPageFileStatic *st){
    printf("=== CARROCERIA ===\n");
    printf("Dano Frente  : %.2f\n", ph->carDamage[0]);
    printf("Dano Traseira: %.2f\n", ph->carDamage[1]);
    printf("Dano Esq     : %.2f\n", ph->carDamage[2]);
    printf("Dano Dir     : %.2f\n", ph->carDamage[3]);
    printf("Dano Centro  : %.2f\n", ph->carDamage[4]);
    printf("Roll         : %.2f\n", ph->roll);
    printf("Pitch        : %.2f\n", ph->pitch);
    printf("Heading      : %.2f\n", ph->heading);
    printf("G Force X    : %.2f\n", ph->accG[0]);
    printf("G Force Y    : %.2f\n", ph->accG[1]);
    printf("G Force Z    : %.2f\n", ph->accG[2]);
} 

void carroceria_send(SPageFilePhysics *ph){
    printf("\nCARROCERIA_SERIAL");
}
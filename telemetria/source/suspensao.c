#include "../header/suspensao.h"
#include <stdio.h>


void suspensao_print(SPageFilePhysics *ph, SPageFileStatic *st){
    printf("=== SUSPENSAO ===\n");
    printf("              FL      FR      RL      RR\n");
    printf("Travel      : %.2f   %.2f   %.2f   %.2f\n", ph->suspensionTravel[0], ph->suspensionTravel[1], ph->suspensionTravel[2], ph->suspensionTravel[3]);
    printf("Max Travel  : %.2f   %.2f   %.2f   %.2f\n", st->suspensionMaxTravel[0], st->suspensionMaxTravel[1], st->suspensionMaxTravel[2], st->suspensionMaxTravel[3]);
    printf("Ride Height : %.2f (frente)  %.2f (traseira)\n", ph->rideHeight[0], ph->rideHeight[1]);
    printf("CG Height   : %.2f\n", ph->cgHeight);
} 

void suspensao_send(SPageFilePhysics *ph){
    printf("\n SUSPENSAO_SERIAL");
}
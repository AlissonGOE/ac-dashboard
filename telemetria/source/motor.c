#include "../header/motor.h"
#include <stdio.h>

void motor_print(SPageFilePhysics *ph, SPageFileStatic *st){
    
    printf("=== MOTOR ===\n");
    printf("Carro       : %ls\n",  st->carModel);
    printf("RPM         : %d / %d\n", ph->rpms, st->maxRpm);
    printf("Velocidade  : %.1f km/h\n", ph->speedKmh);
    
    switch (ph->gear)
    {
    case 0: printf("Marcha      : R\n");    break;
    case 1: printf("Marcha      : N\n");    break;
    default:    printf("Marcha      : %d\n", ph->gear -1);    break;
    }

    printf("Acelerador  : %.0f%%\n", ph->gas   * 100);
    printf("Freio       : %.0f%%\n", ph->brake * 100);
    printf("Turbo       : %.2f\n",  ph->turboBoost);
    printf("TC          : %.2f\n",  ph->tc);
    printf("ABS         : %.2f\n",  ph->abs);
    printf("Pit Limiter : %d\n",    ph->pitLimiterOn);
    printf("Cambio Auto : %d\n",    ph->autoShifterOn);
    printf("DRS         : %.0f\n",  ph->drs);
    printf("KERS Carga  : %.2f\n",  ph->kersCharge);
    printf("KERS Input  : %.2f\n",  ph->kersInput);
}

void motor_send(SPageFilePhysics *ph){
    printf("\nMOTOR_SERIAL");
}
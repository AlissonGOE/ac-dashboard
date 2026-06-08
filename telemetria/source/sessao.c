#include "../header/sessao.h"
#include <stdio.h>

void sessao_print(SPageFilePhysics *ph, SPageFileStatic *st, SPageFileGraphic *gr){
    printf("=== SESSAO ===\n");
    printf("Combustivel  : %.1f / %.1f L\n",   ph->fuel, st->maxFuel);
    printf("Posicao      : %d\n",               gr->position);
    printf("Voltas       : %d / %d\n",          gr->completedLaps, gr->numberOfLaps);
    printf("Tempo Atual  : %ls\n",              gr->currentTime);
    printf("Ultima Volta : %ls\n",              gr->lastTime);
    printf("Melhor Tempo : %ls\n",              gr->bestTime);
    printf("Setor Atual  : %d\n",               gr->currentSectorIndex + 1);
    printf("Ultimo Setor : %d ms\n",            gr->lastSectorTime);
    printf("Tempo Sessao : %.1f s\n",           gr->sessionTimeLeft);
    printf("No Pit       : %s\n",               gr->isInPit     ? "Sim" : "Nao");
    printf("Pit Lane     : %s\n",               gr->isInPitLane ? "Sim" : "Nao");
    printf("Penalidade   : %.1f s\n",           gr->penaltyTime);
}

void sessao_send(SPageFilePhysics *ph){
    printf("\nSESSAO_PRINT");
}
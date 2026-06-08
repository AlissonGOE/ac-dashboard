#include "../header/shared_memory.h"
#include <stdio.h>

int shared_memory_open(AcSharedMemory *ac){

    ac->hPhysics = OpenFileMapping(FILE_MAP_READ, FALSE, "Local\\acpmf_physics");
    ac->hStatic  = OpenFileMapping(FILE_MAP_READ, FALSE, "Local\\acpmf_static");
    ac->hGraphic = OpenFileMapping(FILE_MAP_READ, FALSE, "Local\\acpmf_graphics");

    if (ac->hPhysics == NULL || ac->hStatic == NULL || ac->hGraphic == NULL){
        printf("AC nao esta rodando!\n");
        system("pause");
        return 0;
    }

    ac->ph = (SPageFilePhysics*)MapViewOfFile(ac->hPhysics, FILE_MAP_READ, 0, 0, 0);
    ac->st = (SPageFileStatic*) MapViewOfFile(ac->hStatic,  FILE_MAP_READ, 0, 0, 0);
    ac->gr = (SPageFileGraphic*)MapViewOfFile(ac->hGraphic, FILE_MAP_READ, 0, 0, 0);

    if (ac->ph == NULL || ac->st == NULL || ac->gr == NULL){
        printf("Erro ao mapear memoria!\n");
        system("pause");
        shared_memory_close(ac);
        return 0;
    }

    return 1;
}

void shared_memory_close(AcSharedMemory *ac){

    if (ac->ph) UnmapViewOfFile(ac->ph);
    if (ac->st) UnmapViewOfFile(ac->st);
    if (ac->gr) UnmapViewOfFile(ac->gr);

    if (ac->hPhysics) CloseHandle(ac->hPhysics);
    if (ac->hStatic)  CloseHandle(ac->hStatic);
    if (ac->hGraphic) CloseHandle(ac->hGraphic);
}
#pragma once
#include <windows.h>
#include "../../ac_types.h"

typedef struct {
    HANDLE hPhysics;
    HANDLE hStatic;
    HANDLE hGraphic;

    SPageFilePhysics *ph;
    SPageFileStatic  *st;
    SPageFileGraphic *gr;
} AcSharedMemory;

int shared_memory_open(AcSharedMemory *ac);

void shared_memory_close(AcSharedMemory *ac);

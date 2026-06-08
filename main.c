#include <windows.h>
#include <stdio.h>
#include "ac_types.h"
#include "shared_memory/header/shared_memory.h"
#include "ui/header/menu.h"


int main(void){

    AcSharedMemory ac = {0};

    if (!shared_memory_open(&ac)){
        system("pause");
        return 1;
    }
    
    menu(&ac);
    
    shared_memory_close(&ac);
    Sleep(100);
    printf("Encerrando...\n");
    system("pause");
    return 0;
}
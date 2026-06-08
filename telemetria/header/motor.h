#pragma once
#include "../../ac_types.h"


void motor_print(SPageFilePhysics *ph, SPageFileStatic *st); // Função para imprimir os dados do motor do veiculo.

void motor_send(SPageFilePhysics *ph); // Função para enviar os dados do motor via serial para o ESP32.
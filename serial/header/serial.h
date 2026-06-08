#pragma once
#include <windows.h>
#include <stddef.h>
#include "../../ac_types.h"

int  serial_open(const char *porta);
void serial_close(void);
void serial_send_rpm(int rpm);
void serial_send_telemetry(SPageFilePhysics *ph, SPageFileStatic *st, SPageFileGraphic *gr);
void serial_listar_portas(void);
void serial_escolher_porta(char *porta_out, size_t porta_out_len);
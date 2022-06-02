#ifndef _RELOGIO_ALIMENTADOR_H_
#define _RELOGIO_ALIMENTADOR_H_

#include "Arduino_FreeRTOS.h"
#include "Arduino.h"
#include <time.h>

extern struct tm tm_relogio;

void task_relogio(void *);

void definir_horario(int,int,int);

void definir_data(int,int,int);

bool passou_do_horario(int,int,int);
#endif

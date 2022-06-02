#ifndef _ULTRASSOM_ALIMENTADOR_H_
#define _ULTRASSOM_ALIMENTADOR_H_

#include "Arduino_FreeRTOS.h"
#include <Arduino.h>

#define ECHO_ULTRASSOM 40
#define TRIG_ULTRASSOM 42

#define DISTANCIA_TAMPA 18
 
void inicializar_ultrassom(void);

uint16_t distancia_ultrassom(void);

bool verificar_tampa_despejando(void);
#endif

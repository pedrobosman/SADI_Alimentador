#ifndef _LDR_ALIMENTADOR_H_
#define _LDR_ALIMENTADOR_H_

#include "Arduino_FreeRTOS.h"
#include <Arduino.h>

#define GPIO_LDR A0

void inicializar_ldr(void);

double luminosidade_ambiente(void);
#endif

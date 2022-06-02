#ifndef _LED_ALIMENTADOR_H_
#define _LED_ALIMENTADOR_H_

#include "Arduino_FreeRTOS.h"
#include <Arduino.h>

#define GPIO_LUZ 3
 
void inicializar_luz(void);

void acender_luz(void);

void desligar_luz(void);

void acender_luz_como_dimer(int);
#endif

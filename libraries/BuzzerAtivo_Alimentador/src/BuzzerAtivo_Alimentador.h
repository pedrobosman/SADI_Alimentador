#ifndef _BUZZERATIVO_ALIMENTADOR_H_
#define _BUZZERATIVO_ALIMENTADOR_H_

#include "Arduino_FreeRTOS.h"
#include <Arduino.h>

#define GPIO_BUZZER_ATIVO 32

extern bool buzzer_ativo_status; 

void inicializar_buzzer_ativo(void);

void emitir_som_buzzer_ativo(void);

void desligar_buzzer_ativo(void);

void n_beeps_aviso(int,int,int);
#endif

#ifndef _MOTOR_ALIMENTADOR_H_
#define _MOTOR_ALIMENTADOR_H_

#include <Servo.h>

#define GPIO_MOTOR          7  //PWM

#define ANGULO_FECHAR       0
#define ANGULO_DESPEJAR     180  

extern Servo motor;

void inicializar_motor(void);

void despejar_alimento(void);

void fechar_recipiente(void);


#endif

#include "Motor_Alimentador.h"

Servo motor;

void inicializar_motor(){
  motor.attach(GPIO_MOTOR);
}

void despejar_alimento(){
  motor.write(0);
}

void fechar_recipiente(){
  motor.write(180);
}

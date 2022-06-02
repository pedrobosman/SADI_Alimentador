#include "Motor_Alimentador.h"

Servo motor;

void inicializar_motor(void){
  motor.attach(GPIO_MOTOR);
  fechar_recipiente();
}


void despejar_alimento(void){
  motor.write(ANGULO_DESPEJAR);
}

void fechar_recipiente(void){
  motor.write(ANGULO_FECHAR);
}

#include "Ldr_Alimentador.h"


void inicializar_ldr(void){
  pinMode(GPIO_LDR,INPUT);
}

double luminosidade_ambiente(void){
  int valor_ad = analogRead(GPIO_LDR);
  return (5*valor_ad)/(double)1023;
}

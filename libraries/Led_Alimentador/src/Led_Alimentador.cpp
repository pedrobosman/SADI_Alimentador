#include "Led_Alimentador.h"

bool led_status = false; 

void inicializar_luz(void){
  pinMode(GPIO_LUZ, OUTPUT);
  digitalWrite(GPIO_LUZ, LOW);
  led_status = false;
}

void acender_luz(void){
  digitalWrite(GPIO_LUZ, HIGH);
  led_status = true;
}

void desligar_luz(void){
  digitalWrite(GPIO_LUZ, LOW);
  led_status = false;
}

void acender_luz_como_dimer(int porcentagem){
  led_status = true;
  if(porcentagem > 100){
    analogWrite(GPIO_LUZ, 255); 
  }else if(porcentagem <= 0){
    analogWrite(GPIO_LUZ, 0); 
  }else{
    int valor_saida = 0;
    valor_saida = map(porcentagem, 0,100,0,255);
    analogWrite(GPIO_LUZ, valor_saida); 
  }  
}

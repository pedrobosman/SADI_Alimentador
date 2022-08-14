#include "Ultrassom_Alimentador.h"


void inicializar_ultrassom(void) {
  pinMode(TRIG_ULTRASSOM, OUTPUT);
  pinMode(ECHO_ULTRASSOM, INPUT);
}

uint16_t distancia_ultrassom(void)
{
  digitalWrite(TRIG_ULTRASSOM, LOW);
  vTaskDelay(2 / portTICK_PERIOD_MS );
  digitalWrite(TRIG_ULTRASSOM, HIGH);
  vTaskDelay(10 / portTICK_PERIOD_MS );
  digitalWrite(TRIG_ULTRASSOM, LOW);

  return pulseIn(ECHO_ULTRASSOM, HIGH)/58;
}

bool verificar_tampa_despejando(void){
  int distancia_tampa = distancia_ultrassom();
  
  if(distancia_tampa >= 50 || distancia_tampa <= 0){
    return true; //Deu erro no sensor ultrassonico, mas não é para ficar tentando
                 //Despejar comida. Tratar Erro depois.
  }
  
  if(distancia_tampa >= (DISTANCIA_TAMPA + 5)){
    return false;
  }
  else
  {
    return true;
  }
}

#include "BuzzerAtivo_Alimentador.h"

bool buzzer_ativo_status = false; 

void inicializar_buzzer_ativo(void){
  pinMode(GPIO_BUZZER_ATIVO, OUTPUT);
  digitalWrite(GPIO_BUZZER_ATIVO, LOW);
  buzzer_ativo_status = false;
}

void emitir_som_buzzer_ativo(void){
  digitalWrite(GPIO_BUZZER_ATIVO, HIGH);
  buzzer_ativo_status = true;
}

void desligar_buzzer_ativo(void){
  digitalWrite(GPIO_BUZZER_ATIVO, LOW);
  buzzer_ativo_status = false;
}

void n_beeps_aviso(int num_beeps,int tempo_beep, int tempo_entre_beep_ms){
  for (size_t i = 1; i <= num_beeps; i++)
  {
    emitir_som_buzzer_ativo();
    vTaskDelay(tempo_beep / portTICK_PERIOD_MS);
    desligar_buzzer_ativo();
    vTaskDelay(tempo_entre_beep_ms / portTICK_PERIOD_MS);
  } 
  
}

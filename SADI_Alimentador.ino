#include "Arduino_FreeRTOS.h"
#include "task.h"


#include "tasks_commom.h"
#include "Motor_Alimentador.h"
#include "Ultrassom_Alimentador.h"
#include "Led_Alimentador.h"
#include "Ldr_Alimentador.h"
#include "Relogio_Alimentador.h"
//Tasks
TaskHandle_t        ledTaskH;

void setup() {
  inicializar_motor();
  inicializar_ultrassom();
  inicializar_luz();
  inicializar_ldr();
  Serial.begin(9600);

  xTaskCreate(task_relogio,            //Funcao
              "task_relogio",          //Nome
              128,                //Pilha
              NULL,               //Parametro
              5,                  //Prioridade
              NULL);

  xTaskCreate(ledTask,            //Funcao
              "ledTask",          //Nome
              128,                //Pilha
              NULL,               //Parametro
              2,                  //Prioridade
              &ledTaskH);

}

void loop() {
  // Nada é feito aqui, Todas as funções são feitas em Tasks
}


void ledTask(void *arg) {
  definir_horario(19, 31, 00);
  Serial.println("Comecei");
  while (true) {
    if(passou_do_horario(19, 31, 5)){
      despejar_alimento();
      vTaskDelay(3000 / portTICK_PERIOD_MS);
      fechar_recipiente();
      vTaskDelete(NULL);
    }    
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

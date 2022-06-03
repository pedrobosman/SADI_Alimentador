#include "Arduino_FreeRTOS.h"
#include "task.h"


#include "tasks_commom.h"
#include "Motor_Alimentador.h"
#include "Ultrassom_Alimentador.h"
#include "Led_Alimentador.h"
#include "Ldr_Alimentador.h"
#include "Relogio_Alimentador.h"
#include "Alimentador.h"

//Tasks
//TaskHandle_t        ledTaskH;
Alimentar dar_alimento[20];

void setup() {
  Serial.begin(9600);
  inicializar_motor();
  inicializar_ultrassom();
  inicializar_luz();
  inicializar_ldr();

  xTaskCreate(task_relogio, "task_relogio", TASK_STACK_SIZE_RELOGIO, NULL, TASK_PRIORITY_RELOGIO, NULL);

  xTaskCreate(task_serial, "task_serial", TASK_STACK_SIZE_SERIAL, NULL, TASK_PRIORITY_SERIAL, NULL);

  //xTaskCreate(alimentador, "task_alimentador", TASK_STACK_SIZE_ALIMENTADOR, NULL, TASK_PRIORITY_ALIMENTADOR, NULL);
}

void loop() {
  // Nada é feito aqui, Todas as funções são feitas em Tasks
}


void task_serial(void *arg) {
  Serial.println("Comecei");
  while (true) {
    
    if (Serial.available() > 0) {
      String receber_json = Serial.readString();
      dar_alimento[0] = Json_para_alimentar(receber_json);
      Serial.println(dar_alimento[0].hora);
    }
    
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

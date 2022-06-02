#include "Arduino_FreeRTOS.h"
#include "task.h"


#include "tasks_commom.h" 
#include "Motor_Alimentador.h"
#include "Ultrassom_Alimentador.h"
  
//Tasks
TaskHandle_t        ledTaskH;
TaskHandle_t        sineTaskH;


void setup() {
    inicializar_motor();
    inicializar_ultrassom();
    Serial.begin(9600);
    
    xTaskCreate(ledTask,            //Funcao
                "ledTask",          //Nome
                128,                //Pilha
                NULL,               //Parametro
                5,                  //Prioridade
                &ledTaskH);
     
}
 
void loop() {
    // Nada é feito aqui, Todas as funções são feitas em Tasks
}
 

void ledTask(void *arg) {
    despejar_alimento();
    
    while(true) {
      vTaskDelay(500/portTICK_PERIOD_MS );
      if(verificar_tampa_despejando() == true){
        fechar_recipiente();
      }
    }
}
 

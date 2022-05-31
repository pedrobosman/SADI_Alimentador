#include "Arduino_FreeRTOS.h"
#include "task.h"
//#include "semphr.h"

#include "tasks_commom.h" 
#include "Motor_Alimentador.h"

  
//Tasks
TaskHandle_t        ledTaskH;
TaskHandle_t        sineTaskH;


//Mutex
//SemaphoreHandle_t   SerialMutex;

void setup() {
    inicializar_motor();
    Serial.begin(9600);
    
    xTaskCreate(ledTask,            //Funcao
                "ledTask",          //Nome
                128,                //Pilha
                NULL,               //Parametro
                1,                  //Prioridade
                &ledTaskH);
     
}
 
void loop() {
    // Nada é feito aqui, Todas as funções são feitas em Tasks
}
 

void ledTask(void *arg) {
    
    while(true) {
        despejar_alimento();
        vTaskDelay(1000/portTICK_PERIOD_MS);
        fechar_recipiente();
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
 

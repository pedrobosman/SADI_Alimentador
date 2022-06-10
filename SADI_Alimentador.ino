#include "Arduino_FreeRTOS.h"
#include "task.h"
#include "ArduinoJson.h"
#include <EEPROM.h>

#include "tasks_commom.h"
#include "Motor_Alimentador.h"
#include "Ultrassom_Alimentador.h"
#include "Led_Alimentador.h"
#include "Ldr_Alimentador.h"
#include "Relogio_Alimentador.h"
#include "Alimentador.h"

#define NMAX_HORARIOS_PARA_ALIMENTAR 20
//Tasks
//TaskHandle_t        ledTaskH;
Alimentar dar_alimento[NMAX_HORARIOS_PARA_ALIMENTAR];
void setup() {

  Serial.begin(9600);
  Serial.setTimeout(1000);
  inicializar_motor();
  inicializar_ultrassom();
  inicializar_luz();
  inicializar_ldr();

  //Recuperando última hora definida
  int hora = 0, minuto = 0,  segundo = 0;
  EEPROM.get(0, hora);
  EEPROM.get(sizeof(int), minuto);
  EEPROM.get(2 * sizeof(int), segundo);

  definir_horario(hora, minuto, segundo);
  fechar_recipiente();

  xTaskCreate(task_relogio, "task_relogio", TASK_STACK_SIZE_RELOGIO, NULL, TASK_PRIORITY_RELOGIO, NULL);

  xTaskCreate(task_serial, "task_serial", TASK_STACK_SIZE_SERIAL, NULL, TASK_PRIORITY_SERIAL, NULL);

  xTaskCreate(alimentador_main, "alimentador_main", TASK_STACK_SIZE_ALIMENTADOR, NULL, TASK_PRIORITY_ALIMENTADOR, NULL);

}

void loop() {
  // Nada é feito aqui, Todas as funções são feitas em Tasks
}


void alimentador_main(void *arg) {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  while (true) {
    for (int i = 0; i < NMAX_HORARIOS_PARA_ALIMENTAR; i++) {
      if (passou_do_horario(dar_alimento[i].hora, dar_alimento[i].minuto, 0) && (!dar_alimento[i].ja_alimentou) && dar_alimento[i].id > 0) {
        despejar_alimento();
        vTaskDelay(dar_alimento[i].tempo_vazao_ms / portTICK_PERIOD_MS);
        fechar_recipiente();
        dar_alimento[i].ja_alimentou = true;
      }
    }
    if (luminosidade_ambiente() > 2.5) {
      acender_luz();
    } else {
      desligar_luz();
    }
    if (novo_dia) {
      novo_dia = false;
      for (int i = 0; i < NMAX_HORARIOS_PARA_ALIMENTAR; i++) {
        dar_alimento[i].ja_alimentou = false;
      }
    }
  }
  vTaskDelay(120 / portTICK_PERIOD_MS);
}



void task_serial(void *arg) {
  Serial.println("Comecei");
  Serial.println(horario_para_json());
  while (true) {

    if (Serial.available() > 0) {
      String receber_json = Serial.readString();
      DynamicJsonDocument valores_do_json(256);
      DeserializationError err = deserializeJson(valores_do_json, receber_json);
      if (err)
      {
        DynamicJsonDocument erro_json_doc(256);
        erro_json_doc["erro"] = err.c_str();
        String erro_json;
        serializeJson(erro_json_doc, erro_json);
        Serial.println(erro_json);
      }
      else
      {
        switch ((int)valores_do_json["tipo_msg"])
        {
          case 1: {//Nova Alimentação
              int id = (int)valores_do_json["id"];
              if (id == 0 || id > NMAX_HORARIOS_PARA_ALIMENTAR) {
                Serial.println("{\"erro\":\"id_errado\"}");
              } else {
                dar_alimento[id - 1] = Json_para_alimentar(valores_do_json);
              }
              break;
            }
          case 2: {//Enviar Alimentação
              Alimentar alimentar_get;
              int id = (int)valores_do_json["id"];
              if ( id == 0 || id > NMAX_HORARIOS_PARA_ALIMENTAR) {
                Serial.println("{\"erro\":\"id_errado\"}");
              } else {
                alimentar_get = dar_alimento[id - 1];
                Serial.println(Alimentar_para_json(alimentar_get));
              }
              break;
            }
          case 3: {//Enviar Máximo ID's
              DynamicJsonDocument id_json_doc(32);
              String nmax_id_json;
              
              id_json_doc["nmax_id"] = NMAX_HORARIOS_PARA_ALIMENTAR;
              serializeJson(id_json_doc, nmax_id_json);
              Serial.println(nmax_id_json);
              break;
            }
          case 4: {//Set Relogio Arduino
              definir_horario(valores_do_json["hora"], valores_do_json["minuto"], valores_do_json["segundo"]);
              break;
            }
          case 5: { //Get Relogio Arduino
              Serial.println(horario_para_json());
              break;
            }
          case 6: { //Set Data Arduino
              break;
            }
          case 7: { //Get Data Arduino
              break;
            }
        }
      }
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

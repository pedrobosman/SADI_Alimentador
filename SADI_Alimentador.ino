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
#include "BuzzerAtivo_Alimentador.h"

#define NMAX_HORARIOS_PARA_ALIMENTAR 20
//Tasks
//TaskHandle_t        ledTaskH;
Alimentar dar_alimento[NMAX_HORARIOS_PARA_ALIMENTAR];

int porcentagem_lampada = 100;
double tensao_ldr = 2.5;

//BUZZER
int n_beeps = 2;
int tempo_beep = 100;
int tempo_entre_beeps = 100;

void setup() {

  Serial.begin(9600);
  Serial.setTimeout(10);
  inicializar_motor();
  inicializar_ultrassom();
  inicializar_luz();
  inicializar_ldr();
  inicializar_buzzer_ativo();
  
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
  vTaskDelay(200 / portTICK_PERIOD_MS);
  while (true) {
    for (int i = 0; i < NMAX_HORARIOS_PARA_ALIMENTAR; i++) {
      if (passou_do_horario(dar_alimento[i].hora, dar_alimento[i].minuto, 0) && (!dar_alimento[i].ja_alimentou) && dar_alimento[i].id > 0) {
        despejar_alimento();
        vTaskDelay(dar_alimento[i].tempo_vazao_ms / portTICK_PERIOD_MS);
        if (verificar_tampa_despejando()) {
          dar_alimento[i].ja_alimentou = true;
          n_beeps_aviso(n_beeps,tempo_beep,tempo_entre_beeps);
        } else {
          dar_alimento[i].ja_alimentou = false;
        }
        fechar_recipiente();
      }
    }
    if (luminosidade_ambiente() > tensao_ldr) {
      acender_luz_como_dimer(porcentagem_lampada);
    } else {
      desligar_luz();
    }
    if (novo_dia) {
      novo_dia = false;
      for (int i = 0; i < NMAX_HORARIOS_PARA_ALIMENTAR; i++) {
        dar_alimento[i].ja_alimentou = false;
      }
    }
    //Serial.println(distancia_ultrassom());
    vTaskDelay(120 / portTICK_PERIOD_MS);
  }
}



void task_serial(void *arg) {
  while (true) {

    if (Serial.available() > 0) {
      String receber_json = Serial.readStringUntil("\n");
      DynamicJsonDocument valores_do_json(256);
      DeserializationError err = deserializeJson(valores_do_json, receber_json);
      if (err)
      {
        String erro_json;
        erro_json.concat("{\"erro\":");
        erro_json.concat("\"");
        erro_json.concat(err.c_str());
        erro_json.concat("\"");
        erro_json.concat("}");
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
              String nmax_id_json;
              nmax_id_json.concat("{\"nmax_id\":");
              nmax_id_json.concat(NMAX_HORARIOS_PARA_ALIMENTAR);
              nmax_id_json.concat("}");
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
          case 6: {//Receber % de ilumincação da lampada
              porcentagem_lampada = valores_do_json["porcentagem"];
              break;
            }
          case 7: {//Receber % de clareza para ligar a lampada(LDR)
              double V_ldr = valores_do_json["tensao_ldr"];
              if(V_ldr<=5&&V_ldr>=0){
                tensao_ldr = V_ldr;
              }
              break;
            }
          
          case 8: {//Enviar status do LED
              String led_json;
              led_json.concat("{\"led_status\":");
              led_json.concat(led_status);
              led_json.concat(",\"porcentagem\":");
              led_json.concat(porcentagem_lampada);
              led_json.concat("}");
              Serial.println(led_json);
              break;
            }
          case 9: {//Enviar claridade do ambiente
              double V_ldr = luminosidade_ambiente();
              String ldr_json;
              ldr_json.concat("{\"tensao_ldr\":");
              ldr_json.concat(V_ldr);
              ldr_json.concat(",\"limite_ldr\":");
              ldr_json.concat(tensao_ldr);
              ldr_json.concat("}");
              Serial.println(ldr_json);
              break;
            }
           case 10: {//Enviar ping de conectado (OK)
              String ping_json;
              ping_json.concat("{\"status\":");
              ping_json.concat("\"");
              ping_json.concat("OK");
              ping_json.concat("\"");
              ping_json.concat("}");
              Serial.println(ping_json);
              break;
            }
            case 11: {//Excluir Alimentação
              int id = (int)valores_do_json["id"];
              if (id == 0 || id > NMAX_HORARIOS_PARA_ALIMENTAR) {
                Serial.println("{\"erro\":\"id_errado\"}");
              } else {
                dar_alimento[id - 1].id = 0;
              }
              break;
            }
         
        }
      }
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

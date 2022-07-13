#include "Relogio_Alimentador.h"

struct tm tm_relogio;

bool novo_dia = false;

void task_relogio(void *arg) {
   while (true) {
    if (tm_relogio.tm_sec < 59) {
      tm_relogio.tm_sec += 1;
    }
    else {
      tm_relogio.tm_sec = 0;
      if (tm_relogio.tm_min < 59) {
        tm_relogio.tm_min += 1;
      }
      else {
        tm_relogio.tm_min = 0;
        if (tm_relogio.tm_hour < 23)
          tm_relogio.tm_hour += 1;
        else
          tm_relogio.tm_hour = 0;
      }
    }
    if((tm_relogio.tm_hour == 0) && (tm_relogio.tm_min == 0)){
        novo_dia = true;
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void definir_horario(int horas, int minutos, int segundos) {
  if (horas >= 0 || horas <= 23) {
    tm_relogio.tm_hour = horas;
    EEPROM.put(0, horas);
  }
  if (minutos >= 0 || minutos <= 59) {
    tm_relogio.tm_min = minutos;
    EEPROM.put(sizeof(int), minutos);
  }
  if (segundos >= 0 || segundos <= 59) {
    tm_relogio.tm_sec = segundos;
    EEPROM.put(2*sizeof(int), minutos);
  }
}

void definir_data(int dia,int mes ,int ano){
  mes -= 1;
   if (dia >= 1 || dia <= 31) {
    tm_relogio.tm_mday = dia;
  }
  if (mes >= 0 || mes <= 11) {
    tm_relogio.tm_mon = mes;
  }
  if (ano >= 1900) {
    tm_relogio.tm_year = ano;
  }
}

bool passou_do_horario(int hora,int minuto,int segundo){
  if((tm_relogio.tm_hour >= hora) && (tm_relogio.tm_min>=minuto)){
    return true;
  }else{
    return false;   
  }  
}

String horario_para_json(){
  String json;
  json.concat("{\"hora\":");
  json.concat(tm_relogio.tm_hour);
  json.concat(",\"minuto\":");
  json.concat(tm_relogio.tm_min);
  json.concat(",\"segundo\":");
  json.concat(tm_relogio.tm_sec);
  json.concat("}");
  return json;
}

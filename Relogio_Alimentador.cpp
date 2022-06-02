#include "Relogio_Alimentador.h"

struct tm tm_relogio;

void task_relogio(void *arg) {
  definir_horario(0, 0, 0);
  definir_data(1,0 ,2000);

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
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void definir_horario(int horas, int minutos, int segundos) {
  if (horas >= 0 || horas <= 23) {
    tm_relogio.tm_hour = horas;
  }
  if (minutos >= 0 || minutos <= 59) {
    tm_relogio.tm_min = minutos;
  }
  if (segundos >= 0 || segundos <= 59) {
    tm_relogio.tm_sec = segundos;
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
  if((tm_relogio.tm_hour>= hora) && (tm_relogio.tm_min>= minuto)  && (tm_relogio.tm_sec >= segundo-1)){
    return true;
  }else{
    return false;   
  }  
}
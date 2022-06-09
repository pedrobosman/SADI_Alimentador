#ifndef _ALIMENTADOR_H_
#define _ALIMENTADOR_H_

#include "ArduinoJson.h"

#define NO_ID_ERROR 99999
class Alimentar{
  public:
    int id;
    int hora;
    int minuto;
    double tempo_vazao_ms;
};

Alimentar Json_para_alimentar(DynamicJsonDocument);

String Alimentar_para_json(Alimentar obj);
#endif

#ifndef _ALIMENTADOR_H_
#define _ALIMENTADOR_H_

#include "ArduinoJson.h"

class Alimentar{
  public:
    int hora;
    int minuto;
    double tempo_vazao;
};

Alimentar Json_para_alimentar(String);
#endif

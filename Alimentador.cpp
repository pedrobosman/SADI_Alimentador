#include "Alimentador.h"

Alimentar Json_para_alimentar(String json){
  DynamicJsonDocument alimentar_json(1024);
  deserializeJson(alimentar_json, json);
  Alimentar alimentar_obj;
  
  alimentar_obj.hora = alimentar_json["hora"];
  alimentar_obj.minuto  = alimentar_json["minuto"];
  alimentar_obj.tempo_vazao = alimentar_json["tempo_vazao"];
  
  return alimentar_obj;
}

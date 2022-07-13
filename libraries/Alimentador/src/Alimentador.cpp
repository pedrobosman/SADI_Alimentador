#include "Alimentador.h"

Alimentar Json_para_alimentar(DynamicJsonDocument alimentar_json) {
  Alimentar alimentar_obj;
    alimentar_obj.id                  = (int)alimentar_json["id"];
    alimentar_obj.hora                = (int)alimentar_json["hora"];
    alimentar_obj.minuto              = (int)alimentar_json["minuto"];
    alimentar_obj.tempo_vazao_ms      = (double)alimentar_json["tempo_vazao_ms"];
    alimentar_obj.ja_alimentou        = (bool)alimentar_json["ja_alimentou"];
  return alimentar_obj;
}

String Alimentar_para_json(Alimentar obj) {
  String json;
  json.concat("{\"id\":");
  json.concat(obj.id);
  
  json.concat(",\"hora\":");
  json.concat(obj.hora);
  
  json.concat(",\"minuto\":");
  json.concat(obj.minuto);
  
  json.concat(",\"tempo_vazao_ms\":");
  json.concat(obj.tempo_vazao_ms);
  
  json.concat(",\"ja_alimentou\":");
  json.concat(obj.ja_alimentou);
  
  json.concat("}");
  return json;
}


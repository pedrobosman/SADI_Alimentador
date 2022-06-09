#include "Alimentador.h"

Alimentar Json_para_alimentar(DynamicJsonDocument alimentar_json) {
  Alimentar alimentar_obj;
    alimentar_obj.id                  = (int)alimentar_json["id"];
    alimentar_obj.hora                = (int)alimentar_json["hora"];
    alimentar_obj.minuto              = (int)alimentar_json["minuto"];
    alimentar_obj.tempo_vazao_ms      = (double)alimentar_json["tempo_vazao_ms"];
  return alimentar_obj;
}

String Alimentar_para_json(Alimentar obj) {
  String json;
  DynamicJsonDocument alimentar_json(256);
  alimentar_json["id"]              = obj.id;
  alimentar_json["hora"]            = obj.hora;
  alimentar_json["minuto"]          = obj.minuto;
  alimentar_json["tempo_vazao_ms"]  = obj.tempo_vazao_ms;
  alimentar_json["ja_alimentou"]    = obj.ja_alimentou;
  serializeJson(alimentar_json, json);
  return json;
}

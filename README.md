Compilar no arduino:

Modificar em: Preferências->local do sketchbook para o diretório desse sketch

Enviar no Serial:

Rotina Exemplo:

{"tipo_msg":5} //Ver horario do arduino

//Definir Horario p/ alimentar 
{"tipo_msg":1,"id":1,"hora":8,"minuto":15,"tempo_vazao_ms":500}
{"tipo_msg":1,"id":2,"hora":12,"minuto":20,"tempo_vazao_ms":1000}
{"tipo_msg":1,"id":3,"hora":18,"minuto":05,"tempo_vazao_ms":2000}

//Verificar horarios definidos - No max. 20
{"tipo_msg":2,"id":1}
{"tipo_msg":2,"id":2}
{"tipo_msg":2,"id":3}


//Modificar Horário do arduino
{"tipo_msg":4,"hora":8,"minuto":14,"segundo":55}
{"tipo_msg":2,"id":1} // Verificar a abertura do alimentador e a variavel: ja_alimentou = true

{"tipo_msg":4,"hora":12,"minuto":19,"segundo":55}
{"tipo_msg":2,"id":2} // Verificar a abertura do alimentador e a variavel: ja_alimentou = true

{"tipo_msg":4,"hora":18,"minuto":04,"segundo":55}
{"tipo_msg":2,"id":3} // Verificar a abertura do alimentador e a variavel: ja_alimentou = true

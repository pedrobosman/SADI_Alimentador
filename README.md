Compilar no arduino:

Modificar em: Preferências->local do sketchbook para o diretório desse sketch

Enviar no Serial:

-Rotina Exemplo:

//Ver horario do arduino

    {"tipo_msg":5} 
    
//Definir Horario p/ alimentar e verificar

    {"tipo_msg":1,"id":1,"hora":8,"minuto":15,"tempo_vazao_ms":500, "ja_alimentou":0}
    {"tipo_msg":1,"id":2,"hora":12,"minuto":20,"tempo_vazao_ms":1000, "ja_alimentou":0}
    {"tipo_msg":1,"id":3,"hora":18,"minuto":05,"tempo_vazao_ms":2000, "ja_alimentou":0}

//Verificar os horarios definidos - No max. 20

    {"tipo_msg":2,"id":1}
    {"tipo_msg":2,"id":2}
    {"tipo_msg":2,"id":3}


//Modificar Horário do arduino

      {"tipo_msg":4,"hora":8,"minuto":14,"segundo":55}

// Verificar a abertura do alimentador e a variavel: ja_alimentou = true

      {"tipo_msg":2,"id":1}                                   

//Modificar Horário do arduino

      {"tipo_msg":4,"hora":12,"minuto":19,"segundo":55}

// Verificar a abertura do alimentador e a variavel: ja_alimentou = true

      {"tipo_msg":2,"id":2}                                   

//Modificar Horário do arduino
 
      {"tipo_msg":4,"hora":18,"minuto":04,"segundo":55}

// Verificar a abertura do alimentador e a variavel: ja_alimentou = true

      {"tipo_msg":2,"id":3}                                   

//Novo Dia; Reiniciar a variavel ja_alimentou;

      {"tipo_msg":4,"hora":23,"minuto":59,"segundo":55}       

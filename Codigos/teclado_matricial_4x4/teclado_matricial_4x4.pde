byte const teclado_linha_a   =  3;
byte const teclado_linha_b   =  4;
byte const teclado_linha_c   =  5;
byte const teclado_linha_d   =  6;

byte const teclado_coluna_1  =  7;
byte const teclado_coluna_2  =  8;
byte const teclado_coluna_3  =  9;
byte const teclado_coluna_4  =  10;

void setup ()
{
  Serial.begin ( 9600 );
}

void loop ()
{
  
}

byte tecladoInicializar ()
{
  pinMode ( teclado_linha_a, OUTPUT );
  digitalWrite ( teclado_linha_a, HIGH );
  
  pinMode ( teclado_linha_a, OUTPUT );
  digitalWrite ( teclado_linha_a, HIGH );
  
  pinMode ( teclado_linha_a, OUTPUT );
  digitalWrite ( teclado_linha_a, HIGH );
  
  pinMode ( teclado_linha_a, OUTPUT );
  digitalWrite ( teclado_linha_a, HIGH );
  
  pinMode ( teclado_coluna_1, INPUT );
  digitalWrite ( teclado_coluna_1, HIGH );
  
  pinMode ( teclado_coluna_2, INPUT );
  digitalWrite ( teclado_coluna_2, HIGH );
  
  pinMode ( teclado_coluna_3, INPUT );
  digitalWrite ( teclado_coluna_3, HIGH );
  
  pinMode ( teclado_coluna_4, INPUT );
  digitalWrite ( teclado_coluna_4, HIGH );
}

byte tecladoVarrerLinha ()
{
  byte tecla;
  
  digitalWrite ( teclado_linha_a, LOW );
  
  tecla   =  tecladoVarrerColuna ();
  
  digitalWrite ( teclado_linha_a, HIGH );
  
  if ( tecla != 0 )
  {
    return tecla;
  }
  
  digitalWrite ( teclado_linha_b, LOW );
  
  tecla   =  tecladoVarrerColuna ();
  
  digitalWrite ( teclado_linha_b, HIGH );
  
  if ( tecla != 0 )
  {
    return ( tecla + 4 );
  }
  
  
  digitalWrite ( teclado_linha_c, LOW );
  
  if ( tecla != 0 )
  {
    return ( tecla + 8 );
  }
  
  digitalWrite ( teclado_linha_c, HIGH );
  digitalWrite ( teclado_linha_d, LOW );
  
  if ( tecla != 0 )
  {
    return ( tecla + 12 );
  }
  
  return 0;
}

byte tecladoVarrerColuna ()
{
  if ( digitalRead ( teclado_coluna_1 ) == LOW )
  {
    return 1;
  }
  
  if ( digitalRead ( teclado_coluna_2 ) == LOW )
  {
    return 2;
  }
  
  if ( digitalRead ( teclado_coluna_3 ) == LOW )
  {
    return 3;
  }
  
  if ( digitalRead ( teclado_coluna_4 ) == LOW )
  {
    return 4;
  }
  
  return 0;
}

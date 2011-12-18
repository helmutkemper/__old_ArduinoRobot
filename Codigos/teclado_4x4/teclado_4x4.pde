/******************************************************
* Código fonte: Helmut Kemper                         *
* Contato: helmut.kemper@gmail.com                    *
* Site: http://www.kemper.com.br                      *
*                                                     *
* Este código tem objetivo demonstrar aos meus alunos *
* como configurar e usar um teclado matricial 4x4 de  *
* forma simples e didática. Caso você queira ver a    *
* aula completa, ela pode ser vista de forma gratuita *
* no meu site pessoal.                                *
******************************************************/

// Define os pinos usados na ligação do teclado
const byte linha_1 = 2;
const byte linha_2 = 3;
const byte linha_3 = 4;
const byte linha_4 = 5;

const byte coluna_1 = 6;
const byte coluna_2 = 7;
const byte coluna_3 = 8;
const byte coluna_4 = 9;

// Configura os pinos de acordo com o algoritmo apresentado
void configura ()
{
  // Coloca todas as linhas como saida
  pinMode ( linha_1, OUTPUT );
  pinMode ( linha_2, OUTPUT );
  pinMode ( linha_3, OUTPUT );
  pinMode ( linha_4, OUTPUT );

  // Coloca as colunas como entradas e liga o resistor de pull-up
  pinMode ( coluna_1, INPUT );
  digitalWrite ( coluna_1, HIGH );
  
  pinMode ( coluna_2, INPUT );
  digitalWrite ( coluna_2, HIGH );
  
  pinMode ( coluna_3, INPUT );
  digitalWrite ( coluna_3, HIGH );
  
  pinMode ( coluna_4, INPUT );
  digitalWrite ( coluna_4, HIGH );
}

// Varre o teclado e retorna o valor lido no formato ASCII,
// ou seja, 0 != '0', pois, 0 representa o valor zero numérico e '0' 
//corresponde ao valor numérico 0x30, conforme a tabela ASCII
byte leTeclado ()
{
  // Garante que todas as linhas estão ligadas corretamente
  digitalWrite ( linha_1, LOW );
  digitalWrite ( linha_2, HIGH );
  digitalWrite ( linha_3, HIGH );
  digitalWrite ( linha_4, HIGH );
  
  // Testa as colunas uma por uma
  if ( digitalRead ( coluna_1 == LOW ) )
  {
    return ( '1' );
  }
  
  if ( digitalRead ( coluna_2 == LOW ) )
  {
    return ( '2' );
  }
  
  if ( digitalRead ( coluna_3 == LOW ) )
  {
    return ( '3' );
  }
  
  if ( digitalRead ( coluna_4 == LOW ) )
  {
    return ( 'A' );
  }
  
  // Troca a linha em estado baixo
  digitalWrite ( linha_1, HIGH );
  digitalWrite ( linha_2, LOW );
  
  // Testa as colunas uma por uma
  if ( digitalRead ( coluna_1 == LOW ) )
  {
    return ( '4' );
  }
  
  if ( digitalRead ( coluna_2 == LOW ) )
  {
    return ( '5' );
  }
  
  if ( digitalRead ( coluna_3 == LOW ) )
  {
    return ( '6' );
  }
  
  if ( digitalRead ( coluna_4 == LOW ) )
  {
    return ( 'B' );
  }
  
  // Troca a linha em estado baixo
  digitalWrite ( linha_2, HIGH );
  digitalWrite ( linha_3, LOW );
  
  // Testa as colunas uma por uma
  if ( digitalRead ( coluna_1 == LOW ) )
  {
    return ( '7' );
  }
  
  if ( digitalRead ( coluna_2 == LOW ) )
  {
    return ( '8' );
  }
  
  if ( digitalRead ( coluna_3 == LOW ) )
  {
    return ( '9' );
  }
  
  if ( digitalRead ( coluna_4 == LOW ) )
  {
    return ( 'C' );
  }
  
  // Testa as colunas uma por uma
  digitalWrite ( linha_3, HIGH );
  digitalWrite ( linha_4, LOW );
  
  if ( digitalRead ( coluna_1 == LOW ) )
  {
    return ( '*' );
  }
  
  if ( digitalRead ( coluna_2 == LOW ) )
  {
    return ( '0' );
  }
  
  if ( digitalRead ( coluna_3 == LOW ) )
  {
    return ( '#' );
  }
  
  if ( digitalRead ( coluna_4 == LOW ) )
  {
    return ( 'D' );
  }
}

void setup ()
{
  // Configura o teclado
  configura ();
  
  // Configura a porta serial
  Serial.begin ( 9600 );
}

void loop ()
{
  // Le o teclado e encia o valor lido pela porta serial
  switch ( leTeclado () )
  {
    case '0': Serial.println ( '0' ); break;
    case '1': Serial.println ( '1' ); break;
    case '2': Serial.println ( '2' ); break;
    case '3': Serial.println ( '3' ); break;
    case '4': Serial.println ( '4' ); break;
    case '5': Serial.println ( '5' ); break;
    case '6': Serial.println ( '6' ); break;
    case '7': Serial.println ( '7' ); break;
    case '8': Serial.println ( '8' ); break;
    case '9': Serial.println ( '9' ); break;
    case 'A': Serial.println ( 'A' ); break;
    case 'B': Serial.println ( 'B' ); break;
    case 'C': Serial.println ( 'C' ); break;
    case 'D': Serial.println ( 'D' ); break;
    case '*': Serial.println ( '*' ); break;
    case '#': Serial.println ( '#' ); break;
  }
}

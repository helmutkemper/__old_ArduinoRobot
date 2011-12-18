#include "Ultrasonic.h"
//Ultrasonic(int TP, int EP)
Ultrasonic sensor_direita ( 2, 3 );

const byte motor_direita_0 = 4;
const byte motor_direita_1 = 5;

const int distancia_objeto = 30;

int distancia_direita;
int distancia_esquerda;



void setup()
{
  Serial.begin ( 9600 );
  pinMode ( motor_direita_0, OUTPUT );
  pinMode ( motor_direita_1, OUTPUT );
}

void loop()
{
  distancia_direita = sensor_direita.Ranging ( CM );
  Serial.print   ( "Sensor direita: " );
  Serial.println ( distancia_direita );
  
  if ( distancia_direita <= distancia_objeto )
  {
    digitalWrite ( motor_direita_0, HIGH );
    digitalWrite ( motor_direita_1, LOW );
  }
  
  else
  {
    digitalWrite ( motor_direita_0, LOW );
    digitalWrite ( motor_direita_1, LOW );
  }
  
  /*
  digitalWrite ( motor_esquerda, LOW );
  delay ( 1000 );
  digitalWrite ( motor_esquerda, HIGH );
  delay ( 1000 );
  
  
  */
}

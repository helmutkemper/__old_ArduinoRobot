#include "Ultrasonic.h"
//Ultrasonic(int TP, int EP)

const byte pino_led              =  13;

const byte sensor_direita_ping   =  12;
const byte sensor_direita_echo   =  11;

const byte sensor_esquerda_ping  =  10;
const byte sensor_esquerda_echo  =  9;

const byte motor_direita         =  2;
const byte motor_esquerda        =  3;

const byte distancia_objeto      =  30;

Ultrasonic sensor_direita  ( sensor_direita_ping,  sensor_direita_echo );
Ultrasonic sensor_esquerda ( sensor_esquerda_ping, sensor_esquerda_echo );

int distancia_direita;
int distancia_esquerda;

void setup()
{
  Serial.begin ( 9600 );
  pinMode ( motor_direita, OUTPUT );
  pinMode ( motor_esquerda, OUTPUT );
}

void loop()
{
  distancia_direita  = sensor_direita.Ranging ( CM );
  
  Serial.print   ( "Sensor direita: " );
  Serial.println ( distancia_direita );
  
  if ( distancia_direita <= distancia_objeto )
  {
    digitalWrite ( motor_direita, HIGH );
    delay ( 100 );
  }
  
  digitalWrite ( motor_direita, LOW );
  
  distancia_esquerda = sensor_esquerda.Ranging ( CM );
  
  Serial.print   ( "Sensor esquerda: " );
  Serial.println ( distancia_esquerda );
  
  if ( distancia_esquerda <= distancia_objeto )
  {
    digitalWrite ( motor_esquerda, HIGH );
    delay ( 100 );
  }
  
  digitalWrite ( motor_esquerda, LOW );
  
  /*
  digitalWrite ( motor_esquerda, LOW );
  delay ( 1000 );
  digitalWrite ( motor_esquerda, HIGH );
  delay ( 1000 );
  
  
  */
}

#include <Servo.h> 
#include "SayItModule.h"

const byte pinoLed =  13;
boolean reconhecimento = false;

unsigned char teste[5] = { CommandList::Break, CommandList::TimeOutInfinite, CommandList::LanguageEnglish, CommandList::recPreProgrammedTrigger, CommandList::Free };
unsigned char *p;

Servo servoMotor;
boolean pass = false;
byte apontadorSerial = 0;
byte portaSerial[5];
byte contador = 0;
int servoTempo = 1500;
int ledEstado = HIGH;

void nada ( unsigned char vaucIndex )
{
  if ( ledEstado == HIGH )
  {
    ledEstado = LOW;
  }
  
  else
  {
    ledEstado = HIGH;
  }
  
  digitalWrite ( pinoLed, ledEstado );
}

void setup (  )
{ 
  Serial.begin ( 9600 );
  
  servoMotor.attach ( 9, 707, 2400 );
  servoMotor.writeMicroseconds ( servoTempo );
  
  
  p = &teste[0];
  SayItModule::vcucpMemory = &teste[0];
  pinMode ( pinoLed, OUTPUT );
  
  SayItModule::setSerial ( SerialPort::Port1 );
  SayItModule::defineEventFunction ( &reconhecimentoOk, Reconhecimento );
  SayItModule::defineEventFunction ( &nada, Erro );
  SayItModule::defineEventFunction ( &nada, Livre );
  SayItModule::start ();
  
  reconhecimentoOk( 1 );
  
}

void reconhecimentoOk ( unsigned char vaucIndex )
{
  Serial.print ( "reconheceu: " );
  Serial.println ( vaucIndex );
  SayItModule::setGroup ( CommandList::recPreProgrammedCommand );
  
  if ( ledEstado == HIGH )
  {
    ledEstado = LOW;
  }
  
  else
  {
    ledEstado = HIGH;
  }
  
  digitalWrite ( pinoLed, ledEstado );
}

void loop (  )
{
  SayItModule::run ();
  
  if ( Serial.available() )
  {
    portaSerial[ apontadorSerial ] =  Serial.read ();
    
    if ( ( portaSerial[ apontadorSerial ] == 10 ) || ( portaSerial[ apontadorSerial ] == 13 ) )
      pass = true;
      
    else
      apontadorSerial ++;
  }
  
  if ( pass )
  {
    switch ( apontadorSerial )
    {
      case 1:
        Serial.println ( "0" );
        servoTempo = ( portaSerial[ 0 ] - 0x30 );
        break;
      
      case 2:
        Serial.println ( "1" );
        servoTempo = ( portaSerial[ 1 ] - 0x30 ) + ( portaSerial[ 0 ] - 0x30 ) * 10;
        break;
        
      case 3:
        Serial.println ( "2" );
        servoTempo = ( portaSerial[ 2 ] - 0x30 ) + ( portaSerial[ 1 ] - 0x30 ) * 10 + ( portaSerial[ 0 ] - 0x30 ) * 100;
        break;
        
      case 4:
        Serial.println ( "3" );
        servoTempo = ( portaSerial[ 3 ] - 0x30 ) + ( portaSerial[ 2 ] - 0x30 ) * 10 + ( portaSerial[ 1 ] - 0x30 ) * 100 + ( portaSerial[ 0 ] - 0x30 ) * 1000;
        break;
        
      case 5:
        Serial.println ( "4" );
        servoTempo = ( portaSerial[ 4 ] - 0x30 ) + ( portaSerial[ 3 ] - 0x30 ) * 10 + ( portaSerial[ 2 ] - 0x30 ) * 100 + ( portaSerial[ 1 ] - 0x30 ) * 1000 + ( portaSerial[ 0 ] - 0x30 ) * 10000;
        break;
    }
    
    if ( servoTempo < 720 )
      servoTempo = 720;
      
    servoMotor.writeMicroseconds ( servoTempo );
    
    Serial.println ( String ( servoTempo ) );
    
    pass = false;
    apontadorSerial = 0;
    Serial.flush ();
  }
  
  
}

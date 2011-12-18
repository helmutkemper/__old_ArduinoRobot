#include "SayItModule.h"

const byte pinoLed =  13;
//boolean reconhecimento = false;

unsigned char teste[5] = { CommandList::Break, CommandList::TimeOutInfinite, CommandList::LanguageEnglish, CommandList::recPreProgrammedTrigger, CommandList::Free };
unsigned char *p;

void setup ()
{
  p = &teste[0];
  SayItModule::vcucpMemory = &teste[0];
  pinMode ( pinoLed, OUTPUT );
  
  SayItModule::setSerial ( SerialPort::Port1 );
  SayItModule::defineEventFunction ( &piscar1, Reconhecimento );
  SayItModule::defineEventFunction ( &piscar2, Erro );
  SayItModule::defineEventFunction ( &piscar3, Livre );
  SayItModule::start ();
}

void loop ()
{
  int cont = 0;
  SayItModule::run ();
}

void piscar1 ( unsigned char vaucIndex )
{
  byte count;
  for ( count = 0; count != 4; count ++ )
  {
    digitalWrite ( pinoLed, HIGH );
    delay ( 300 );
    digitalWrite ( pinoLed, LOW );
    delay ( 300 );
  }
  Serial.print ( "reconheceu: " );
  Serial.println ( vaucIndex );
  teste[0] =  CommandList::recPreProgrammedCommand;
  teste[1] =  CommandList::Free;
  SayItModule::vcucpMemory = &teste[0];
  
  //SayItModule::setGroup ( CommandList::recPreProgrammedCommand );
}

void piscar2 ( unsigned char vaucIndex )
{
  digitalWrite ( pinoLed, HIGH );
  delay ( 300 );
  digitalWrite ( pinoLed, LOW );
  delay ( 300 );
  digitalWrite ( pinoLed, HIGH );
  delay ( 300 );
  digitalWrite ( pinoLed, LOW );
  delay ( 300 );  
}

void piscar3 ( unsigned char vaucIndex )
{
  digitalWrite ( pinoLed, HIGH );
  delay ( 300 );
  digitalWrite ( pinoLed, LOW );
  delay ( 300 );
  digitalWrite ( pinoLed, HIGH );
  delay ( 300 );
  digitalWrite ( pinoLed, LOW );
  delay ( 300 );
  digitalWrite ( pinoLed, HIGH );
  delay ( 300 );
  digitalWrite ( pinoLed, LOW );
  delay ( 300 );
}



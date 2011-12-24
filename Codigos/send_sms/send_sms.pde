/*  @altor
 *  
 *  
 */

#include <ModemATBased.h>

const byte ledPin   =  13;

void setup ()
{
  pinMode ( ledPin, OUTPUT );
  
  ModemATBased::setSerial ( SerialPort::Port0, 19200 );
  ModemATBased::Telefon =  "99268744";
  ModemATBased::Message =  "Hello World! In Brasil, this message can be 128 characters per message";
  ModemATBased::sendTextSms ( &ledBlink );
}

void loop ()
{
  
}

void ledBlink ()
{
  while ( true )
  {
    digitalWrite ( ledPin, HIGH );
    delay ( 300 );
    
    digitalWrite ( ledPin, LOW );
    delay ( 300 );
  }
}

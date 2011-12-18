#include <ModemATBased.h>

void setup ()
{
  Serial.begin ( 19200 );
  pinMode ( 13, OUTPUT );
  delay ( 10000 );
  
  unsigned char numero[]     =  { '9', '9', '2', '6', '8', '7', '4', '4', 0x00 };
  unsigned char mensagem[]   =  { 'O', 'l', 'a', ' ', 'm', 'u', 'n', 'd', 'o', ' ', 'c', 'r', 'u', 'e', 'l', '!', 0x00 };
  
  ModemATBased::setSerial ( SerialPort::Port1 );
  ModemATBased::sendTextSms ( &numero[0], &mensagem[0] );
}

void loop ()
{
  if ( Serial1.available () )
  {
    Serial.print ( ( unsigned char ) Serial1.read () );
  }
}

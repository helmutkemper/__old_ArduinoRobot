#include <ModemATBased.h>

  unsigned char numero[]     =  { '9', '9', '2', '6', '8', '7', '4', '4', 0x00 };
  unsigned char mensagem[]   =  { 'O', 'l', 'a', ' ', 'm', 'u', 'n', 'd', 'o', ' ', 'c', 'r', 'u', 'e', 'l', '2', 0x00 };

void setup ()
{
  Serial.begin ( 19200 );
  pinMode ( 13, OUTPUT );
//  delay ( 10000 );
  

  
  ModemATBased::teste        =  &numero[0];
  ModemATBased::setSerial ( SerialPort::Port0 );
  ModemATBased::sendTextSms ( (const unsigned char *)&mensagem[0] );
}

void loop ()
{
  ModemATBased::getDataModem ();
  /*
  if ( Serial1.available () )
  {
    Serial.print ( ( unsigned char ) Serial1.read () );
  }
  */
}

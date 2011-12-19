#include <ModemATBased.h>

unsigned char numero[]     =  { '9', '9', '2', '6', '8', '7', '4', '4', 0x00 };
unsigned char mensagem[]   =  { 'O', 'l', 'a', ' ', 'm', 'u', 'n', 'd', 'o', ' ', 'c', 'r', 'u', 'e', 'l', '3', 0x00 };

void setup ()
{
  Serial.begin ( 19200 );
  
  ModemATBased::vcpucTelefone  =  &numero[0];
  ModemATBased::vcpucMessage   =  &mensagem[0];
  ModemATBased::setSerial ( SerialPort::Port1 );
  ModemATBased::sendTextSms ();
}

void loop ()
{
  ModemATBased::getDataModem ();
}

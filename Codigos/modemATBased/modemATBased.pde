#include <ModemATBased.h>

const unsigned char numero[]     =  { '8', '6', '8', '2', '5', '6', '0', '7', 0x00 };
const unsigned char mensagem[]   =  { 'p', 'a', 'r', 'a', ' ', 'r', 'e', 'c', 'e', 'b', 'r', ' ', 'u', 'm', ' ', 'k', 'i', 't', ' ', 's', 'i', 'm', 'p', 'l', 'e', 's', ' ', 'p', 'a', 'r', 'a', ' ', 'v', 'o', 'c', 'e', ',', ' ', 'F', 'a', 'b', 'i', 'o', 'l', 'a', ' ', 'e', ' ', 'E', 'r', 'i', 'l', 'a', 'n', 'e', '?', 0x00 };

void setup ()
{
  Serial.begin ( 19200 );
//  delay (10000);
  ModemATBased::vcpucTelefone  =  &numero[0];
  ModemATBased::vcpucMessage   =  &mensagem[0];
  ModemATBased::setSerial ( SerialPort::Port1 );
  ModemATBased::sendTextSms ();
}

void loop ()
{
  ModemATBased::getDataModem ();
}

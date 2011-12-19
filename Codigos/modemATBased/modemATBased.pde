#include <ModemATBased.h>

const String numero     =  "99268744";
const String mensagem   =  "Ola mundo. Esta e uma nova mensagem de teste feita para ser transmitida pelo robo.";

void setup ()
{
  Serial.begin ( 19200 );
  delay (10000);
  ModemATBased::setSerial ( SerialPort::Port1 );
  ModemATBased::sendTextSms ( &numero, &mensagem );
}

void loop ()
{
  ModemATBased::getDataModem ();
}

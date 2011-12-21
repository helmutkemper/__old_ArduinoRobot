#include <ModemATBased.h>

const String numero       =  "99268744";
const String mensagem     =  "Ola mundo. Esta e uma nova mensagem de teste feita para ser transmitida pelo robo.";

const String host         =  "kemper.com.br";
const String hostPort     =  String ( 80, DEC );
const String queryString  =  "/modem/modem.php?teste=robo%20enviando%20ok";

void setup ()
{
  Serial.begin ( 19200 );
  while (true)
  {
    if (Serial.available())
      if ((unsigned char)Serial.read()=='c')
        break;
  }
  ModemATBased::setSerial ( SerialPort::Port1 );
  ModemATBased::internetConnect ( &internetConnect );
  

  //ModemATBased::internetGETSend ( &host, &hostPort, &queryString, &pisca );
  //ModemATBased::sendTextSms ( &numero, &mensagem, &pisca );
}

void internetConnect ()
{
  ModemATBased::internetGETSend ( &host, &hostPort, &queryString, &pisca );  
}

void internetSendData ()
{
  pisca ();
}

void pisca ()
{
  while ( true )
  {
    pinMode ( 13, OUTPUT );
    digitalWrite ( 13, HIGH );
    delay ( 300 );
    digitalWrite ( 13, LOW );
    delay ( 300 );
  }
}

void loop ()
{
  ModemATBased::getDataModem ();
}

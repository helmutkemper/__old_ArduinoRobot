#include <ModemATBased.h>

const String numero       =  "99268744";
const String mensagem     =  "Ola mundo. Esta e uma nova mensagem de teste feita para ser transmitida pelo robo.";

const String host         =  "http://www.kemper.com.br";
const String hostPort     =  "80";
const String queryString  =  "/modem/modem.php?teste=6";

void setup ()
{
  Serial.begin ( 19200 );
  delay (10000);
//  ModemATBased::setSerial ( SerialPort::Port1 );
//  ModemATBased::internetConnect ( &_internetConnect );
  


  ModemATBased::sendTextSms ( &numero, &mensagem, &pisca );
}

void _internetConnect ()
{
  Serial.println ( "void _internetConnect () ok" );
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

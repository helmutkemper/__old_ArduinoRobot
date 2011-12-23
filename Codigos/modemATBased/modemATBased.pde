//#define debug_ModemATBased

#include <ModemATBased.h>

const String host         =  "kemper.com.br";
const String hostPort     =  String ( 80, DEC );
const String queryString  =  "/modem/modem.php?contador=";

unsigned int contadorLoop          =  0;

void setup ()
{
 pinMode(9, OUTPUT); 
 digitalWrite(9,LOW);
 delay(1000);
 digitalWrite(9,HIGH);
 delay(2500);
 digitalWrite(9,LOW);
 delay(3500);

  
  
  
  
  
  
  
  Serial.begin ( 19200 );
  
  while (true)
  {
    if (Serial.available())
      if ((unsigned char)Serial.read()=='c')
        break;
  }
  ModemATBased::setSerial ( SerialPort::Port1, 19200 );
  //ModemATBased::internetConnect ( &internetConnect );
  
  ModemATBased::Telefon =  "99268744";
  ModemATBased::Message =  "Hello World! In Brasil, this message can be 128 characters per message";
  ModemATBased::sendTextSms ( &pisca );
}

void internetConnect ()
{
  ModemATBased::Host        =  "kemper.com.br";
  ModemATBased::HostPort    =  "80";
  ModemATBased::internetConnectToHost ( &sendDataLoop );
}

void sendDataLoop ()
{
  /*String query=  "/modem/modem.php?contador=0";
  String data =  query.concat( String ( contadorLoop, DEC ) );
  const String * p;
  p = &data;*/
  
  
 /* const String * a = &queryString;
  String lixo;
  String b = "100";
  String c = "/modem/modem.php?contador=";//*a;
  String d = c.concat( b );
  const String * e = &c;
  */

  ModemATBased::QueryString =  "/modem/modem.php?contador=";
  ModemATBased::QueryString.concat ( String ( contadorLoop, DEC ) );
  
  ModemATBased::internetDataSendByGET ( &sendDataLoop );
  contadorLoop ++;
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

  /*
Protocolo:

	EEPROM:
	
	Versão:    unsigned char  0x0000 a 0x0005
	Id:        unsigned char  0x0006 a 0x000C
	Telefone:  unsigned char  0x000D a 0x0021
	URL:       unsigned char  0x0022 a 0x0222
	String:    unsigned char  0x0223 a 0x022D
	Status:    unsigned char  0x022E a 0x023F
	S.Key:     unsigned char  0x0240 a 0x024F
*/

#include <EEPROM.h>
#include <ModemATBased.h>

const String host         =  "kemper.com.br";
const String hostPort     =  String ( 80, DEC );
const String queryString  =  "/modem/modem.php?contador=";

String IdSmsToDelete;

unsigned int contadorLoop          =  0;

unsigned long vgulMillis  =  millis ();

void resetMillis ()
{
  vgulMillis  =  millis ();
}

boolean testMillis ( unsigned long vaulMillis )
{
  if ( millis () < vgulMillis )
  {
    resetMillis ();
  }
  
  if ( vgulMillis + vaulMillis < millis () )
  {
    return true;
  }
  
  return false;
}

void setup ()
{
  Serial.begin ( 19200 );
  
  ModemATBased::StateMachineEvent = &Evento;
  ModemATBased::setSerial ( SerialPort::Port1, 19200 );
}

void testEeprom ( unsigned char vaucAddress, unsigned char * vapucDataToTest )
{
  
}

void Evento ( eEvent e, eEvent d )
{
  switch ( e )
  {
    case Event::SignalQuality:                   Serial.print ( "\r\nEvento: Quality dBm - " );
                                                 Serial.println ( ModemATBased::SignalQualityDbm );
                                                 //ModemATBased::internetConnect ();
                                                 break;
                                                 
    case Event::DataCaptured:                    Serial.print ( "\r\nEvento: Data - " );
                                                 Serial.println ( ModemATBased::Data );
                                                 break;
                                                 
    case Event::SMSDeleted:                      //Serial.print ( "\r\nEvento: SMS Deleted" );
                                                 break;
    
    case Event::TelefonByDataUserCaptured:       Serial.print ( "\r\nEvento: User Telefon - " );
                                                 Serial.println ( ModemATBased::Telefon );
                                                 break;
    
    case Event::MessageByDataUserCaptured:       Serial.print ( ModemATBased::Message );
                                                 break;
    
    case Event::StatusByDataUserCaptured:        Serial.print ( "\r\nEvento: User Status - " );
                                                 Serial.println ( ModemATBased::Status );
                                                 break;
    
    case Event::IdByDataUserCaptured:            Serial.print ( "\r\nEvento: User Id - " );
                                                 Serial.println ( ModemATBased::Id );
                                                 break;
    
    case Event::DataByDataUserCaptured:          if ( (ModemATBased::Data).startsWith ("host:") )
                                                 {
                                                   Serial.write ( "host encontrada: " );
                                                   Serial.print ( (ModemATBased::Data).substring( 5 ) );
                                                   Serial.print ( "\r\n" );
                                                 }
                                                 else if ( (ModemATBased::Data).startsWith ("url:") )
                                                 {
                                                   Serial.write ( "url encontrada: " );
                                                   Serial.print ( (ModemATBased::Data).substring( 4 ) );
                                                   Serial.print ( "\r\n" );
                                                 }
                                                 
                                                 else if ( (ModemATBased::Data).startsWith ("id:") )
                                                 {
                                                   Serial.write ( "id encontrado: " );
                                                   Serial.print ( (ModemATBased::Data).substring( 3 ) );
                                                   Serial.print ( "\r\n" );
                                                 }
                                                 
                                                 else if ( (ModemATBased::Data).startsWith ("telefone:") )
                                                 {
                                                   Serial.write ( "telefone encontrado: " );
                                                   Serial.print ( (ModemATBased::Data).substring( 9 ) );
                                                   Serial.print ( "\r\n" );
                                                 }
                                                 
                                                 else if ( (ModemATBased::Data).startsWith ("end") )
                                                 {
                                                   ModemATBased::internetDisconnectToHost ();
                                                   Serial.print ( "Data END!\r\n" );
                                                 }
                                                 
                                                 //Serial.print ( "\r\nEvento: User Data - " );
                                                 //Serial.println ( ModemATBased::Data );
                                                 //ModemATBased::Id = IdSmsToDelete;
                                                 //ModemATBased::deleteSmsById ();
                                                 break;
    
    case Event::TimeZoneCaptured:                Serial.print ( "\r\nEvento: Time Zone - " );
                                                 Serial.println ( ModemATBased::TimeZone );
                                                 break;
    
    case Event::IdCaptured:                      Serial.print ( "\r\nEvento: Id - " );
                                                 Serial.println ( ModemATBased::Id );
                                                 break;
                                        
    case Event::DayCaptured:                     Serial.print ( "\r\nEvento: Day - " );
                                                 Serial.println ( ModemATBased::Day );
                                                 break;
                                        
    case Event::MonthCaptured:                   Serial.print ( "\r\nEvento: Month - " );
                                                 Serial.println ( ModemATBased::Month );
                                                 break;
                                        
    case Event::YearCaptured:                    Serial.print ( "\r\nEvento: Year - " );
                                                 Serial.println ( ModemATBased::Year );
                                                 break;
                                        
    case Event::HourCaptured:                    Serial.print ( "\r\nEvento: Hour - " );
                                                 Serial.println ( ModemATBased::Hour );
                                                 break;
                                        
    case Event::MinuteCaptured:                  Serial.print ( "\r\nEvento: Minute - " );
                                                 Serial.println ( ModemATBased::Minute );
                                                 break;
                                        
    case Event::SecondCaptured:                  Serial.print ( "\r\nEvento: Second - " );
                                                 Serial.println ( ModemATBased::Second );
                                                 break;
                                        
    case Event::TelefonCaptured:                 Serial.print ( "\r\nEvento: Telefon - " );
                                                 Serial.println ( ModemATBased::Telefon );
                                                 break;
                                        
    case Event::MessageCaptured:                 Serial.print ( "\r\nEvento: Message - " );
                                                 Serial.println ( ModemATBased::Message );
                                                 break;
                                        
    case Event::StatusCaptured:                  Serial.print ( "\r\nEvento: Status - " );
                                                 Serial.println ( ModemATBased::Status );
                                                 break;
                                        
    case Event::CallReady:                       ModemATBased::getSignalQuality ();
                                                 break;
                                        
    case Event::PowerDown:                       Serial.println ( "\r\nEvento: Modem desligado" );
                                                 break;
                                        
    case Event::SMSSend:                         Serial.println ( "\r\nEvento: SMS send" );
                                                 break;
                                        
    case Event::SMSRead:                         Serial.println ( "\r\nEvento: Novo SMS" );
                                                 Serial.print   ( "ModemATBased::Status: " );
                                                 Serial.println   ( ModemATBased::Status );
                                                 Serial.print   ( "ModemATBased::Telefon: " );
                                                 Serial.println   ( ModemATBased::Telefon );
                                                 Serial.print   ( "ModemATBased::Year: " );
                                                 Serial.println   ( ModemATBased::Year );
                                                 Serial.print   ( "ModemATBased::Month: " );
                                                 Serial.println   ( ModemATBased::Month );
                                                 Serial.print   ( "ModemATBased::Day: " );
                                                 Serial.println   ( ModemATBased::Day );
                                                 Serial.print   ( "ModemATBased::Hour: " );
                                                 Serial.println   ( ModemATBased::Hour );
                                                 Serial.print   ( "ModemATBased::Minute: " );
                                                 Serial.println   ( ModemATBased::Minute );
                                                 Serial.print   ( "ModemATBased::Second: " );
                                                 Serial.println   ( ModemATBased::Second );
                                                 Serial.print   ( "ModemATBased::Message: " );
                                                 Serial.println   (  ModemATBased::Message );
                                                 //IdSmsToDelete =  ModemATBased::Id;
                                                 //ModemATBased::readTextSms ();
                                                 break;
                                        
    case Event::Ring:                            Serial.println ( "\r\nEvento: tocando\r" );
                                                 ModemATBased::getCurrentCallNumber ();
                                                 break;
                                        
    case Event::NoCarrier:                       Serial.println ( "\r\nEvento: Parou de tocar\r" );
                                                 break;
                                        
    case Event::Error:                           Serial.println ( "\r\nEvento: Error" );
                                                 if ( d == Event::internetConnectFunction )
                                                 {
                                                   ModemATBased::internetConnect ();
                                                 }
                                                 break;
                                                  
    case Event::Closed:                          Serial.println ( "\r\nEvento: Closed" );
                                                 break;
                                                 
    case Event::InternetConnect:                 Serial.println ( "\r\nEvento: InternetConnect" );
                                                 ModemATBased::Host        =  "kemper.com.br";
                                                 ModemATBased::HostPort    =  "80";
                                                 ModemATBased::internetConnectToHost ();
                                                 break;
                                                 
    case Event::InternetConnectToHost:           Serial.println ( "\r\nEvento: connect to host" );
                                                 ModemATBased::QueryString =  "/modem/modem.php?status=";
                                                 ModemATBased::QueryString.concat ( String ( contadorLoop, DEC ) );
                                                 ModemATBased::internetDataSendByGET ();
                                                 contadorLoop ++;

                                                 break;
                                                 
    case Event::InternetDataSendByGET:           Serial.println ( "\r\nEvento: sent data" );
                                                 break;
                                                 
    case Event::ConnectionFailed:                Serial.println ( "\r\nEvento: connection failed\r" ); 
                                                 break;
    
                               
                                                 //ModemATBased::internetDisconnectToHost ();
                                                 //delay ( 5000 );
                                                 break;
                                        
    case Event::Close:                           Serial.println ( "\r\nEvento: close\r" );
                                                 break;
                                                 
    case Event::InternetDisconnectToHost:        if ( d == Event::internetDisconnectToHostFunction )
                                                 {
                                                   Serial.println ( "\r\nEvento: disconnect to host\r" );
                                                   ModemATBased::Id =  "1";
                                                   ModemATBased::readTextSms ();
                                                   break;
                                                 }
                                                 
  }
}

void loop ()
{
  unsigned char data;
  
  if ( Serial.available() )
  {
    data = Serial.read();
    
    if ( ( data == 's' ) || ( data == 'S' ) )
    {
      ModemATBased::Telefon =  "97344690";
      //  ModemATBased::Message =  "!data:Hello World! In Brasil, this message can be 128 characters per message";
      ModemATBased::Message =  "!telefon: 08199268744\r!data:Esta vivo!\r";
      ModemATBased::sendTextSms ();
    }
    
    else if ( ( data == 'i' ) || ( data == 'I' ) )
    {
      ModemATBased::internetConnect ();
    }
    
    else if ( ( data == 'q' ) || ( data == 'Q' ) )
    {
      ModemATBased::getSignalQuality ();
    }
    
    else if ( ( data == 'd' ) || ( data == 'D' ) )
    {
      ModemATBased::internetDisconnectToHost ();
    }
    
    else if ( ( data == 'g' ) || ( data == 'G' ) )
    {
      Serial.println ( ModemATBased::vcsSerialBuffer );
    }
    
    else if ( ( data == 'c' ) || ( data == 'C' ) )
    {
      ModemATBased::vcsSerialBuffer =  "";
    }
    
    else if ( ( data == 'r' ) || ( data == 'R' ) )
    {
      ModemATBased::Id = "1";
      ModemATBased::readTextSms ();
    }
  }
  
  ModemATBased::getDataModem ();
}


  /*
CONNECT FAIL

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

const byte kReady              =  0x00;
const byte kConnectingInternet =  0x01;
const byte kConnectingHost     =  0x02;
const byte kConnectingPage     =  0x03;
const byte kError              =  0x04;
const byte kClosed             =  0x05;
const byte kCallReady          =  0x06;

const String host          =  "kemper.com.br";
const String hostPort      =  String ( 80, DEC );

byte vgbStatusCode         =  kReady;




const unsigned int kuiEepromAddressRecordedData   =  0x0000;
const unsigned int kuiEepromAddressId             =  0x000F;
const unsigned int kuiEepromAddressTelefon        =  0x002F;
const unsigned int kuiEepromAddressUrl            =  0x0043;
const unsigned int kuiEepromAddressPage           =  0x00C3;
const unsigned int kuiEepromAddressMessage        =  0x0143;

const unsigned char kucEepromGravada[]   =  "DATA_GRAV_OK";
const unsigned char kucEepromVersion[]   =  "V1.0";

String IdSmsToDelete;
String IdLastMessage                              =  "0";
String PowerLed                                   =  "1";
unsigned long vgulMillis  =  millis ();

void onDataEvent ()
{
  int vlsiIndexOfStart, vlsiIndexOfEnd ;
  String       vlstIdActualMesageReceived;
  unsigned int vluiIdLastMesageReceived;
  unsigned int vluiIdActualMesageReceived;
  
  ModemATBased::Data   =  "";
  
  // s - id da mensagem atual
  vlsiIndexOfStart           =  ModemATBased::vcsSerialBuffer.indexOf ( "s:" );
  vlsiIndexOfEnd             =  ModemATBased::vcsSerialBuffer.indexOf ( "\r\n", vlsiIndexOfStart + 2 );
  vlstIdActualMesageReceived =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart + 2, vlsiIndexOfEnd );
  vluiIdActualMesageReceived =  StringToUInt ( vlstIdActualMesageReceived );
  
  // id da ultima mensagem valida recebida
  vluiIdLastMesageReceived   =  StringToUInt ( IdLastMessage );
  
  // esta mensagem ja foi processada
  if ( vluiIdLastMesageReceived >= vluiIdActualMesageReceived )
  {
    ModemATBased::vcsSerialBuffer =  "";
    return;
  }
  
  ModemATBased::Id       =  "";
  ModemATBased::Telefon  =  "";
  
  // arquiva o id da nova mensagem
  IdLastMessage          =  vlstIdActualMesageReceived;
  
  // i - id do novo modem
  vlsiIndexOfStart       =  ModemATBased::vcsSerialBuffer.indexOf ( "i:" );
  vlsiIndexOfEnd         =  ModemATBased::vcsSerialBuffer.indexOf ( "\r\n", vlsiIndexOfStart + 2 );
  
  if ( vlsiIndexOfStart != -1 )
  {
    ModemATBased::Id     =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart + 2, vlsiIndexOfEnd );
  }
    
  // t - telefone do modem base na SMM
  vlsiIndexOfStart       =  ModemATBased::vcsSerialBuffer.indexOf ( "t:" );
  vlsiIndexOfEnd         =  ModemATBased::vcsSerialBuffer.indexOf ( "\r\n", vlsiIndexOfStart + 2 );
  
  if ( vlsiIndexOfStart != -1 )
  {
    ModemATBased::Telefon =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart + 2, vlsiIndexOfEnd );
  }
  
  // Se houver um novo id e um novo telefone a eeprom e gravada
  if ( ( ModemATBased::Id.length () > 0 ) && ( ModemATBased::Telefon.length () >= 7 ) )
  {
    writeEepromData ( &kuiEepromAddressId, &ModemATBased::Id );
    writeEepromData ( &kuiEepromAddressTelefon, &ModemATBased::Telefon );
    
    makeEepromRecordedData ();
    Serial.println ( "\r\nDados gravados na EEPROM" );
  }
  
  // m - mensagem para o display
  vlsiIndexOfStart     =  ModemATBased::vcsSerialBuffer.indexOf ( "m:" );
  vlsiIndexOfEnd       =  ModemATBased::vcsSerialBuffer.indexOf ( "\r\n", vlsiIndexOfStart + 2 );
  
  if ( vlsiIndexOfStart != -1 )
  {
    ModemATBased::Data   =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart + 2, vlsiIndexOfEnd );
                            sendMessageToDisplay ( &ModemATBased::Data );
  }
  
  vlsiIndexOfStart     =  ModemATBased::vcsSerialBuffer.indexOf ( "shut-down\r\n" );
  
  if ( vlsiIndexOfStart != -1 )
  {
    PowerLed =  "0";
    shutDownDisplay ( true );
  }
  
  vlsiIndexOfStart     =  ModemATBased::vcsSerialBuffer.indexOf ( "shut-up\r\n" );
  
  if ( vlsiIndexOfStart != -1 )
  {
    PowerLed =  "1";
    shutDownDisplay ( false );
  }
  
  vlsiIndexOfStart     =  ModemATBased::vcsSerialBuffer.indexOf ( "reset-message-id\r\n" );
  
  if ( vlsiIndexOfStart != -1 )
  {
    IdLastMessage      =  "0";
    Serial.println ( "\r\nid da mesg zerado" );
  }
}

void shutDownDisplay ( boolean vlbPowerToDisplay )
{
  if ( vlbPowerToDisplay == true )
  {
    Serial.println ( "\r\nDisplay desligado" );
  }
  
  else
  {
    Serial.println ( "\r\nDisplay ligado" );
  }
}

void sendMessageToDisplay ( String * vastpMessage )
{
  Serial.print ( "\r\nMensagem para o display: " );
  Serial.println ( * vastpMessage );
}

unsigned int StringToUInt ( String vastIntString )
{
  unsigned int vluiNumber       =  0;
  unsigned int vluiMultiplier   =  1;
  byte         vlbtContador     =  0;
  
  while ( vastIntString.charAt ( vlbtContador ) != 0x00 )
  {
    vlbtContador ++;
  }
  
  do
  {
    vluiNumber +=  ( int ( vastIntString.charAt ( -- vlbtContador ) ) - 0x30 ) * vluiMultiplier;
    
    vluiMultiplier *=  10;
    
  }
  while ( vlbtContador != 0x00 );
  
  return vluiNumber;
}

void resetMillis ()
{
  vgulMillis  =  millis ();
}

boolean testMillis ( unsigned long vaulMillis )
{
  if ( millis () < vgulMillis )
  {
    Serial.println ( "milis erro" );
    while(true);
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
  resetMillis ();
  Serial.begin ( 9600 );
  
  ModemATBased::StateMachineEvent = &Evento;
  ModemATBased::setSerial ( SerialPort::Port1, 9600 );
  
  ModemATBased::DataEvent = &onDataEvent;
}

void makeEepromRecordedData ()
{
  const unsigned char * vlucpAddressData =  &kucEepromGravada[0];
        unsigned int    vlucpAddress     =  kuiEepromAddressRecordedData;
        
  do
  {
    
    EEPROM.write ( vlucpAddress, * vlucpAddressData );
    
    vlucpAddressData ++;
    vlucpAddress ++;
    
  } while ( * vlucpAddressData != 0x00 );
  
  EEPROM.write ( vlucpAddress, 0x00 );
}

boolean testEepromRecordedData ()
{
  unsigned int vluiAddress =  kuiEepromAddressRecordedData;
  
  while ( true )
  {
    if ( kucEepromGravada[ vluiAddress ] == 0x00 )
    {
      return true;
    }
    
    else
    {
      if ( EEPROM.read ( vluiAddress ) == kucEepromGravada[ vluiAddress ] )
      {
        vluiAddress ++;
      }
      
      else
      {
        return false;
      }
    }
  }
}

void writeEepromData ( const unsigned int * vauipAddress, String * vastpDara )
{
  unsigned int  vluiEepromAddress =  * vauipAddress;
  byte          vlbtStringAddress =    0;
  
  while ( true )
  {
    if ( (* vastpDara ).charAt ( vlbtStringAddress ) == 0x00 )
    {
      EEPROM.write ( vluiEepromAddress, 0x00 );
      return;
    }
    
    else
    {
      EEPROM.write ( vluiEepromAddress, ( char )(* vastpDara ).charAt ( vlbtStringAddress ) );
    }
    
    vluiEepromAddress ++;
    vlbtStringAddress ++;
  }
}

void readEepromData ( const unsigned int * vauipAddress, String * vastpDara )
{
  unsigned int  vluiEepromAddress =  * vauipAddress;
  byte          vlbtStringAddress =    0;
  
  while ( true )
  {
    if ( EEPROM.read ( vluiEepromAddress ) != 0x00 )
    {
      (* vastpDara ).concat ( ( char ) EEPROM.read ( vluiEepromAddress ++ ) );
    }
    
    else
    {
      (* vastpDara ).concat ( ( char ) EEPROM.read ( vluiEepromAddress ++ ) );
      return;
    }
  }
}

void Evento ( eEvent e, eEvent d )
{
  switch ( e )
  {
    case Event::CallReady:                       resetMillis ();
                                                 ModemATBased::getSignalQuality ();
                                                 break;
                                                 
    case Event::SignalQuality:                   resetMillis ();
                                                 if ( ModemATBased::SignalQualityDbm.equals ( "0" ) )
                                                 {
                                                   ModemATBased::getSignalQuality ();
                                                 }
                                                 
                                                 else
                                                 {
                                                   ModemATBased::QueryString  =  "/modem/modem.php?i=";
                                                   
                                                   if ( testEepromRecordedData () == true )
                                                   {
                                                     ModemATBased::QueryString.concat ( "1" );
                                                     ModemATBased::QueryString.concat ( "&q=" );
                                                     ModemATBased::QueryString.concat ( ModemATBased::SignalQualityDbm );
                                                     ModemATBased::QueryString.concat ( "&la=0&lo=0&s=" );
                                                     ModemATBased::QueryString.concat ( IdLastMessage );
                                                     ModemATBased::QueryString.concat ( "&p=" );
                                                     ModemATBased::QueryString.concat ( PowerLed );
                                                   }
                                                   
                                                   else
                                                   {
                                                     ModemATBased::QueryString.concat ( "-1&q=" );
                                                     ModemATBased::QueryString.concat ( ModemATBased::SignalQualityDbm );
                                                     ModemATBased::QueryString.concat ( "&la=0&lo=0" );
                                                   }
                                                   
                                                   ModemATBased::internetConnect ( kConnectingInternet );
                                                 }
                                                 break;
                                                 
    case Event::InternetConnect:                 Serial.println ( "\r\nEvento: InternetConnect" );
                                                 ModemATBased::Host        =  "kemper.com.br";
                                                 ModemATBased::HostPort    =  "80";
                                                 resetMillis ();
                                                 ModemATBased::internetConnectToHost ( kConnectingHost );
                                                 break;
                                                 
    case Event::InternetConnectToHost:           Serial.println ( "\r\nEvento: connect to host" );
                                                 //ModemATBased::QueryString =  "/modem/modem.php?status=";
                                                 //ModemATBased::QueryString.concat ( String ( contadorLoop, DEC ) );
                                                 resetMillis ();
                                                 ModemATBased::internetDataSendByGET ( kConnectingPage );
                                                 break;
    case Event::Error:
    case Event::ConnectionFailed:                resetMillis ();
                                                 ModemATBased::internetDisconnectToHost ( kError );
                                                 break;
    case Event::Closed:                          
                                                 resetMillis ();
                                                 ModemATBased::internetDisconnectToHost ( kClosed );
                                                 break;
    
                               
                                                 //ModemATBased::internetDisconnectToHost ();
                                                 //delay ( 5000 );
                                                 break;
                                        
    case Event::InternetDisconnectToHost:        resetMillis ();
                                                 switch ( ModemATBased::getUserStatus () )
                                                 {
                                                   case kConnectingInternet: break;
                                                   case kError:              
                                                   case kClosed:             resetMillis ();
                                                                             ModemATBased::getSignalQuality ();
                                                                             break;
                                                   break;
                                                 }
    /*
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
                                                  
    case Event::Closed:                          
    case Event::Close:                           ModemATBased::internetDisconnectToHost ();
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
                                        
    case Event::InternetDisconnectToHost:        if ( d == Event::internetDisconnectToHostFunction )
                                                 {
                                                   Serial.println ( "\r\nEvento: disconnect to host\r" );
                                                   ModemATBased::Id =  "1";
                                                   ModemATBased::readTextSms ();
                                                   break;
                                                 }
    */
  }
}

void loop ()
{
  unsigned char data;
  
  if ( testMillis ( 15000 ) == true )
  {
    Evento ( Event::Error, Event::None );
  }
  
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



//#include "ATList.h"

#include "WProgram.h"
#include "ModemATBased.h"

#include "ATList.h"

void ( * ModemATBased::vcpfOnFunction ) ( void ) =  0;

eSerialPort				ModemATBased::vceSerial;
const String *          ModemATBased::vcacucATString[ 20 ];
const String *          ModemATBased::vcacucATResponse[ 20 ];
int                     ModemATBased::vcacucATDelay[ 20 ];
const String *          ModemATBased::vcucpDataToCompare;
unsigned char			ModemATBased::vcucSMStep;
unsigned char			ModemATBased::vcucSMTotalStep;
unsigned char           ModemATBased::vcucSMStepCompare = 0;
		 char			ModemATBased::vcascPointerDataModem = -1;
String                  ModemATBased::vcsQueryString;

         

ModemATBased::ModemATBased ()
{

}

/** 
 *  
 *  
 *  
 *  
 */
void ModemATBased::setSerial ( eSerialPort vaeSerial )
{
    #ifdef debug_ModemATBased
    Serial.end ();
    Serial.begin ( 19200 );
    #endif
    
	switch ( vaeSerial )
	{
		#ifndef debug_ModemATBased
		case SerialPort::Port0:	Serial.begin ( 19200 );
			break;
		#endif
		#if defined(UBRR1H)
		case SerialPort::Port1:	Serial1.begin ( 19200 );
								
			break;
		#endif
		#if defined(UBRR2H)
		case SerialPort::Port2:	Serial2.begin ( 19200 );
			break;
		#endif
		#if defined(UBRR3H)
		case SerialPort::Port3:	Serial3.begin ( 19200 );
			break;
		#endif
	}
	
	ModemATBased::vceSerial	 =  vaeSerial;
}

/** 
 *  
 *  
 *  
 *  
 */
void ModemATBased::sendData ( String vasData )
{
	switch ( ModemATBased::vceSerial )
	{
		#ifndef debug_ModemATBased
		case SerialPort::Port0:	Serial.print ( vasData );
			break;
		#endif
        
        #if defined(UBRR1H)
        
		case SerialPort::Port1:	Serial1.print ( vasData );
            #ifdef debug_ModemATBased
            Serial.print ( vasData );
            #endif
            
			break;
            
		#endif
        
		#if defined(UBRR2H)
        
		case SerialPort::Port2:	Serial2.print ( vasData );
            #ifdef debug_ModemATBased
            Serial.print ( vasData );
            #endif
            
			break;
            
		#endif
        
		#if defined(UBRR3H)
        
		case SerialPort::Port3:	Serial3.print ( vasData );
            #ifdef debug_ModemATBased
            Serial.print ( vasData );
            #endif
            
			break;
            
		#endif
	}
}

/** 
 *  
 *  
 *  
 *  
 */
int ModemATBased::availableData ( )
{
	switch ( ModemATBased::vceSerial )
	{
		#ifndef debug_ModemATBased
		case SerialPort::Port0:	return ( Serial.available () );
		#endif
		#if defined(UBRR1H)
		case SerialPort::Port1:	return ( Serial1.available () );
		#endif
		#if defined(UBRR2H)
		case SerialPort::Port2:	return ( Serial2.available () );
		#endif
		#if defined(UBRR3H)
		case SerialPort::Port3:	return ( Serial3.available () );
		#endif
	}
}

/** 
 *  
 *  
 *  
 *  
 */
unsigned char ModemATBased::getData ( )
{
    #ifdef debug_ModemATBased
    unsigned char vlucSerialData;
    #endif

    switch ( ModemATBased::vceSerial )
	{
		#ifndef debug_ModemATBased
		case SerialPort::Port0:
        
            return ( ( unsigned char ) Serial.read () );
		
        #endif
        
        #if defined(UBRR1H)
		case SerialPort::Port1:
            
            #ifdef debug_ModemATBased
            
                vlucSerialData   =  ( unsigned char ) Serial1.read ();
                Serial.print ( vlucSerialData );
            
                return ( vlucSerialData );
                
            #endif
            
            #ifndef debug_ModemATBased
            
                return ( ( unsigned char ) Serial1.read () );
                
            #endif
            
        #endif
		
        #if defined(UBRR2H)
		case SerialPort::Port2:
            
            #ifdef debug_ModemATBased
            
                vlucSerialData   =  ( unsigned char ) Serial2.read ();
                Serial.print ( vlucSerialData );
            
                return ( vlucSerialData );
                
            #endif
            
            #ifndef debug_ModemATBased
            
                return ( ( unsigned char ) Serial2.read () );
                
            #endif
            
		#endif
		
        #if defined(UBRR3H)
		case SerialPort::Port3:
            
            #ifdef debug_ModemATBased
            
                vlucSerialData   =  ( unsigned char ) Serial3.read ();
                Serial.print ( vlucSerialData );
            
                return ( vlucSerialData );
                
            #endif
            
            #ifndef debug_ModemATBased
            
                return ( ( unsigned char ) Serial3.read () );
                
            #endif
            
        #endif
	}
}

void ModemATBased::internetConnect ( void ( * vafpExtFuntion ) ( void ) )
{
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_echo_off;
    ModemATBased::vcacucATDelay[ 0 ]     =  0;
    ModemATBased::vcacucATResponse[ 0 ]	 =  &modem_modem_ok;
    
    ModemATBased::vcacucATString[ 1 ]	 =  &modem_ip_single;
    ModemATBased::vcacucATDelay[ 1 ]     =  0;
    ModemATBased::vcacucATResponse[ 1 ]	 =  &modem_modem_ok;
    
    ModemATBased::vcacucATString[ 2 ]	 =  &modem_ip_mode_normal;
    ModemATBased::vcacucATDelay[ 2 ]     =  0;
    ModemATBased::vcacucATResponse[ 2 ]	 =  &modem_modem_ok;
    
    ModemATBased::vcacucATString[ 3 ]	 =  &modem_internet_connect;
    ModemATBased::vcacucATDelay[ 3 ]     =  0;
    ModemATBased::vcacucATResponse[ 3 ]	 =  &modem_modem_ok;
    
    ModemATBased::vcacucATString[ 4 ]	 =  &modem_interner_connect_password;
    ModemATBased::vcacucATDelay[ 4 ]     =  0;
    ModemATBased::vcacucATResponse[ 4 ]	 =  &modem_modem_ok;
    
    ModemATBased::vcacucATString[ 5 ]	 =  &modem_deactive_gprs_dpd;
    ModemATBased::vcacucATDelay[ 5 ]     =  0;
    ModemATBased::vcacucATResponse[ 5 ]	 =  &modem_deactive_gprs_dpd_ok;
    
    ModemATBased::vcpfOnFunction         =  vafpExtFuntion;
    
    ModemATBased::vcucpDataToCompare     =  0;
	ModemATBased::vcucSMStepCompare      =  0;
    ModemATBased::vcucSMStep			 =  0;
	ModemATBased::vcucSMTotalStep		 =  5;
	ModemATBased::vcascPointerDataModem	 = -1;
	ModemATBased::StateMachineRun ();
}

void ModemATBased::internetConnectToHost ( const String * vapsHost, const String * vapsHostPort, void ( * vafpExtFuntion ) ( void ) )
{
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_connect_host_and_port_1of3;
    ModemATBased::vcacucATDelay[ 0 ]     =  0;
    ModemATBased::vcacucATResponse[ 0 ]	 =  0;
    
    ModemATBased::vcacucATString[ 1 ]	 =  vapsHost;
    ModemATBased::vcacucATDelay[ 1 ]     =  0;
    ModemATBased::vcacucATResponse[ 1 ]	 =  0;
    
    ModemATBased::vcacucATString[ 2 ]	 =  &modem_connect_host_and_port_2of3;
    ModemATBased::vcacucATDelay[ 2 ]     =  0;
    ModemATBased::vcacucATResponse[ 2 ]	 =  0;
    
    ModemATBased::vcacucATString[ 3 ]	 =  vapsHostPort;
    ModemATBased::vcacucATDelay[ 3 ]     =  0;
    ModemATBased::vcacucATResponse[ 3 ]	 =  0;
    
    ModemATBased::vcacucATString[ 4 ]	 =  &modem_connect_host_and_port_3of3;
    ModemATBased::vcacucATDelay[ 4 ]     =  0;
    ModemATBased::vcacucATResponse[ 4 ]	 =  &modem_connect_host_and_port_ok;
    
    ModemATBased::vcpfOnFunction         =  vafpExtFuntion;
    
    ModemATBased::vcucpDataToCompare     =   0;
	ModemATBased::vcucSMStepCompare      =   0;
    ModemATBased::vcucSMStep			 =   0;
	ModemATBased::vcucSMTotalStep		 =   4;
	ModemATBased::vcascPointerDataModem	 =  -1;
	ModemATBased::StateMachineRun ();
}

//void ModemATBased::internetGETSend ( const String * vapsHost, const String * vapsHostPort, const String * vapsPathAndQueryString, void ( * vafpExtFuntion ) ( void ) )
void ModemATBased::internetDataSendByGET ( const String * vapsHost, const String * vapsHostPort, const String * vapsPathAndQueryString, void ( * vafpExtFuntion ) ( void ) )
{
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_start_send_data_over_tcp_udp;
    ModemATBased::vcacucATDelay[ 0 ]     =  0;
    ModemATBased::vcacucATResponse[ 0 ]	 =  &modem_sms_text_redy_to_send;
    
    ModemATBased::vcacucATString[ 1 ]	 =  &modem_header_get_send_1of3;
    ModemATBased::vcacucATDelay[ 1 ]     =  0;
    ModemATBased::vcacucATResponse[ 1 ]	 =  0;
    
    ModemATBased::vcacucATString[ 2 ]	 =  &modem_header_get_send_2of3;
    ModemATBased::vcacucATDelay[ 2 ]     =  0;
    ModemATBased::vcacucATResponse[ 2 ]	 =  0;
    
    ModemATBased::vcacucATString[ 3 ]	 =  &modem_header_get_send_3of3;
    ModemATBased::vcacucATDelay[ 3 ]     =  0;
    ModemATBased::vcacucATResponse[ 3 ]	 =  0;//&modem_at_command_general_end_line;
    
    ModemATBased::vcacucATString[ 4 ]	 =  &modem_header_host;
    ModemATBased::vcacucATDelay[ 4 ]     =  0;
    ModemATBased::vcacucATResponse[ 4 ] =  0;
    
    ModemATBased::vcacucATString[ 5 ]	 =  vapsHost;
    ModemATBased::vcacucATDelay[ 5 ]     =  0;
    ModemATBased::vcacucATResponse[ 5 ] =  0;
    
    ModemATBased::vcacucATString[ 6 ]	 =  &modem_at_command_general_end_line;
    ModemATBased::vcacucATDelay[ 6 ]     =  0;
    ModemATBased::vcacucATResponse[ 6 ] =  0;//&modem_at_command_general_end_line;
    
    ModemATBased::vcacucATString[ 7 ]	 =  &modem_heafer_connection_alive;
    ModemATBased::vcacucATDelay[ 7 ]     =  0;
    ModemATBased::vcacucATResponse[ 7 ] =  0;//&modem_at_command_general_end_line;
    
    ModemATBased::vcacucATString[ 8 ]	 =  &modem_header_accept;
    ModemATBased::vcacucATDelay[ 8 ]     =  0;
    ModemATBased::vcacucATResponse[ 8 ] =  0;//&modem_at_command_general_end_line;
    
    ModemATBased::vcacucATString[ 9 ]	 =  &modem_header_connection_close;
    ModemATBased::vcacucATDelay[ 9 ]     =  0;
    ModemATBased::vcacucATResponse[ 9 ] =  0;
    
    ModemATBased::vcacucATString[ 10 ]	 =  &modem_bye;
    ModemATBased::vcacucATDelay[ 10 ]     =  0;
    ModemATBased::vcacucATResponse[ 10 ] =  &modem_bye_ok;
    //
//    ModemATBased::vcacucATString[ 11 ]	 =  &modem_deactive_gprs_dpd;
//    ModemATBased::vcacucATDelay[ 11 ]     =  0;
//    ModemATBased::vcacucATResponse[ 11 ] =  &modem_deactive_gprs_dpd_ok;
    
    ModemATBased::vcpfOnFunction         =  vafpExtFuntion;
    
    ModemATBased::vcucpDataToCompare     =   0;
	ModemATBased::vcucSMStepCompare      =   0;
    ModemATBased::vcucSMStep			 =   0;
	ModemATBased::vcucSMTotalStep		 =  10;
	ModemATBased::vcascPointerDataModem	 =  -1;
	ModemATBased::StateMachineRun ();
}

void ModemATBased::sendTextSms ( const String * vapcucTelefon, const String * vapcucMessage, void ( * vafpExtFuntion ) ( void ) )
{
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_echo_off;
    ModemATBased::vcacucATResponse[ 0 ]	 =  &modem_modem_ok;
    
	ModemATBased::vcacucATString[ 1 ]	 =  &modem_sms_text_mode;
	ModemATBased::vcacucATResponse[ 1 ]	 =  &modem_modem_ok;
    
	ModemATBased::vcacucATString[ 2 ]	 =  &modem_sms_send_confg_1of2;
    ModemATBased::vcacucATResponse[ 2 ]	 =  0;
    
    ModemATBased::vcacucATString[ 3 ]	 =  vapcucTelefon;
    ModemATBased::vcacucATResponse[ 3 ]	 =  0;
    
	ModemATBased::vcacucATString[ 4 ]	 =  &modem_sms_send_confg_2of2;
    ModemATBased::vcacucATResponse[ 4 ]	 =  &modem_sms_text_redy_to_send;
    
	ModemATBased::vcacucATString[ 5 ]	 =  vapcucMessage;
    ModemATBased::vcacucATResponse[ 5 ]	 =  0;
	
	ModemATBased::vcacucATString[ 6 ]	 =  &modem_bye;
	ModemATBased::vcacucATResponse[ 6 ]	 =  &modem_modem_ok;
    
    ModemATBased::vcpfOnFunction         =  vafpExtFuntion;
    
    ModemATBased::vcucpDataToCompare     =  0;
	ModemATBased::vcucSMStepCompare      =  0;
    ModemATBased::vcucSMStep			 =  0;
	ModemATBased::vcucSMTotalStep		 =  6;
	ModemATBased::vcascPointerDataModem	 = -1;
	ModemATBased::StateMachineRun ();
}

void ModemATBased::StateMachineRun ()
{
    /*
    if ( ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ] != 0 )
    {
        Serial.print ( "Res. esp.: " );
        Serial.println ( * ( ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ] ) );
    }
    */
    
//    ModemATBased::sendData ( "\r\nSTEP: " );
//    ModemATBased::sendData ( String ( ModemATBased::vcucSMStep, DEC ) );
//    ModemATBased::sendData ( "\r\n" );
    /*if ( ModemATBased::vcacucATString[ ModemATBased::vcucSMStep ] == 0 )
    {
        ModemATBased::sendData ( "fudeu" );
        while (true);
    }*/
    
    String s = * ( ModemATBased::vcacucATString[ ModemATBased::vcucSMStep ] );
    
    if ( s.equals ( String ( "q" ) ) )
    {
//        Serial.println ( ModemATBased::vcsQueryString );
        Serial.println ("entrou na query string");
        ModemATBased::sendData ( ModemATBased::vcsQueryString );
    }
    else
    {
        ModemATBased::sendData ( * ( ModemATBased::vcacucATString[ ModemATBased::vcucSMStep ] ) );
    }
//    ModemATBased::sendData ( * ( ModemATBased::vcacucATString[ ModemATBased::vcucSMStep ] ) );
    delay ( ModemATBased::vcacucATDelay[ ModemATBased::vcucSMStep ] );
    
    if ( ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ] == 0 )
	{
        if ( ModemATBased::vcucSMStep != ModemATBased::vcucSMTotalStep )
        {
            ModemATBased::vcucSMStep ++;
            ModemATBased::StateMachineRun ();
        }
        
        //ModemATBased::sendData ( "\r\nCOMPARE ZERADO\r\n" );
        
        //ModemATBased::vcucpDataToCompare	 =  0;
	}
	
	else
	{
		ModemATBased::vcascPointerDataModem	 =  0;
        //ModemATBased::sendData ( "\r\nESPERADO: " );
        //ModemATBased::sendData ( *(ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ]) );
        //ModemATBased::sendData ( "\r\n" );
		ModemATBased::vcucpDataToCompare	 =  ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ];
	}
}

void ModemATBased::getDataModem ()
{
	if ( ( ModemATBased::vcascPointerDataModem == -1 ) || ( ModemATBased::vcucpDataToCompare == 0) )
	{
        /*if ( ModemATBased::availableData () )
        {
            //ModemATBased::sendData ( " --> " );
            //ModemATBased::sendData ( ModemATBased::getData () );
        }*/
		//ModemATBased::sendData ( "Entrou aqui - getDataModem lixo" );
        if (Serial1.available())
        Serial.print( (unsigned char)Serial1.read() );
		return;
	}
	
	if ( ModemATBased::availableData () )
	{
        unsigned char vlucSerialData =  ModemATBased::getData ();
        
        /*if ( (*ModemATBased::vcucpDataToCompare) == 0 )
        {
            ModemATBased::sendData ( "fudeu 399" );
            while ( true );
        }
        
        if ( (*ModemATBased::vcucpDataToCompare).length() < ModemATBased::vcucSMStepCompare )
        {
            ModemATBased::sendData ( "fudeu 405" );
            while ( true );
        }*/
        
		if ( vlucSerialData == (unsigned char)(*ModemATBased::vcucpDataToCompare).charAt ( ModemATBased::vcucSMStepCompare ) )
		{
            //ModemATBased::sendData ( "ENTROU 416" );
			ModemATBased::vcucSMStepCompare ++;
            
			if ( (*ModemATBased::vcucpDataToCompare).length () == ModemATBased::vcucSMStepCompare )
			{
                //ModemATBased::sendData ( "ENTROU 421" );
                if ( ModemATBased::vcucSMStep == ModemATBased::vcucSMTotalStep )
                {
                    //ModemATBased::sendData ( "ENTROU 424" );
                    ModemATBased::vcpfOnFunction ();
                }
                else
                {
                    //ModemATBased::sendData ( "ENTROU 429" );
                    ModemATBased::vcucSMStepCompare =  0;
                    ModemATBased::vcucSMStep ++;
                    ModemATBased::StateMachineRun ();
                }
			}
		}
        
        else
        {
            //ModemATBased::sendData ( "ENTROU 439" );
            ModemATBased::vcucSMStepCompare =  0;
        }
	}
}
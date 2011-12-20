//#include "ATList.h"

#include "WProgram.h"
#include "ModemATBased.h"

#include "ATList.h"

void ( * ModemATBased::vcpfOnFunction ) ( void ) =  0;

eSerialPort				ModemATBased::vceSerial;
const String *          ModemATBased::vcacucATString[ 15 ];
const String *          ModemATBased::vcacucATResponse[ 15 ];
const String *          ModemATBased::vcucpDataToCompare;
unsigned char			ModemATBased::vcucSMStep;
unsigned char			ModemATBased::vcucSMTotalStep;
unsigned char           ModemATBased::vcucSMStepCompare = 0;
		 char			ModemATBased::vcascPointerDataModem = -1;


         

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
    ModemATBased::vcacucATResponse[ 0 ]	 =  &modem_modem_ok;
    
    ModemATBased::vcacucATString[ 1 ]	 =  &modem_ip_single;
    ModemATBased::vcacucATResponse[ 1 ]	 =  &modem_modem_ok;
    
    ModemATBased::vcacucATString[ 2 ]	 =  &modem_ip_mode_normal;
    ModemATBased::vcacucATResponse[ 2 ]	 =  &modem_modem_ok;
    
    ModemATBased::vcacucATString[ 3 ]	 =  &modem_internet_connect;
    ModemATBased::vcacucATResponse[ 3 ]	 =  &modem_modem_ok;
    
    ModemATBased::vcacucATString[ 4 ]	 =  &modem_interner_connect_password;
    ModemATBased::vcacucATResponse[ 4 ]	 =  &modem_modem_ok;
    
    ModemATBased::vcacucATString[ 5 ]	 =  &modem_deactive_gprs_dpd;
    ModemATBased::vcacucATResponse[ 5 ]	 =  &modem_deactive_gprs_dpd_ok;
    
    ModemATBased::vcpfOnFunction         =  vafpExtFuntion;
    
	ModemATBased::vcucSMStepCompare      =  0;
    ModemATBased::vcucSMStep			 =  0;
	ModemATBased::vcucSMTotalStep		 =  5;
	ModemATBased::vcascPointerDataModem	 = -1;
	ModemATBased::StateMachineRun ();
}

void ModemATBased::internetGETSend ( const String * vapsHost, const String * vapsHostPort, const String * vapsPathAndQueryString, void ( * vafpExtFuntion ) ( void ) )
{
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_connect_host_and_port_1of3;
    ModemATBased::vcacucATResponse[ 0 ]	 =  0;
    
    ModemATBased::vcacucATString[ 1 ]	 =  vapsHost;
    ModemATBased::vcacucATResponse[ 1 ]	 =  0;
    
    ModemATBased::vcacucATString[ 2 ]	 =  &modem_connect_host_and_port_2of3;
    ModemATBased::vcacucATResponse[ 2 ]	 =  0;
    
    ModemATBased::vcacucATString[ 3 ]	 =  vapsHostPort;
    ModemATBased::vcacucATResponse[ 3 ]	 =  0;
    
    ModemATBased::vcacucATString[ 4 ]	 =  &modem_connect_host_and_port_3of3;
    ModemATBased::vcacucATResponse[ 4 ]	 =  &modem_connect_host_and_port_ok;
    
    ModemATBased::vcacucATString[ 5 ]	 =  &modem_start_send_data_over_tcp_udp;
    ModemATBased::vcacucATResponse[ 5 ]	 =  0;
    
    ModemATBased::vcacucATString[ 6 ]	 =  &modem_header_get_send_1of2;
    ModemATBased::vcacucATResponse[ 6 ]	 =  0;
    
    ModemATBased::vcacucATString[ 7 ]	 =  vapsPathAndQueryString;
    ModemATBased::vcacucATResponse[ 7 ]	 =  0;
    
    ModemATBased::vcacucATString[ 8 ]	 =  &modem_header_get_send_2of2;
    ModemATBased::vcacucATResponse[ 8 ]	 =  0;
    
    ModemATBased::vcacucATString[ 9 ]	 =  &modem_header_host;
    ModemATBased::vcacucATResponse[ 9 ]	 =  0;
    
    ModemATBased::vcacucATString[ 10 ]	 =  vapsHost;
    ModemATBased::vcacucATResponse[ 10 ] =  0;
    
    ModemATBased::vcacucATString[ 11 ]	 =  &modem_at_command_general_end_line;
    ModemATBased::vcacucATResponse[ 11 ] =  0;
    
    ModemATBased::vcacucATString[ 12 ]	 =  &modem_heafer_connection_alive;
    ModemATBased::vcacucATResponse[ 12 ] =  0;
    
    ModemATBased::vcacucATString[ 13 ]	 =  &modem_header_accept;
    ModemATBased::vcacucATResponse[ 13 ] =  0;
    
    ModemATBased::vcacucATString[ 14 ]	 =  &modem_header_connection_close;
    ModemATBased::vcacucATResponse[ 14 ] =  &modem_header_connection_close_ok;
    
    ModemATBased::vcpfOnFunction         =  vafpExtFuntion;
    
	ModemATBased::vcucSMStepCompare      =   0;
    ModemATBased::vcucSMStep			 =   0;
	ModemATBased::vcucSMTotalStep		 =  14;
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
    
	ModemATBased::vcucSMStepCompare      =  0;
    ModemATBased::vcucSMStep			 =  0;
	ModemATBased::vcucSMTotalStep		 =  6;
	ModemATBased::vcascPointerDataModem	 = -1;
	ModemATBased::StateMachineRun ();
}

void ModemATBased::StateMachineRun ()
{
    ModemATBased::sendData ( * ( ModemATBased::vcacucATString[ ModemATBased::vcucSMStep ] ) );
    
    if ( ModemATBased::vcucSMStep == ModemATBased::vcucSMTotalStep )
    {
        ModemATBased::vcpfOnFunction ();
    }
    
    if ( ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ] == 0 )
	{
        if ( ModemATBased::vcucSMStep != ModemATBased::vcucSMTotalStep )
        {
            ModemATBased::vcucSMStep ++;
            ModemATBased::StateMachineRun ();
        }
	}
	
	else
	{
		ModemATBased::vcascPointerDataModem	 =  0;
		ModemATBased::vcucpDataToCompare	 =  ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ];
	}
}

void ModemATBased::getDataModem ()
{
	if ( ModemATBased::vcascPointerDataModem == -1 )
	{
		Serial.print( (unsigned char)Serial1.read() );
		return;
	}
	
	if ( ModemATBased::availableData () )
	{
        unsigned char vlucSerialData =  ModemATBased::getData ();
        
		if ( ( vlucSerialData == (unsigned char)(*ModemATBased::vcucpDataToCompare).charAt ( ModemATBased::vcucSMStepCompare ) ) || ( (unsigned char)(*ModemATBased::vcucpDataToCompare).charAt ( ModemATBased::vcucSMStepCompare ) == kAnyWare ) )
		{
			ModemATBased::vcucSMStepCompare ++;
            
			if ( ( (unsigned char)(*ModemATBased::vcucpDataToCompare).charAt ( ModemATBased::vcucSMStepCompare ) == '\r' ) || ( vlucSerialData == '>' ) )
			{
                if ( vlucSerialData == '>' )
                {
                    delay ( 300 );
                }
                
                ModemATBased::vcucSMStepCompare =  0;
                ModemATBased::vcucSMStep ++;
				ModemATBased::StateMachineRun ();
			}
		}
	}
}
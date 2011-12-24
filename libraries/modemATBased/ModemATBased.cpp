//#include "ATList.h"

#include "WProgram.h"
#include "ModemATBased.h"

#include "ATList.h"

//void ( * ModemATBased::vcpfOnFunction ) ( Event );

ponteiroDeFuncao        ModemATBased::StateMachineEvent =  0;
eSerialPort				ModemATBased::vceSerial;
eEvent                  ModemATBased::vceEvent;
const String *          ModemATBased::vcacucATString[ 11 ];
const String *          ModemATBased::vcacucATResponse[ 11 ];
unsigned char			ModemATBased::vcucSMStep;
unsigned char			ModemATBased::vcucSMTotalStep;
unsigned char           ModemATBased::vcucSMStepCompare = 0;
		 char			ModemATBased::vcascPointerDataModem = -1;
         
unsigned char           ModemATBased::vcucFlagGroup1 =  0xFF;
unsigned char           ModemATBased::vcucFlagGroup2 =  0xFF;

String                  ModemATBased::vcsDadoSerial;

String                  ModemATBased::Host;
String                  ModemATBased::HostPort;
String                  ModemATBased::QueryString;

#ifndef I_do_not_need_to_send_sms_in_my_program

    String                  ModemATBased::Telefon;
    String                  ModemATBased::Message;
    
#endif

ModemATBased::ModemATBased ()
{

}

/** 
 *  
 *  
 *  
 *  
 */
void ModemATBased::setSerial ( eSerialPort vaeSerial, unsigned int vauiSpeed )
{
/*    #ifdef debug_ModemATBased
    Serial.end ();
    Serial.begin ( vauiSpeed );
    #endif*/
    
	switch ( vaeSerial )
	{
		#ifndef debug_ModemATBased
		case SerialPort::Port0:	Serial.begin ( vauiSpeed );
			break;
		#endif
		#if defined(UBRR1H)
		case SerialPort::Port1:	Serial1.begin ( vauiSpeed );
								
			break;
		#endif
		#if defined(UBRR2H)
		case SerialPort::Port2:	Serial2.begin ( vauiSpeed );
			break;
		#endif
		#if defined(UBRR3H)
		case SerialPort::Port3:	Serial3.begin ( vauiSpeed );
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
		/*#ifndef debug_ModemATBased
		case SerialPort::Port0:	Serial.print ( vasData );
			break;
		#endif*/
        
        #if defined(UBRR1H)
        
		case SerialPort::Port1:	Serial1.print ( vasData );
            /*#ifdef debug_ModemATBased
            Serial.print ( vasData );
            #endif*/
            
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
                //Serial.print ( vlucSerialData );
            
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

void ModemATBased::internetConnect ()
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
    
    ModemATBased::vceEvent               =  Event::InternetConnect;
    
	ModemATBased::vcucSMStepCompare      =  0;
    ModemATBased::vcucSMStep			 =  0;
	ModemATBased::vcucSMTotalStep		 =  5;
	ModemATBased::vcascPointerDataModem	 = -1;
	ModemATBased::StateMachineRun ();
}

void ModemATBased::internetDisconnectToHost ()
{
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_deactive_gprs_dpd;
    ModemATBased::vcacucATResponse[ 0 ]  =  &modem_deactive_gprs_dpd_ok;
    
//    ModemATBased::vcpfOnFunction         =  vafpExtFuntion;
    ModemATBased::vceEvent               =  Event::InternetDisconnectToHost;
    
	ModemATBased::vcucSMStepCompare      =   0;
    ModemATBased::vcucSMStep			 =   0;
	ModemATBased::vcucSMTotalStep		 =   1;
	ModemATBased::vcascPointerDataModem	 =  -1;
	ModemATBased::StateMachineRun ();

}

void ModemATBased::internetConnectToHost ()
{
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_connect_host_and_port_1of3;
    ModemATBased::vcacucATResponse[ 0 ]	 =  0;
    
    ModemATBased::vcacucATString[ 1 ]	 =  &modem_header_hostString;
    ModemATBased::vcacucATResponse[ 1 ]	 =  0;
    
    ModemATBased::vcacucATString[ 2 ]	 =  &modem_connect_host_and_port_2of3;
    ModemATBased::vcacucATResponse[ 2 ]	 =  0;
    
    ModemATBased::vcacucATString[ 3 ]	 =  &modem_header_hostPort;
    ModemATBased::vcacucATResponse[ 3 ]	 =  0;
    
    ModemATBased::vcacucATString[ 4 ]	 =  &modem_connect_host_and_port_3of3;
    ModemATBased::vcacucATResponse[ 4 ]	 =  &modem_connect_host_and_port_ok;
    
    ModemATBased::vceEvent               =  Event::InternetConnectToHost;
    
	ModemATBased::vcucSMStepCompare      =   0;
    ModemATBased::vcucSMStep			 =   0;
	ModemATBased::vcucSMTotalStep		 =   4;
	ModemATBased::vcascPointerDataModem	 =  -1;
	ModemATBased::StateMachineRun ();
}

void ModemATBased::internetDataSendByGET ()
{
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_start_send_data_over_tcp_udp;
    ModemATBased::vcacucATResponse[ 0 ]	 =  &modem_sms_text_redy_to_send;
    
    ModemATBased::vcacucATString[ 1 ]	 =  &modem_header_get_send_1of3;
    ModemATBased::vcacucATResponse[ 1 ]	 =  0;
    
    ModemATBased::vcacucATString[ 2 ]	 =  &modem_header_get_send_2of3;
    ModemATBased::vcacucATResponse[ 2 ]	 =  0;
    
    ModemATBased::vcacucATString[ 3 ]	 =  &modem_header_get_send_3of3;
    ModemATBased::vcacucATResponse[ 3 ]	 =  0;
    
    ModemATBased::vcacucATString[ 4 ]	 =  &modem_header_host;
    ModemATBased::vcacucATResponse[ 4 ]  =  0;
    
    ModemATBased::vcacucATString[ 5 ]	 =  &modem_header_hostString;
    ModemATBased::vcacucATResponse[ 5 ]  =  0;
    
    ModemATBased::vcacucATString[ 6 ]	 =  &modem_at_command_general_end_line;
    ModemATBased::vcacucATResponse[ 6 ]  =  0;
    
    ModemATBased::vcacucATString[ 7 ]	 =  &modem_heafer_connection_alive;
    ModemATBased::vcacucATResponse[ 7 ]  =  0;
    
    ModemATBased::vcacucATString[ 8 ]	 =  &modem_header_accept;
    ModemATBased::vcacucATResponse[ 8 ]  =  0;
    
    ModemATBased::vcacucATString[ 9 ]	 =  &modem_header_connection_close;
    ModemATBased::vcacucATResponse[ 9 ]  =  0;
    
    ModemATBased::vcacucATString[ 10 ]	 =  &modem_bye;
    ModemATBased::vcacucATResponse[ 10 ] =  &modem_bye_ok;
    
    ModemATBased::vceEvent               =  Event::InternetDataSendByGET;
    
	ModemATBased::vcucSMStepCompare      =   0;
    ModemATBased::vcucSMStep			 =   0;
	ModemATBased::vcucSMTotalStep		 =  10;
	ModemATBased::vcascPointerDataModem	 =  -1;
	ModemATBased::StateMachineRun ();
}

#ifndef I_do_not_need_to_send_sms_in_my_program

    void ModemATBased::sendTextSms ()
    {
        ModemATBased::vcacucATString[ 0 ]	 =  &modem_echo_off;
        ModemATBased::vcacucATResponse[ 0 ]	 =  &modem_modem_ok;
        
        ModemATBased::vcacucATString[ 1 ]	 =  &modem_sms_text_mode;
        ModemATBased::vcacucATResponse[ 1 ]	 =  &modem_modem_ok;
        
        ModemATBased::vcacucATString[ 2 ]	 =  &modem_sms_send_confg_1of2;
        ModemATBased::vcacucATResponse[ 2 ]	 =  0;
        
        ModemATBased::vcacucATString[ 3 ]	 =  &modem_sms_send_telefon;//vapcucTelefon;
        ModemATBased::vcacucATResponse[ 3 ]	 =  0;
        
        ModemATBased::vcacucATString[ 4 ]	 =  &modem_sms_send_confg_2of2;
        ModemATBased::vcacucATResponse[ 4 ]	 =  &modem_sms_text_redy_to_send;
        
        ModemATBased::vcacucATString[ 5 ]	 =  &modem_sms_send_message;//vapcucMessage;
        ModemATBased::vcacucATResponse[ 5 ]	 =  0;
        
        ModemATBased::vcacucATString[ 6 ]	 =  &modem_bye;
        ModemATBased::vcacucATResponse[ 6 ]	 =  &modem_modem_ok;
        
        ModemATBased::vceEvent               =  Event::SMSSend;
        
        ModemATBased::vcucSMStepCompare      =  0;
        ModemATBased::vcucSMStep			 =  0;
        ModemATBased::vcucSMTotalStep		 =  6;
        ModemATBased::vcascPointerDataModem	 = -1;
        ModemATBased::StateMachineRun ();
    }

#endif

void ModemATBased::StateMachineRun ()
{
    String s = * ( ModemATBased::vcacucATString[ ModemATBased::vcucSMStep ] );
    
    /*
     *  Please note: the Arduino compiler did not make the type conversion 
     *  properly, therefore, an alternative method was used.
     */
    if ( s.equals ( String ( "q" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::QueryString );
    }
    else if ( s.equals ( String ( "h" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::Host );
    }
    else if ( s.equals ( String ( "p" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::HostPort );
    }
    #ifndef I_do_not_need_to_send_sms_in_my_program
        
        else if ( s.equals ( String ( "t" ) ) )
        {
            ModemATBased::sendData ( ModemATBased::Telefon );
        }
        else if ( s.equals ( String ( "m" ) ) )
        {
            ModemATBased::sendData ( ModemATBased::Message );
        }
        
    #endif
    else
    {
        ModemATBased::sendData ( * ( ModemATBased::vcacucATString[ ModemATBased::vcucSMStep ] ) );
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
	}
}

void ModemATBased::clearFlags ()
{
    ModemATBased::vcucFlagGroup1 =  0xFF;
    ModemATBased::vcucFlagGroup2 =  0xFF;
    
    bitClear ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
}

void ModemATBased::getDataModem ()
{
    if ( ModemATBased::availableData () )
    {
        unsigned char vlucSerialData =  ModemATBased::getData ();
        
        if ( ( ( vlucSerialData == '\r' ) || ( vlucSerialData == '\n' ) ) && ( ModemATBased::vcucSMStep == 0 ) )
        {
            clearFlags ();
            return;
        }
        
        /*else if ( ( ( vlucSerialData == '\r' ) || ( vlucSerialData == '\n' ) ) && ( ModemATBased::vcucSMStep != 0 ) )
        {
        
        }*/
        
        else
        {
            // Expected Response
            if ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_expected_response ) == 1 )
            {
                if ( vlucSerialData == (unsigned char)(*ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ]).charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
            
                else
                {
                    bitClear ( ModemATBased::vcucFlagGroup1, leitura_modem_expected_response );
                }
            }
            
            // NO CARRYER
            if ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_no_carrier ) == 1 )
            {
                if ( vlucSerialData == (unsigned char) modem_response_no_carrier.charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    Serial.print( "Reconheceu: " );
                    Serial.println( (unsigned char) modem_response_no_carrier.charAt ( ModemATBased::vcucSMStepCompare ) );
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
                
                else
                {
                    bitClear ( ModemATBased::vcucFlagGroup1, leitura_modem_no_carrier );
                }
            }
            
            // NO DIALTONE
            if ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_no_dialtone ) == 1 )
            {
                if ( vlucSerialData == (unsigned char) modem_response_no_dialtone1.charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
                
                else
                {
                    bitClear ( ModemATBased::vcucFlagGroup1, leitura_modem_no_dialtone );
                }
            }
             
            // NO DIAL TONE
            if ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_no_dial_tone ) == 1 )
            {    
                if ( vlucSerialData == (unsigned char) modem_response_no_dialtone2.charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
                
                else
                {
                    bitClear ( ModemATBased::vcucFlagGroup1, leitura_modem_no_dial_tone );
                }
            }
            
            // NO ANSWER
            if ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_answer ) == 1 )
            {
                if ( vlucSerialData == (unsigned char) modem_response_no_answer.charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
                
                else
                {
                    bitClear ( ModemATBased::vcucFlagGroup1, leitura_modem_answer );
                }
            }
             
            // BUSY
            if ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_busy ) == 1 )
            {
                if ( vlucSerialData == (unsigned char) modem_response_busy.charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
                
                else
                {
                    bitClear ( ModemATBased::vcucFlagGroup1, leitura_modem_busy );
                }
            }
            
            // +CME ERROR
            if ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_cme_error ) == 1 )
            {
                if ( vlucSerialData == (unsigned char) modem_response_cme_error.charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
                
                else
                {
                    bitClear ( ModemATBased::vcucFlagGroup1, leitura_modem_cme_error );
                }
            }
                
            // ERROR
            if ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_error ) == 1 )
            {
                if ( vlucSerialData == (unsigned char) modem_response_error.charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
                
                else
                {
                    bitClear ( ModemATBased::vcucFlagGroup1, leitura_modem_error );
                }
            }
            
            // RING
            if ( bitRead ( ModemATBased::vcucFlagGroup2, leitura_modem_ring ) == 1 )
            {
                if ( vlucSerialData == (unsigned char) modem_response_ring.charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
                
                else
                {
                    Serial.println( "clear bit ring" );
                    bitClear ( ModemATBased::vcucFlagGroup2, leitura_modem_ring );
                }
             }
                
            // NEW SMS
            if ( bitRead ( ModemATBased::vcucFlagGroup2, leitura_modem_new_sms ) == 1 )
            {
                if ( vlucSerialData == (unsigned char) modem_response_sms.charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
                
                else
                {
                    bitClear ( ModemATBased::vcucFlagGroup2, leitura_modem_new_sms );
                }
            }
                
            // CLOSE
            if ( bitRead ( ModemATBased::vcucFlagGroup2, leitura_modem_close ) == 1 )
            {
                if ( vlucSerialData == (unsigned char) modem_response_close.charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
                
                else
                {
                    bitClear ( ModemATBased::vcucFlagGroup2, leitura_modem_close );
                }
            }
                
            // CLOSEED
            if ( bitRead ( ModemATBased::vcucFlagGroup2, leitura_modem_closed ) == 1 )
            {
                if ( vlucSerialData == (unsigned char) modem_response_closed.charAt ( ModemATBased::vcucSMStepCompare ) )
                {
                    bitSet ( ModemATBased::vcucFlagGroup2, leitura_modem_continue );
                }
                
                else
                {
                    bitClear ( ModemATBased::vcucFlagGroup2, leitura_modem_closed );
                }
            }
            
            
            if ( bitRead ( ModemATBased::vcucFlagGroup2, leitura_modem_continue ) == 1 )
            {
                //clearFlags ();
                
                ModemATBased::vcucSMStepCompare ++;
                
                if ( ( (*ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ]).length () == ModemATBased::vcucSMStepCompare ) && ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_expected_response ) == 1 ) )
                {
                    clearFlags ();
                    if ( ModemATBased::vcucSMStep == ModemATBased::vcucSMTotalStep )
                    {
                        if ( ModemATBased::StateMachineEvent != 0 )
                        {
                            ModemATBased::StateMachineEvent ( ModemATBased::vceEvent );
                        }
                    }
                    else
                    {
                        ModemATBased::vcucSMStepCompare =  0;
                        ModemATBased::vcucSMStep ++;
                        ModemATBased::StateMachineRun ();
                    }
                }
                
                if ( ( modem_response_no_carrier.length () == ModemATBased::vcucSMStepCompare ) && ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_no_carrier ) == 1 ) )
                {   
                    Serial.println( "Entrou" );
                    clearFlags ();
                    ModemATBased::vcucSMStepCompare =  0;
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {Serial.println( "Evento" );
                        ModemATBased::StateMachineEvent ( Event::NoCarrier );
                    }
                }
                
                if ( ( modem_response_no_dialtone1.length () == ModemATBased::vcucSMStepCompare ) && ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_no_dialtone ) == 1 ) )
                {
                    clearFlags ();
                    ModemATBased::vcucSMStepCompare =  0;
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::NoDialTone );
                    }
                }
                
                if ( ( modem_response_no_dialtone2.length () == ModemATBased::vcucSMStepCompare ) && ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_no_dialtone ) == 1 ) )
                {
                    clearFlags ();
                    ModemATBased::vcucSMStepCompare =  0;
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::NoDialTone );
                    }
                }
                
                if ( ( modem_response_no_answer.length () == ModemATBased::vcucSMStepCompare ) && ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_answer ) == 1 ) )
                {
                    clearFlags ();
                    ModemATBased::vcucSMStepCompare =  0;
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::NoAnswer );
                    }
                }
                
                if ( ( modem_response_busy.length () == ModemATBased::vcucSMStepCompare ) && ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_busy ) == 1 ) )
                {
                    clearFlags ();
                    ModemATBased::vcucSMStepCompare =  0;
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::Busy );
                    }
                }
                
                if ( ( modem_response_cme_error.length () == ModemATBased::vcucSMStepCompare ) && ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_cme_error ) == 1 ) )
                {
                    clearFlags ();
                    ModemATBased::vcucSMStepCompare =  0;
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::CmeError );
                    }
                }
                
                if ( ( modem_response_error.length () == ModemATBased::vcucSMStepCompare ) && ( bitRead ( ModemATBased::vcucFlagGroup1, leitura_modem_error ) == 1 ) )
                {
                    clearFlags ();
                    ModemATBased::vcucSMStepCompare =  0;
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::Error );
                    }
                }
                
                if ( ( modem_response_ring.length () == ModemATBased::vcucSMStepCompare ) && ( bitRead ( ModemATBased::vcucFlagGroup2, leitura_modem_ring ) == 1 ) )
                {
                    clearFlags ();
                    Serial.println ( bitRead ( ModemATBased::vcucFlagGroup2, leitura_modem_ring ), DEC );
                    ModemATBased::vcucSMStepCompare =  0;
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::Ring );
                    }
                }
                
                if ( ( modem_response_sms.length () == ModemATBased::vcucSMStepCompare ) && bitRead ( ModemATBased::vcucFlagGroup2, leitura_modem_new_sms ) == 1 )
                {
                    clearFlags ();
                    ModemATBased::vcucSMStepCompare =  0;
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::SMSNew );
                    }
                }
                
                if ( ( modem_response_close.length () == ModemATBased::vcucSMStepCompare ) && ( bitRead ( ModemATBased::vcucFlagGroup2, leitura_modem_close ) == 1 ) )
                {
                    clearFlags ();
                    ModemATBased::vcucSMStepCompare =  0;
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::Close );
                    }
                }
                
                if ( ( modem_response_closed.length () == ModemATBased::vcucSMStepCompare ) && ( bitRead ( ModemATBased::vcucFlagGroup2, leitura_modem_closed ) == 1 ) )
                {
                    clearFlags ();
                    ModemATBased::vcucSMStepCompare =  0;
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::Closed );
                    }
                }
            }
            
            else
            {
                ModemATBased::vcucSMStepCompare =  0;
            }
        }
        
        
        /*
        if ( ( ModemATBased::vcascPointerDataModem == -1 ) || ( ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ] == 0) )
        {
        
        }
        
        else if ( vlucSerialData == (unsigned char)(*ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ]).charAt ( ModemATBased::vcucSMStepCompare ) )
		{
			ModemATBased::vcucSMStepCompare ++;
            
			if ( (*ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ]).length () == ModemATBased::vcucSMStepCompare )
			{
                if ( ModemATBased::vcucSMStep == ModemATBased::vcucSMTotalStep )
                {
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( ModemATBased::vceEvent );
                    }
                }
                else
                {
                    ModemATBased::vcucSMStepCompare =  0;
                    ModemATBased::vcucSMStep ++;
                    ModemATBased::StateMachineRun ();
                }
			}
		}
        
        else
        {
            ModemATBased::vcucSMStepCompare =  0;
        }
        */
    }
}
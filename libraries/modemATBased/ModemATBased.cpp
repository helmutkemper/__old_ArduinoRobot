//    Copyright (C) 2012  Helmut Kemper - <helmut.kemper@gmail.com>
//                                        <http:://www.kemper.com.br>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as
//    published by the Free Software Foundation, either version 3 of the
//    License, or (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "ModemATBased.h"

#include "ATList.h"
#include <EEPROM.h>

byte                    ModemATBased::ModemStatus       =  kStandBy;
byte                    ModemATBased::ModemUserStatus   =  0x00;


functionExternalPointer ModemATBased::DataEvent         =  0;
functionPointer         ModemATBased::StateMachineEvent =  0;
eSerialPort				ModemATBased::vceSerial;
eEvent                  ModemATBased::vceEvent;
eEvent                  ModemATBased::vceEventDispatchedBy =  Event::None;
const String *          ModemATBased::vcacucATString[ 11 ];
const String *          ModemATBased::vcacucATResponse[ 11 ];
unsigned char			ModemATBased::vcucSMStep;
unsigned char			ModemATBased::vcucSMTotalStep;
unsigned char           ModemATBased::vcucSMStepCompare = 0;
		 char			ModemATBased::vcascPointerDataModem = -1;
         
unsigned long           ModemATBased::vculFlags =  0xFFFFFFFF;

String                  ModemATBased::Host;
String                  ModemATBased::HostPort;
String                  ModemATBased::HostPage;
String                  ModemATBased::QueryString;
String                  ModemATBased::SignalQualityDbm;
String                  ModemATBased::SignalQualityPercent;

String                  ModemATBased::vcsSerialBuffer =  "";

#ifndef I_do_not_need_to_send_sms_in_my_program

    String              ModemATBased::Id;
    String              ModemATBased::Day;
    String              ModemATBased::Month;
    String              ModemATBased::Year;
    String              ModemATBased::Hour;
    String              ModemATBased::Minute;
    String              ModemATBased::Second;
    String              ModemATBased::Telefon;
    String              ModemATBased::Message;
    String              ModemATBased::Status;
    String              ModemATBased::TimeZone;
    String				ModemATBased::Data;
    
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
		#ifndef debug_ModemATBased
		case SerialPort::Port0:	Serial.print ( vasData );
			break;
		#endif
        
        #if defined(UBRR1H)
        
		case SerialPort::Port1:	Serial1.print ( vasData );
            #ifdef debug_ModemATBased
            Serial.print ( String ( vasData ) );
            #endif
            
			break;
            
		#endif
        
		#if defined(UBRR2H)
        
		case SerialPort::Port2:	Serial2.print ( vasData );
            #ifdef debug_ModemATBased
            Serial.print ( String ( vasData ) );
            #endif
            
			break;
            
		#endif
        
		#if defined(UBRR3H)
        
		case SerialPort::Port3:	Serial3.print ( vasData );
            #ifdef debug_ModemATBased
            Serial.print ( String ( vasData ) );
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
            
                vlucSerialData   =  Serial1.read ();
                Serial.write ( vlucSerialData );
            
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
                Serial.write ( vlucSerialData );
            
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
                Serial.write ( vlucSerialData );
            
                return ( vlucSerialData );
                
            #endif
            
            #ifndef debug_ModemATBased
            
                return ( ( unsigned char ) Serial3.read () );
                
            #endif
            
        #endif
	}
}

void ModemATBased::setUserStatus ( byte vabtStatus )
{
    ModemATBased::ModemUserStatus =  vabtStatus;
}

byte ModemATBased::getUserStatus ()
{
    return ModemATBased::ModemUserStatus;
}

void ModemATBased::internetConnect ( byte vabtStatus )
{
    if ( ( vabtStatus != 0x00 ) && ( vabtStatus != 0xFF ) )
    {
        ModemATBased::ModemUserStatus =  vabtStatus;
    }
    
    else if ( vabtStatus == 0xFF )
    {
        ModemATBased::ModemUserStatus =  0x00;
    }
    
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
    ModemATBased::vceEventDispatchedBy   =  Event::internetConnectFunction;
    
    ModemATBased::ModemStatus            =  kSMRun;
    
	ModemATBased::vcucSMStepCompare      =  0;
    ModemATBased::vcucSMStep			 =  0;
	ModemATBased::vcucSMTotalStep		 =  5;
	ModemATBased::vcascPointerDataModem	 = -1;
    ModemATBased::clearFlags ();
	ModemATBased::StateMachineRun ();
}

void ModemATBased::internetDisconnectToHost ( byte vabtStatus )
{
    if ( ( vabtStatus != 0x00 ) && ( vabtStatus != 0xFF ) )
    {
        ModemATBased::ModemUserStatus =  vabtStatus;
    }
    
    else if ( vabtStatus == 0xFF )
    {
        ModemATBased::ModemUserStatus =  0x00;
    }
    
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_deactive_gprs_dpd;
    ModemATBased::vcacucATResponse[ 0 ]  =  &modem_deactive_gprs_dpd_ok;
    
    ModemATBased::vceEvent               =  Event::InternetDisconnectToHost;
    ModemATBased::vceEventDispatchedBy   =  Event::internetDisconnectToHostFunction;
    
    ModemATBased::ModemStatus            =  kSMRun;
    
	ModemATBased::vcucSMStepCompare      =   0;
    ModemATBased::vcucSMStep			 =   0;
	ModemATBased::vcucSMTotalStep		 =   0;
	ModemATBased::vcascPointerDataModem	 =  -1;
    ModemATBased::clearFlags ();
	ModemATBased::StateMachineRun ();

}

void ModemATBased::internetConnectToHost ( byte vabtStatus )
{
    if ( ( vabtStatus != 0x00 ) && ( vabtStatus != 0xFF ) )
    {
        ModemATBased::ModemUserStatus =  vabtStatus;
    }
    
    else if ( vabtStatus == 0xFF )
    {
        ModemATBased::ModemUserStatus =  0x00;
    }
    
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
    ModemATBased::vceEventDispatchedBy   =  Event::internetConnectToHostFunction;
    
    ModemATBased::ModemStatus            =  kSMRun;
    
	ModemATBased::vcucSMStepCompare      =   0;
    ModemATBased::vcucSMStep			 =   0;
	ModemATBased::vcucSMTotalStep		 =   4;
	ModemATBased::vcascPointerDataModem	 =  -1;
    ModemATBased::clearFlags ();
	ModemATBased::StateMachineRun ();
}

void ModemATBased::internetDataSendByGET ( byte vabtStatus )
{
    if ( ( vabtStatus != 0x00 ) && ( vabtStatus != 0xFF ) )
    {
        ModemATBased::ModemUserStatus =  vabtStatus;
    }
    
    else if ( vabtStatus == 0xFF )
    {
        ModemATBased::ModemUserStatus =  0x00;
    }
    
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
    ModemATBased::vceEventDispatchedBy   =  Event::internetDataSendByGETFunction;
    
    ModemATBased::ModemStatus            =  kSMRun;
    
	ModemATBased::vcucSMStepCompare      =   0;
    ModemATBased::vcucSMStep			 =   0;
	ModemATBased::vcucSMTotalStep		 =  10;
	ModemATBased::vcascPointerDataModem	 =  -1;
    ModemATBased::clearFlags ();
	ModemATBased::StateMachineRun ();
}

#ifndef I_do_not_need_to_send_sms_in_my_program

    void ModemATBased::sendTextSms ( byte vabtStatus )
    {
        if ( ( vabtStatus != 0x00 ) && ( vabtStatus != 0xFF ) )
        {
            ModemATBased::ModemUserStatus =  vabtStatus;
        }
        
        else if ( vabtStatus == 0xFF )
        {
            ModemATBased::ModemUserStatus =  0x00;
        }
        
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
        ModemATBased::vceEventDispatchedBy   =  Event::sendTextSmsFunction;
        
        ModemATBased::ModemStatus            =  kSMRun;
    
        ModemATBased::vcucSMStepCompare      =  0;
        ModemATBased::vcucSMStep			 =  0;
        ModemATBased::vcucSMTotalStep		 =  6;
        ModemATBased::vcascPointerDataModem	 = -1;
        ModemATBased::clearFlags ();
        ModemATBased::StateMachineRun ();
    }
    
    void ModemATBased::readTextSms ( byte vabtStatus )
    {
        if ( ( vabtStatus != 0x00 ) && ( vabtStatus != 0xFF ) )
        {
            ModemATBased::ModemUserStatus =  vabtStatus;
        }
        
        else if ( vabtStatus == 0xFF )
        {
            ModemATBased::ModemUserStatus =  0x00;
        }
        
        ModemATBased::vcacucATString[ 0 ]	 =  &modem_sms_text_mode;
        ModemATBased::vcacucATResponse[ 0 ]	 =  &modem_modem_ok;
        
        ModemATBased::vcacucATString[ 1 ]	 =  &modem_sms_read_message;
        ModemATBased::vcacucATResponse[ 1 ]	 =  0;
        
        ModemATBased::vcacucATString[ 2 ]	 =  &modem_variable_id;
        ModemATBased::vcacucATResponse[ 2 ]	 =  0;
        
        ModemATBased::vcacucATString[ 3 ]	 =  &modem_at_command_general_end_line;
        ModemATBased::vcacucATResponse[ 3 ]	 =  0;
        
        ModemATBased::vceEvent               =  Event::None;
        ModemATBased::vceEventDispatchedBy   =  Event::readTextSmsFunction;
        
        ModemATBased::ModemStatus            =  kSMRun;
    
        ModemATBased::vcucSMStepCompare      =  0;
        ModemATBased::vcucSMStep			 =  0;
        ModemATBased::vcucSMTotalStep		 =  3;
        ModemATBased::vcascPointerDataModem	 = -1;
        ModemATBased::clearFlags ();
        ModemATBased::StateMachineRun ();
    }
    
    void ModemATBased::deleteSmsById ( byte vabtStatus )
    {
        if ( ( vabtStatus != 0x00 ) && ( vabtStatus != 0xFF ) )
        {
            ModemATBased::ModemUserStatus =  vabtStatus;
        }
        
        else if ( vabtStatus == 0xFF )
        {
            ModemATBased::ModemUserStatus =  0x00;
        }
        
        ModemATBased::vcacucATString[ 0 ]	 =  &modem_sms_delete_by_id;
        ModemATBased::vcacucATResponse[ 0 ]	 =  0;
        
        ModemATBased::vcacucATString[ 1 ]	 =  &modem_variable_id;
        ModemATBased::vcacucATResponse[ 1 ]	 =  &modem_modem_ok;
        
        ModemATBased::vceEvent               =  Event::SMSDeleted;
        ModemATBased::vceEventDispatchedBy   =  Event::deleteTextSmsByIdFunction;
        
        ModemATBased::ModemStatus            =  kSMRun;
    
        ModemATBased::vcucSMStepCompare      =  0;
        ModemATBased::vcucSMStep			 =  0;
        ModemATBased::vcucSMTotalStep		 =  1;
        ModemATBased::vcascPointerDataModem	 = -1;
        ModemATBased::clearFlags ();
        ModemATBased::StateMachineRun ();
    }
    
    void ModemATBased::deleteSmsByStatus ( byte vabtStatus )
    {
        if ( ( vabtStatus != 0x00 ) && ( vabtStatus != 0xFF ) )
        {
            ModemATBased::ModemUserStatus =  vabtStatus;
        }
        
        else if ( vabtStatus == 0xFF )
        {
            ModemATBased::ModemUserStatus =  0x00;
        }
        
        ModemATBased::vcacucATString[ 0 ]	 =  &modem_sms_delete_by_status;
        ModemATBased::vcacucATResponse[ 0 ]	 =  0;
        
        ModemATBased::vcacucATString[ 1 ]	 =  &modem_variable_status;
        ModemATBased::vcacucATResponse[ 1 ]	 =  &modem_modem_ok;
        
        ModemATBased::vceEvent               =  Event::SMSDeleted;
        ModemATBased::vceEventDispatchedBy   =  Event::deleteTextSmsByStatusFunction;
        
        ModemATBased::ModemStatus            =  kSMRun;
    
        ModemATBased::vcucSMStepCompare      =  0;
        ModemATBased::vcucSMStep			 =  0;
        ModemATBased::vcucSMTotalStep		 =  1;
        ModemATBased::vcascPointerDataModem	 = -1;
        ModemATBased::clearFlags ();
        ModemATBased::StateMachineRun ();
    }

#endif

void ModemATBased::getCurrentCallNumber ( byte vabtStatus )
{
    if ( ( vabtStatus != 0x00 ) && ( vabtStatus != 0xFF ) )
    {
        ModemATBased::ModemUserStatus =  vabtStatus;
    }
    
    else if ( vabtStatus == 0xFF )
    {
        ModemATBased::ModemUserStatus =  0x00;
    }
    
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_header_carrier_number;
    ModemATBased::vcacucATResponse[ 0 ]	 =  0;
    
    ModemATBased::vceEvent               =  Event::None;
    ModemATBased::vceEventDispatchedBy   =  Event::None;
    
    ModemATBased::ModemStatus            =  kSMRun;
    
    ModemATBased::vcucSMStepCompare      =  0;
    ModemATBased::vcucSMStep			 =  0;
    ModemATBased::vcucSMTotalStep		 =  0;
    ModemATBased::vcascPointerDataModem	 = -1;
    ModemATBased::clearFlags ();
    ModemATBased::StateMachineRun ();
}

void ModemATBased::getSignalQuality ( byte vabtStatus )
{
    if ( ( vabtStatus != 0x00 ) && ( vabtStatus != 0xFF ) )
    {
        ModemATBased::ModemUserStatus =  vabtStatus;
    }
    
    else if ( vabtStatus == 0xFF )
    {
        ModemATBased::ModemUserStatus =  0x00;
    }
    
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_header_signal_quality;
    ModemATBased::vcacucATResponse[ 0 ]	 =  0;//modem_header_signal_quality_response;
    
    ModemATBased::vceEvent               =  Event::None;
    ModemATBased::vceEventDispatchedBy   =  Event::None;
    
    ModemATBased::ModemStatus            =  kSMRun;
    
    ModemATBased::vcucSMStepCompare      =  0;
    ModemATBased::vcucSMStep			 =  0;
    ModemATBased::vcucSMTotalStep		 =  0;
    ModemATBased::vcascPointerDataModem	 = -1;
    ModemATBased::clearFlags ();
    ModemATBased::StateMachineRun ();
}

void ModemATBased::StateMachineRun ()
{
    String s = * ( ModemATBased::vcacucATString[ ModemATBased::vcucSMStep ] );
    
    /*
     *  Please note: the Arduino compiler did not make the type conversion 
     *  properly, therefore, an alternative POG method was used.
     */
    if ( s.equals ( String ( "q" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::QueryString );
    }
    else if ( s.equals ( String ( "H" ) ) )
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
        else if ( s.equals ( String ( "g" ) ) )
        {
            ModemATBased::sendData ( ModemATBased::Message );
        }
        
    #endif
    else if ( s.equals ( String ( "i" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::Id );
    }
    else if ( s.equals ( String ( "d" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::Day );
    }
    else if ( s.equals ( String ( "M" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::Month );
    }
    else if ( s.equals ( String ( "y" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::Year );
    }
    else if ( s.equals ( String ( "h" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::Hour );
    }
    else if ( s.equals ( String ( "m" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::Minute );
    }
    else if ( s.equals ( String ( "s" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::Second );
    }
    else if ( s.equals ( String ( "S" ) ) )
    {
        ModemATBased::sendData ( ModemATBased::Status );
    }
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
    /*
     *  This value refer to modem_read_... consts
     */
    ModemATBased::vculFlags  =  0x00FFFFFF;
    
    bitClear ( ModemATBased::vculFlags, modem_read_continue );
}

void ModemATBased::getDataModem ()
{
    int vlsiIndexOfStart;
    int vlsiIndexOfEnd;
    
    if ( ModemATBased::availableData () )
    {
        unsigned char vlucSerialData =  ModemATBased::getData ();
        
        ModemATBased::vcsSerialBuffer.concat ( char ( ( unsigned char ) vlucSerialData ) );
        
        switch ( ModemATBased::ModemStatus )
        {
            case kSMRun:
            
                if ( ( ModemATBased::vcsSerialBuffer.indexOf ( *ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ] ) != -1 ) && ( ModemATBased::vcacucATResponse[ ModemATBased::vcucSMStep ] != 0 ) )
                {
                    ModemATBased::vcsSerialBuffer =  "";
                    
                    if ( ModemATBased::vcucSMStep == ModemATBased::vcucSMTotalStep )
                    {
                        if ( ModemATBased::StateMachineEvent != 0 )
                        {
                            switch ( ModemATBased::vceEventDispatchedBy )
                            {
                                case Event::internetDataSendByGETFunction:
                                case Event::internetConnectToHostFunction:
                                case Event::internetDisconnectToHostFunction:
                                case Event::internetConnectFunction:
                                
                                    ModemATBased::ModemStatus  =  kInternet;
                                    break;
                                
                                default:    ModemATBased::ModemStatus  =  kStandBy;
                            }
                            
                            ModemATBased::StateMachineEvent ( ModemATBased::vceEvent, ModemATBased::vceEventDispatchedBy );
                        }
                    }
                    else
                    {
                        ModemATBased::vcucSMStepCompare =  0;
                        ModemATBased::vcucSMStep ++;
                        ModemATBased::StateMachineRun ();
                    }
                }
            
            break;
            
            case kStandBy:
            
                if ( ModemATBased::vcsSerialBuffer.endsWith ( "RING\r\n" ) )
                {
                    ModemATBased::vcsSerialBuffer =  "";
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::Ring, ModemATBased::vceEventDispatchedBy );
                    }
                }
                
                if ( ModemATBased::vcsSerialBuffer.indexOf ( "+CMTI: \"SM\"," ) != -1 )
                {
                    ModemATBased::Id              =  ModemATBased::vcsSerialBuffer.substring ( ModemATBased::vcsSerialBuffer.indexOf ( "+CMTI: \"SM\"," ) + 11, ModemATBased::vcsSerialBuffer.indexOf ( "\r\n" ) );
                    ModemATBased::vcsSerialBuffer =  "";
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::SMSNew, ModemATBased::vceEventDispatchedBy );
                    }
                }
                
                /*if ( ( ModemATBased::vcsSerialBuffer.indexOf ( "+CSQ: " ) != -1 ) && ( ModemATBased::vcsSerialBuffer.endsWith ( "\r\nOK\r\n" ) ) )
                {
                    ModemATBased::SignalQualityDbm =  ModemATBased::vcsSerialBuffer.substring ( ModemATBased::vcsSerialBuffer.indexOf ( "+CSQ: " ) + 5, ModemATBased::vcsSerialBuffer.indexOf ( "," ) );
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::SignalQuality, ModemATBased::vceEventDispatchedBy );
                    }
                    ModemATBased::vcsSerialBuffer =  "";
                }*/
                
                if ( ( ModemATBased::vcsSerialBuffer.indexOf ( "+CLCC: " ) != -1 ) && ( ModemATBased::vcsSerialBuffer.endsWith ( "\r\nOK\r\n" ) ) )
                {
                    vlsiIndexOfStart                =  ModemATBased::vcsSerialBuffer.indexOf ( "\"" );
                    vlsiIndexOfEnd                  =  ModemATBased::vcsSerialBuffer.indexOf ( "\"", vlsiIndexOfStart + 1 );
                    
                    ModemATBased::Telefon           =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart, vlsiIndexOfEnd );
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::TelefonCaptured, ModemATBased::vceEventDispatchedBy );
                    }
                    ModemATBased::vcsSerialBuffer   =  "";
                }
                
            break;
            
            case kInternet:
            
                if ( ModemATBased::vcsSerialBuffer.endsWith ( "CLOSE\r\n" ) )
                {
                    ModemATBased::vcsSerialBuffer =  "";
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::Close, ModemATBased::vceEventDispatchedBy );
                    }
                }
                
                if ( ModemATBased::vcsSerialBuffer.endsWith ( "CLOSED\r\n" ) )
                {
                    ModemATBased::vcsSerialBuffer =  "";
                    if ( ModemATBased::StateMachineEvent != 0 )
                    {
                        ModemATBased::StateMachineEvent ( Event::Closed, ModemATBased::vceEventDispatchedBy );
                    }
                }
                /*
                if ( ( ModemATBased::vcsSerialBuffer.indexOf ( "HTTP/" ) != -1 ) && ( ModemATBased::vcsSerialBuffer.endsWith ( "\r\n" ) ) )
                {Serial.println ("\r\nlimpo!");
                    ModemATBased::vcsSerialBuffer =  "";
                }
                
                if ( ( ModemATBased::vcsSerialBuffer.indexOf ( "Server" ) != -1 ) && ( ModemATBased::vcsSerialBuffer.endsWith ( "\r\n" ) ) )
                {Serial.println ("\r\nlimpo!");
                    ModemATBased::vcsSerialBuffer =  "";
                }
                
                if ( ( ModemATBased::vcsSerialBuffer.indexOf ( "Content-Length" ) != -1 ) && ( ModemATBased::vcsSerialBuffer.endsWith ( "\r\n" ) ) )
                {Serial.println ("\r\nlimpo!");
                    ModemATBased::vcsSerialBuffer =  "";
                }
                
                if ( ( ModemATBased::vcsSerialBuffer.indexOf ( "Content-Type" ) != -1 ) && ( ModemATBased::vcsSerialBuffer.endsWith ( "\r\n" ) ) )
                {Serial.println ("\r\nlimpo!");
                    ModemATBased::vcsSerialBuffer =  "";
                }
                
                if ( ( ModemATBased::vcsSerialBuffer.indexOf ( "Cache" ) != -1 ) && ( ModemATBased::vcsSerialBuffer.endsWith ( "\r\n" ) ) )
                {Serial.println ("\r\nlimpo!");
                    ModemATBased::vcsSerialBuffer =  "";
                }
                
                if ( ( ModemATBased::vcsSerialBuffer.indexOf ( "Pragma" ) != -1 ) && ( ModemATBased::vcsSerialBuffer.endsWith ( "\r\n" ) ) )
                {Serial.println ("\r\nlimpo!");
                    ModemATBased::vcsSerialBuffer =  "";
                }
                
                if ( ( ModemATBased::vcsSerialBuffer.indexOf ( "Content-Length:" ) != -1 ) && ( ModemATBased::vcsSerialBuffer.endsWith ( "\r\n" ) ) )
                {Serial.println ("\r\nlimpo!");
                    ModemATBased::vcsSerialBuffer =  "";
                }
                */
                if ( ModemATBased::vcsSerialBuffer.indexOf ( "clear-all" ) != -1 )
                {
                    ModemATBased::vcsSerialBuffer =  "";
                }
                
                if ( ModemATBased::vcsSerialBuffer.indexOf ( "end-data" ) != -1 )
                {
                    if ( ModemATBased::DataEvent != 0 )
                    {
                        ModemATBased::DataEvent ();
                    }
                }
                
            break;
        
        }
        
        if ( ModemATBased::vcsSerialBuffer.endsWith ( "CONNECTION FAILED\r\n" ) )
        {
            ModemATBased::vcsSerialBuffer =  "";
            if ( ModemATBased::StateMachineEvent != 0 )
            {
                ModemATBased::StateMachineEvent ( Event::ConnectionFailed, ModemATBased::vceEventDispatchedBy );
            }
        }
        
        if ( ModemATBased::vcsSerialBuffer.endsWith ( "ERROR\r\n" ) )
        {
            ModemATBased::vcsSerialBuffer =  "";
            if ( ModemATBased::StateMachineEvent != 0 )
            {
                ModemATBased::StateMachineEvent ( Event::Error, ModemATBased::vceEventDispatchedBy );
            }
        }
        
        if ( ModemATBased::vcsSerialBuffer.endsWith ( "Call Ready\r\n" ) )
        {
            ModemATBased::vcsSerialBuffer =  "";
            if ( ModemATBased::StateMachineEvent != 0 )
            {
                ModemATBased::StateMachineEvent ( Event::CallReady, ModemATBased::vceEventDispatchedBy );
            }
        }
        
        if ( ModemATBased::vcsSerialBuffer.endsWith ( "NORMAL POWER DOWN\r\n" ) )
        {
            ModemATBased::vcsSerialBuffer =  "";
            if ( ModemATBased::StateMachineEvent != 0 )
            {
                ModemATBased::StateMachineEvent ( Event::PowerDown, ModemATBased::vceEventDispatchedBy );
            }
        }
        
        if ( ( ModemATBased::vcsSerialBuffer.indexOf ( "+CMGR: " ) != -1 ) && ( ModemATBased::vcsSerialBuffer.indexOf ( "OK" ) != -1 ) )
        {
            vlsiIndexOfStart        =  ModemATBased::vcsSerialBuffer.indexOf ( "\"" );
            vlsiIndexOfEnd          =  ModemATBased::vcsSerialBuffer.indexOf ( "\"", vlsiIndexOfStart + 1 );
            
            ModemATBased::Status    =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart + 1, vlsiIndexOfEnd );
                                                                                
            vlsiIndexOfStart        =  ModemATBased::vcsSerialBuffer.indexOf ( "\",\"" );
            vlsiIndexOfEnd          =  ModemATBased::vcsSerialBuffer.indexOf ( "\",\"", vlsiIndexOfStart + 1 );
            
            ModemATBased::Telefon   =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart + 3, vlsiIndexOfEnd );
            
            vlsiIndexOfStart        =  ModemATBased::vcsSerialBuffer.indexOf ( "/", vlsiIndexOfEnd + 1 );
            
            ModemATBased::Year      =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart -  2, vlsiIndexOfStart -  2 + 2 );
            ModemATBased::Month     =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart +  1, vlsiIndexOfStart +  1 + 2 );
            ModemATBased::Day       =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart +  4, vlsiIndexOfStart +  4 + 2 );
            ModemATBased::Hour      =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart +  7, vlsiIndexOfStart +  7 + 2 );
            ModemATBased::Minute    =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart + 10, vlsiIndexOfStart + 10 + 2 );
            ModemATBased::Second    =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart + 13, vlsiIndexOfStart + 13 + 2 );
            
            vlsiIndexOfStart        =  ModemATBased::vcsSerialBuffer.indexOf ( "\r\n", vlsiIndexOfStart + 13 + 2 );
            vlsiIndexOfEnd          =  ModemATBased::vcsSerialBuffer.length ();
            
            ModemATBased::Message   =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart + 2, vlsiIndexOfEnd - 7 );
            
            if ( ModemATBased::StateMachineEvent != 0 )
            {
                ModemATBased::StateMachineEvent ( Event::SMSRead, ModemATBased::vceEventDispatchedBy );
            }
            
            ModemATBased::vcsSerialBuffer =  "";
        }
        
        if ( ( ModemATBased::vcsSerialBuffer.indexOf ( "+CSQ: " ) != -1 ) && ( ModemATBased::vcsSerialBuffer.indexOf ( "\r\nOK\r\n" ) != -1 ) )
        {
            vlsiIndexOfStart        =  ModemATBased::vcsSerialBuffer.indexOf ( "+CSQ: " );
            vlsiIndexOfEnd          =  ModemATBased::vcsSerialBuffer.indexOf ( ",", vlsiIndexOfStart + 1 );
            
            ModemATBased::SignalQualityDbm =  ModemATBased::vcsSerialBuffer.substring ( vlsiIndexOfStart + 6, vlsiIndexOfEnd );
            
            if ( ModemATBased::StateMachineEvent != 0 )
            {
                ModemATBased::StateMachineEvent ( Event::SignalQuality, ModemATBased::vceEventDispatchedBy );
            }
                
            ModemATBased::vcsSerialBuffer =  "";
        }
        /*
        if ( ModemATBased::vcsSerialBuffer.endsWith ( "NO CARRIER\r\n" ) )
        {
            ModemATBased::vcsSerialBuffer =  "";
            if ( ModemATBased::StateMachineEvent != 0 )
            {
                ModemATBased::StateMachineEvent ( Event::NoCarrier, ModemATBased::vceEventDispatchedBy );
            }
        }
        
        if ( ( ModemATBased::vcsSerialBuffer.endsWith ( "NO DIALTONE\r\n" ) ) || ( ModemATBased::vcsSerialBuffer.endsWith ( "NO DIAL TONE\r\n" ) ) )
        {
            ModemATBased::vcsSerialBuffer =  "";
            if ( ModemATBased::StateMachineEvent != 0 )
            {
                ModemATBased::StateMachineEvent ( Event::NoDialTone, ModemATBased::vceEventDispatchedBy );
            }
        }
        
        if ( ModemATBased::vcsSerialBuffer.endsWith ( "NO ANSWER\r\n" ) )
        {
            ModemATBased::vcsSerialBuffer =  "";
            if ( ModemATBased::StateMachineEvent != 0 )
            {
                ModemATBased::StateMachineEvent ( Event::NoAnswer, ModemATBased::vceEventDispatchedBy );
            }
        }
        
        if ( ModemATBased::vcsSerialBuffer.endsWith ( "BUSY\r\n" ) )
        {
            ModemATBased::vcsSerialBuffer =  "";
            if ( ModemATBased::StateMachineEvent != 0 )
            {
                ModemATBased::StateMachineEvent ( Event::Busy, ModemATBased::vceEventDispatchedBy );
            }
        }
        
        if ( ModemATBased::vcsSerialBuffer.endsWith ( "+CME ERROR\r\n" ) )
        {
            ModemATBased::vcsSerialBuffer =  "";
            if ( ModemATBased::StateMachineEvent != 0 )
            {
                ModemATBased::StateMachineEvent ( Event::CmeError, ModemATBased::vceEventDispatchedBy );
            }
        }
        */
    }
}
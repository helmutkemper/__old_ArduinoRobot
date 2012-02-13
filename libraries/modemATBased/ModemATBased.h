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

#ifndef ModemATBased_h
#define ModemATBased_h

#define debug_ModemATBased

//#define I_do_not_need_to_send_sms_in_my_program
//#define I_do_not_need_to_internet_in_my_program

//#define kTelefon    0x80
//#define kMessage    0x81
//#define kAnyWare    0x82

/*! \brief All Arduino Serial Ports.
 *  Sets the serial port used to communicate with the module.
 *  The UBRRxH are AVR registers used by serial port.
 *  
 *  Define a porta de serial usada para se comunicar com o módulo.
 *  UBRRxH são registros do AVR usados para configurar a porta serial
 *  
 */
namespace SerialPort
{
	enum eSerialPort
	{
		#if defined(UBRR3H)
		Port3,
		#endif
		#if defined(UBRR2H)
		Port2,
		#endif
		#if defined(UBRR1H)
		Port1,
		#endif
		#ifndef debug_sayitmodule
		Port0
		#else
		#warning SayItModule::SerialPort0 is used by debuger. Please, open SayItModule.h and comment line #define debug_sayitmodule 1
		#warning SayItModule::SerialPort0 esta sendo usada pelo debuger. Por favor, abra o arquivo SayItModule.h e comente a linha #define debug_sayitmodule 1
		#endif
	};
}
using namespace SerialPort;

namespace Event
{
    enum eEvent
    {
        None,
        Ring,
        SMSNew,
        SMSSend,
        SMSRead,
        SMSDeleted,
        InternetConnect,
        InternetConnectToHost,
        InternetDataSendByGET,
        InternetDisconnectToHost,
        NoCarrier,
        NoDialTone,
        NoAnswer,
        Busy,
        CmeError,
        Error,
        FatalError,
        Close,
        Closed,
        ConnectionFailed,
        CallReady,
        PowerDown,
        IdCaptured,
        DayCaptured,
        MonthCaptured,
        YearCaptured,
        HourCaptured,
        MinuteCaptured,
        SecondCaptured,
        TelefonCaptured,
        MessageCaptured,
        StatusCaptured,
        TimeZoneCaptured,
        DataCaptured,
        SignalQuality,
        
        TelefonByDataUserCaptured,
        MessageByDataUserCaptured,
        StatusByDataUserCaptured,
        IdByDataUserCaptured,
        DataByDataUserCaptured,
        SignalQualityDbmCaptured,
        SignalQualityPercentCaptured,
        
        internetConnectFunction,
        internetDisconnectToHostFunction,
        internetConnectToHostFunction,
        internetDataSendByGETFunction,
        sendTextSmsFunction,
        readTextSmsFunction,
        deleteTextSmsByIdFunction,
        deleteTextSmsByStatusFunction,
        getSignalQualityFuntion,
        
        GPSData
    };
}
using namespace Event;

extern "C"
{
	typedef void ( * functionPointer )( eEvent, eEvent );
    typedef void ( * functionExternalPointer )();
}

const byte modem_read_expected_response         		=   0;
const byte modem_read_no_carrier                		=   1;
const byte modem_read_no_dialtone               		=   2;
const byte modem_read_no_dial_tone              		=   3;
const byte modem_read_answer                    		=   4;
const byte modem_read_busy                      		=   5;
const byte modem_read_cme_error                 		=   6;
const byte modem_read_error                     		=   7;
const byte modem_read_ring                      		=   8;
const byte modem_read_new_sms                   		=   9;
const byte modem_read_close                     		=  10;
const byte modem_read_closed                    		=  11;
const byte modem_read_connection_failed         		=  12;
const byte modem_read_call_ready                		=  13;
const byte modem_read_normal_power_down         		=  14;
const byte modem_read_continue                  		=  15;
const byte modem_read_sms_read                  		=  16;

const byte modem_read_data								=  17;
const byte modem_read_telefon							=  18;
const byte modem_read_id								=  19;
const byte modem_read_message							=  20;
const byte modem_read_status							=  21;
const byte modem_read_signal_quality                    =  22;
const byte modem_read_ring_telefon                      =  23;

/*
 *  Please, note: change this values, afect "ModemATBased::clearFlags ()"
 */
const byte modem_read_capturing_number_ignore_spaces    =  24;
const byte modem_read_capturing_anything_data			=  25;
const byte modem_read_clear_data                		=  26;
const byte modem_read_capturing_number_started  		=  27;

const byte modem_read_capturing_number_first_element    =  28;
const byte modem_read_capturing_quoted          		=  29;
const byte modem_read_capturing_quoted_started  		=  30;
const byte modem_read_capturing_quoted_ended    		=  31;

const byte kSMRun       =  0x00;
const byte kStandBy     =  0x01;
const byte kInternet    =  0x02;

class ModemATBased
{
	private:
        
//        static void ( * vcpfOnFunction ) ( void );
    
        
        static byte                     ModemStatus;
        static byte                     ModemUserStatus;
		static eSerialPort              vceSerial;
        static eEvent                   vceEvent;
        static eEvent                   vceEventDispatchedBy;
		static const String *           vcacucATString[ 11 ];
		static const String *           vcacucATResponse[ 11 ];
        
		static unsigned char            vcucSMStep;
        static unsigned char            vcucSMStepCompare;
        static unsigned char            vcucSMTotalStep;
        static          char            vcascPointerDataModem;
    
		static void                     sendData ( String vapucData );
		static int                      availableData ( );
		static unsigned char            getData ( );
		static void                     StateMachineRun ();
        static void                     clearFlags ();
        
        
//        static void                   testSpecialCharacter ( unsigned char * vapucSerialData, String * vapstVariable, eEvent vaenEvent );
//        static void                   testCharacterAndRunStateMachine ( unsigned char * vapucSerialData, const String * vapcstsATCommand, const byte * vapcstbtFlagAddress );
//        static void                   testCharacterAndMakeEvent ( unsigned char * vapucSerialData, const String * vapcstsATCommand, const byte * vapcstbtFlagAddress, eEvent vaenEvent );
		
	public:
        
        static String                   vcsSerialBuffer;
        
        static unsigned long            vculFlags;
        
        static functionExternalPointer  DataEvent;
        static functionPointer          StateMachineEvent;
        static String                   Host;
        static String                   HostPage;
        static String                   HostPort;
        static String                   QueryString;
        static String                   Data;
        static String                   SignalQualityDbm;
        static String                   SignalQualityPercent;
        
                                        ModemATBased ();
		static void                     setSerial ( eSerialPort vaeSerial, unsigned int vauiSpeed );
        
        #ifndef I_do_not_need_to_send_sms_in_my_program
        
            static String               Id;
            static String               Day;
            static String               Month;
            static String               Year;
            static String               Hour;
            static String               Minute;
            static String               Second;
            static String               Telefon;
            static String               Message;
            static String               Status;
            static String               TimeZone;
            static void                 sendTextSms ( byte vabtStatus = 0x00 );
            static void                 readTextSms ( byte vabtStatus = 0x00 );
            static void                 deleteSmsById ( byte vabtStatus = 0x00 );
            static void                 deleteSmsByStatus ( byte vabtStatus = 0x00 );
        
        #endif
        
        static void                     internetDataSendByGET ( byte vabtStatus = 0x00 );
        static void                     internetDisconnectToHost ( byte vabtStatus = 0x00 );
        static void                     internetConnectToHost ( byte vabtStatus = 0x00 );
        static void                     internetConnect ( byte vabtStatus = 0x00 );
		static void                     getDataModem ();
        static void                     getSignalQuality ( byte vabtStatus = 0x00 );
        static void                     getCurrentCallNumber ( byte vabtStatus = 0x00 );
        static void                     setUserStatus ( byte vabtStatus );
        static byte                     getUserStatus ();
};

#endif
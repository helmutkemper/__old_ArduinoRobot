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
        
        TelefonByDataUserCaptured,
        MessageByDataUserCaptured,
        StatusByDataUserCaptured,
        IdByDataUserCaptured,
        DataByDataUserCaptured,
        
        internetConnectFunction,
        internetDisconnectToHostFunction,
        internetConnectToHostFunction,
        internetDataSendByGETFunction,
        sendTextSmsFunction,
        readTextSmsFunction
    };
}
using namespace Event;

extern "C"
{
	typedef void ( * ponteiroDeFuncao )( eEvent, eEvent );
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

/*
 *  Please, note: change this values, afect "ModemATBased::clearFlags ()"
 */
const byte modem_read_ignore_spaces_on             		=  24;
const byte modem_read_capturing_anything_data			=  25;
const byte modem_read_clear_data                		=  26;
const byte modem_read_capturing_number_started  		=  27;

const byte modem_read_capturing_number_first_element    =  28;
const byte modem_read_capturing_quoted          		=  29;
const byte modem_read_capturing_quoted_started  		=  30;
const byte modem_read_capturing_quoted_ended    		=  31;

class ModemATBased
{
	private:
	
        static void ( * vcpfOnFunction ) ( void );
    
		static eSerialPort		vceSerial;
        static eEvent           vceEvent;
        static eEvent           vceEventDispatchedBy;
		static const String *	vcacucATString[ 11 ];
		static const String *	vcacucATResponse[ 11 ];
        
		static unsigned char	vcucSMStep;
        static unsigned char    vcucSMStepCompare;
        static unsigned char    vcucSMTotalStep;
        static          char    vcascPointerDataModem;
    
		static void				sendData ( String vapucData );
		static int				availableData ( );
		static unsigned char	getData ( );
		static void				StateMachineRun ();
        static void             clearFlags ();
        
        static void             testSpecialCharacter ( unsigned char * vapucSerialData, String * vapstVariable, eEvent vaenEvent );
        static void             testCharacterAndRunStateMachine ( unsigned char * vapucSerialData, const String * vapcstsATCommand, const byte * vapcstbtFlagAddress );
        static void             testCharacterAndMakeEvent ( unsigned char * vapucSerialData, const String * vapcstsATCommand, const byte * vapcstbtFlagAddress, eEvent vaenEvent );
		
	public:
        
        static unsigned long    vculFlags;
        
        static ponteiroDeFuncao StateMachineEvent;
        static String           Host;
        static String           HostPort;
        static String           QueryString;
        static String           Data;
        
                                ModemATBased ();
		static void				setSerial ( eSerialPort vaeSerial, unsigned int vauiSpeed );
        
        #ifndef I_do_not_need_to_send_sms_in_my_program
        
            static String       Id;
            static String       Day;
            static String       Month;
            static String       Year;
            static String       Hour;
            static String       Minute;
            static String       Second;
            static String       Telefon;
            static String       Message;
            static String       Status;
            static String       TimeZone;
            static void			sendTextSms ();
            static void         readTextSms ();
        
        #endif
        
        static void             internetDataSendByGET ();
        static void             internetDisconnectToHost ();
        static void             internetConnectToHost ();
        static void             internetConnect ();
		static void				getDataModem ();
};

#endif
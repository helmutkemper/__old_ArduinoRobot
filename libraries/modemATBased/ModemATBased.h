#ifndef ModemATBased_h
#define ModemATBased_h

#include "WProgram.h"

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
        Ring,
        SMSNew,
        SMSSend,
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
        ConnectionFailed
    };
}
using namespace Event;

extern "C"
{
	typedef void ( * ponteiroDeFuncao )( eEvent );
}



const byte leitura_modem_expected_response   =  0;
const byte leitura_modem_no_carrier          =  1;
const byte leitura_modem_no_dialtone         =  2;
const byte leitura_modem_no_dial_tone        =  3;
const byte leitura_modem_answer              =  4;
const byte leitura_modem_busy                =  5;
const byte leitura_modem_cme_error           =  6;
const byte leitura_modem_error               =  7;
const byte leitura_modem_ring                =  0;
const byte leitura_modem_new_sms             =  1;
const byte leitura_modem_close               =  2;
const byte leitura_modem_closed              =  3;
const byte leitura_connection_failed         =  4;

const byte leitura_modem_continue            =  7;



class ModemATBased
{
	private:
	
        static void ( * vcpfOnFunction ) ( void );
    
		static eSerialPort		vceSerial;
        static eEvent           vceEvent;
		static const String *	vcacucATString[ 11 ];
		static const String *	vcacucATResponse[ 11 ];
        static String           vcsDadoSerial;
        
		static unsigned char	vcucSMStep;
        static unsigned char    vcucSMStepCompare;
        static unsigned char    vcucSMTotalStep;
        static          char    vcascPointerDataModem;
    
		static void				sendData ( String vapucData );
		static int				availableData ( );
		static unsigned char	getData ( );
		static void				StateMachineRun ();
        static void             clearFlags ();
		
	public:
        
        static unsigned char    vcucFlagGroup1;
        static unsigned char    vcucFlagGroup2;
        
        static ponteiroDeFuncao StateMachineEvent;
        static String           Host;
        static String           HostPort;
        static String           QueryString;
        
                                ModemATBased ();
		static void				setSerial ( eSerialPort vaeSerial, unsigned int vauiSpeed );
        
        #ifndef I_do_not_need_to_send_sms_in_my_program
        
            static String       Telefon;
            static String       Message;
            static void			sendTextSms ();
        
        #endif
        
        static void             internetDataSendByGET ();
        static void             internetDisconnectToHost ();
        static void             internetConnectToHost ();
        static void             internetConnect ();
		static void				getDataModem ();
};

#endif
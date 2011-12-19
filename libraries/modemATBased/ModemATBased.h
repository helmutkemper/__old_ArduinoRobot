#ifndef ModemATBased_h
#define ModemATBased_h

#include "WProgram.h"

/*extern "C"
{
	typedef void (*voidPonteiroDeFuncao)( unsigned char );
}*/

#define debug_ModemATBased 1

#define kTelefon    0x80
#define kMessage    0x81
#define kAnyWare    0x82

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

class ModemATBased
{
	private:
	
		static eSerialPort				vceSerial;
		static const unsigned char *	vcacucATString[ 8 ];
		static const unsigned char *	vcacucATResponse[ 8 ];
		static const unsigned char *	vcucpDataToCompare;
		static unsigned char			vcaucSMStep;
		static unsigned char			vcaucSMTotalStep;
		static			char			vcascPointerDataModem;
    
		static void				sendData ( unsigned char vapucData );
		static int				availableData ( );
		static unsigned char	getData ( );
		static void				sendCommandConstBased ( const unsigned char * vapcucString );
		static void				StateMachineRun ();
        static void             sendCommandExternalPointerBased ( unsigned char * vapucExternalPointer );
		
	public:
		/**  Arquiva o número do telefone usado para envio
         *   
         */
        static const unsigned char *    vcpucTelefone;
        static const unsigned char *    vcpucMessage;
                                
                                ModemATBased ();
		static void				setSerial ( eSerialPort vaeSerial );
		static void				sendTextSms ();
		static void				getDataModem ();
		
};

#endif
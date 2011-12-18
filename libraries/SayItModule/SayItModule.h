#ifndef SayItModule_h
#define SayItModule_h

#include "WProgram.h"
#define Erro				0
#define Reconhecimento		1
#define Livre				2

#define StepRing			5
#define debug_sayitmodule
#define expertMode
#define enLanguageEnglish
//#define enLanguageItalian
//#define enLanguageJapanese
//#define enLanguageGerman
//#define enTimeOutDefault
#define enTimeOutInfinite
//#define enTimeOut10
//#define enTimeOut20
//#define enTimeOut30
#define enRecPreProgrammedTrigger
#define enRecPreProgrammedCommand
#define enRecPreProgrammedDirection
#define enRecPreProgrammedNumber
#define enRecCustomTrigger
#define enRecCustomGroup1
#define enRecCustomGroup2
#define enRecCustomGroup3
#define enRecCustomGroup4
#define enRecCustomGroup5
//#define enRecCustomGroup6
//#define enRecCustomGroup7
//#define enRecCustomGroup8
//#define enRecCustomGroup9
//#define enRecCustomGroup10
//#define enRecCustomGroup11
//#define enRecCustomGroup12
//#define enRecCustomGroup13
//#define enRecCustomGroup14
//#define enRecCustomGroup15
//#define enRecPassword
//#define enFirmwareVersion


//const byte kNumberToASCII[34]	 =  { '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`' };

extern "C"
{
	/** 
	 *  
	 *  
	 *  
	 *  
	 */
	typedef void (*voidPonteiroDeFuncao)( unsigned char );
}

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

namespace CommandList
{
	enum eCommandList
	{
		Free,
		
		FirmwareVersion,
		Break,
		
		setLabelSpeakerDependent,
		
		LanguageEnglish,
		LanguageItalian,
		LanguageJapanese,
		LanguageGerman,
		
		TimeOutDefault,
		TimeOutInfinite,
		TimeOut10,
		TimeOut20,
		TimeOut30,
		
		recPreProgrammedTrigger,
		recPreProgrammedCommand,
		recPreProgrammedDirection,
		recPreProgrammedNumber,
		
		recCustomTrigger,
		recCustomGroup1,
		recCustomGroup2,
		recCustomGroup3,
		recCustomGroup4,
		recCustomGroup5,
		recCustomGroup6,
		recCustomGroup7,
		recCustomGroup8,
		recCustomGroup9,
		recCustomGroup10,
		recCustomGroup11,
		recCustomGroup12,
		recCustomGroup13,
		recCustomGroup14,
		recCustomGroup15,
		recPassword
	};
}
using namespace CommandList;

/** 
 *  Classe para Arduino do módulo Parallax 'SayItModule'.
 *  Para maiores informações sobre o módulo reconhecedor de voz, por favor, visite o site http://www.parallax.com e procure por '30080'.
 *  
 *  Explicação sobre o funcionamento da classe:
 *  
 *  Embora código orientado a objeto seja bom para organizar os dados, a utilização de classes dinâmicas requer um espaço em memória
 *  de dados que a maioria dos µC não pode suportar, por isto, o construtor não é usado e todos os métodos são estáticos. Possibilitando
 *  o melhor da organização de código com o mínimo de uso de memória RAM.
 *  
 *  Quanto ao uso de ponteiros em classes estáticas, na versão atual do compilador Arduino, isto não foi possível, por isto, a classe
 *  reserva cinco bytes em memória RAM para arquivar os passos da máquina de estados.
 *  
 *  
 *  
 *  
 *  
 *  
 *  
 *  
 *  
 *  
 *  
 *  
 */
class SayItModule
{
	private:
		
		/*! \brief Arquiva os ponteiros das funções de reconhecimento, erro e livre.
		 *  
		 *  A máquina de estados pode receber três funções opcionais para os três eventos principais.
		 *  Reconhecimento	-  O módulo reconheceu algum comando vocal;
		 *  Erro			-  Ocorreu algum erro no reconhecimento vocal;
		 *	Livre			-  Todos os passos foram executados e a máquina de estados está parada.
		 */
		static voidPonteiroDeFuncao		vcaFuncoes[ 3 ];
		
		/*! \brief Recebe a sequência de comandos a ser executada.
		 *  
		 *  A sequência fica arquivada no enum eCommandList e o array pode receber no máximo 5 elementos, de acordo com a linha '#define StepRing'.
		 *  Porém, perceba que o último comando deve obrigatoriamente ser 'CommandList::Free'
		 *  Abaixo segue um exemplo de inicialisação correta da máquina de estados.
		 *  { CommandList::Break, CommandList::TimeOutInfinite, CommandList::LanguageEnglish, CommandList::recCustomTrigger, CommandList::Free };
		 *  CommandList::Break				-  Para qualquer reconhecimento em processo. Importante após um reser do sistema;
		 *  CommandList::TimeOutInfinite	-  Faz que o reconhecimento de voz fique indefinidamente;
		 *  CommandList::LanguageEnglish	-  Define uma dos quatro idiomas para o reconhecimento dos comandos de fábrica;
		 *  CommandList::recCustomTrigger	-  Pede o reconhecimento da função de trigger definida pelo usuário;
		 *  CommandList::Free				-  Informa que a máquina de estados terminou de executar todos os passos
		 */
		#ifndef expertMode
		static unsigned char			vceSMStepList[ StepRing ];
		#endif
//		static unsigned char			vcucSMStepIn;
		static unsigned char			vcucSMStepOut;
//		static unsigned char			vcucSMStepError;
		static unsigned char			vcucSMStepSubordinate;
		static boolean					vcbSMStepBusy;
		static eSerialPort				vceSerial;
		
		/*! \brief Envia dados para o módulo
		 *  Todos os comandos enviados ao módulo são da forma de caracteres ASCII imprimíveis.
		 *  
		 *  \param String Object - Veja o manual do módulo para maiores detalhes
		 *  \see setSerial ()
		 *  \see availableData ()
		 */
		static void sendData ( String vasData );
//		static void sendErrorCode ( String vasErroCode );
		
		/*! \brief Equivale a Serial.available ()
		 *  
		 *  Este método escolhe de forma automática qual das portas seriais para ferificar se há dados.
		 */
		static int availableData ( void );
		
		/*! \brief Equivale a Serial.read ()
		 *  
		 *  Este método escolhe de forma automática qual das portas seriais para capturar os dados.
		 *  O grupo Arduino tem uma mania irritante de usar o tipo int, 2 bytes, para tudo, e toda porta serial usa apenas 1 byte
		 *  por isto, este método usa menos recursos de memória.
		 *
		 *  \param void
		 *  \return Dado Serial
		 */
		static unsigned char getData ( void );
		
		/*! \brief Retorna o valor atual do enum.
		 *  
		 *  A classe usa como base um enum 'eCommandList' contendo todos os comandos da maquina de status e usa um array contendo estes 
		 *  comandos para definir a lista de passos a serem seguidos
		 */
//		static unsigned char getStep ( void );
		static void incrementStep ();
		
		
	public:
		
		static unsigned char *vcucpMemory;
		
		SayItModule ( );
		
		static void start ();
		static void run ();
		static void clear ();
		
		/*! \brief Executa o passo atual sem alterar o ponteiro do passo
		 *  
		 *  Este método executa o passo atual e é privado, pois, a máquina de status decide se o passo atual será incrementado ou não 
		 *  de acordo com o evento ocorrido
		 */
		static void execute ( void );
		
		
//		static void setSetupBuffer ( unsigned char * vapucBuffer );
		//static void setStepBuffer ( unsigned char * vapucBuffer );
		static void setSerial ( eSerialPort vaeSerial );
		static void executeEventFunction ( unsigned char vaucType, unsigned char vaucIndex );
		static void defineEventFunction ( void ( * vafpExtFuntion ) ( unsigned char ), unsigned char vaucType );
		static void setLabelSpeakerDependent ( unsigned char vaucGroup, unsigned char vaucPosition, unsigned char vaucLength, unsigned char * vapucBuffer );
		
		static void setGroup ( eCommandList vaeGroup );
};

#endif
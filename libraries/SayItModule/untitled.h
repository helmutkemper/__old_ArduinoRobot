/*
#include "SayItModule.h"

//SayItModule SayItModule ();

void setup ()
{
	SayItModule::setSerial ( PortaSerial::Porta0 );
}

void loop () {}
*/









const byte STM_CONTAGEM_SIMPLES                  =  255;
const byte STM_CONTAGEM_GRUPO_PRE                =  253;
const byte STM_CONTAGEM_SIMPLES_COM_PADRAO       =  252;
const byte STM_CONTAGEM_SIMPLES_COM_PONTEIRO     =  251;
const byte STM_CONTAGEM_DUPLA                    =  250;
const byte STM_END                               =  0;

const byte STS_MASK                   =  'k';
const byte STS_COUNT                  =  'c';
const byte STS_AWAKEN                 =  'w';
const byte STS_DATA                   =  'd';
const byte STS_ERROR                  =  'e';
const byte STS_INVALID                =  'v';
const byte STS_TIMEOUT                =  't';
const byte STS_INTERR                 =  'i';
const byte STS_SUCCESS                =  'o';
const byte STS_RESULT                 =  'r';
const byte STS_SIMILAR                =  's';
const byte STS_OUT_OF_MEM             =  'm';
const byte STS_ID                     =  'x';

const byte PRM_OPCAO[34]              =  { '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 0 };

const byte PRM_IDIOMA_INGLES          =  'A';
const byte PRM_IDIOMA_ITALIANO        =  'B';
const byte PRM_IDIOMA_JAPONES         =  'C';
const byte PRM_IDIOMA_ALEMAO          =  'D';

byte vgbSendAcaoNecessaria;
byte teste = 1;

void dadosMontar ( const byte *vapbComando, const byte *vapbResposta, const byte *vapbParametros )
{
	boolean vlboContinua = true;
	
	byte vlbContadorEnvio   =  0;
	byte vlbEnviar;
	
	do
	{
		if ( vlbContadorEnvio == 0 )
		{
			dadosEnviar ( vapbComando );
		}
		else
		{
			switch ( *vapbParametros )
			{
				case STM_CONTAGEM_SIMPLES:
				case STM_CONTAGEM_GRUPO_PRE:
					
				case STM_CONTAGEM_SIMPLES_COM_PADRAO:
					
					/*
					 *  Testa se o dado a ser enviado e maior ou igual ao valor minimo e menor ou igual ao valor maximo
					 *  Caso contrario acusa o erro
					 */
					if ( *( vapbParametros + 1 ) >= *( vapbParametros + 3 ) && *( vapbParametros + 2 ) <= *( vapbParametros + 3 ) )
					{
						dadosEnviar ( ( byte * ) &PRM_OPCAO[ *( vapbParametros + 3 ) ] );
					}
					else
					{
						// erroEnviar ();
					}
					
					vlboContinua =  false;
					
					break;
					
				case STM_CONTAGEM_SIMPLES_COM_PONTEIRO:
					
					if ( *( vapbParametros + 1 ) >= *( vapbParametros + 3 ) && *( vapbParametros + 2 ) <= *( vapbParametros + 3 ) )
					{
						dadosEnviar ( ( byte * ) &PRM_OPCAO[ *( vapbParametros + 3 ) ] );
					}
					else
					{
						// erroEnviar ();
					}
					
					vlboContinua =  false;
					
				case STM_CONTAGEM_DUPLA:
					break;
				default:
				{
					Serial.println ( "default" );
				}
			}
		}
		
		vlbContadorEnvio++;
		
	} while ( vlboContinua );
	while(true){}
}

void dadosEnviar ( const byte *vapbDado )
{
	Serial.print ( *vapbDado );
}

// Wake-up, na verdade, acontece quando um byte qualquer e recebido pela porta serial e deve ser a primeira coisa enviada, antes de qualquer comando inicial
const byte CMD_WAKEUP                =  'w';
const byte CMD_WAKEUP_OK[2]          =  { STS_AWAKEN, STM_END };
const byte CMD_WAKEUP_PARAM[1]       =  { STM_END };

// Para um reconhecimento em progresso
const byte CMD_BREAK                 =  'b';
const byte CMD_BREAK_OK[3]           =  { STS_SUCCESS, STS_INTERR, STM_END };
const byte CMD_BREAK_PARAM[1]        =  { STM_END };

// O manual nao fala sobre os niveis de sleep
const byte CMD_SLEEP                 =  's';
const byte CMD_SLEEP_OK[2]           =  { STS_SUCCESS, STM_END };
const byte CMD_SLEEP_PARAM[4]        =  { STM_CONTAGEM_SIMPLES_COM_PADRAO, 1, 9, 1 };

// Define o ganho do MIC.
const byte CMD_KNOB                  =  'k';
const byte CMD_KNOB_OK[2]            =  { STS_SUCCESS, STM_END };
const byte CMD_KNOB_PARAM[4]         =  { STM_CONTAGEM_SIMPLES_COM_PADRAO, 1, 5, 1 };

// Fez a placa travar!
// const byte CMD_LEVEL                 =  'v';
// const byte CMD_LEVEL_OK[2]           =  { STS_SUCCESS, 0 };

// Seleciona o idioma do reconhecimento
// 1 INGLES, 2 ITALIANO, 3 JAPONES, 4 ALEMAO
const byte CMD_LANGUAGE              =  'l';
const byte CMD_LANGUAGE_OK[2]        =  { STS_SUCCESS, STM_END };
//const byte CMD_LANGUAGE_PARAM[4]     =  { STM_CONTAGEM_SIMPLES_COM_PADRAO, 1, 4, 1 };
const byte CMD_LANGUAGE_PARAM[4]     =  { STM_CONTAGEM_SIMPLES_COM_PONTEIRO, 1, 4,  (&teste) };

// Define o tempo de espera para o reconhecimento
// 0 default, 1 infinito, 2-32 define de 0 a 30 segundos de espera
const byte CMD_TIMEOUT               =  'o';
const byte CMD_TIMEOUT_OK[2]         =  { STS_SUCCESS, STM_END };
const byte CMD_TIMEOUT_PARAM[4]      =  { STM_CONTAGEM_SIMPLES_COM_PADRAO, 0, 32, 1 };

// Define qual lista de comandos pre programados usar ( valor retornado )
// 0 - robot ( A )
// 1 - action ( A ), move ( B ), tun ( C ), run ( D ), look ( E ), attack ( F ), stop ( G ), hello ( H )
// 2 - left ( A ), right ( B ), up ( C ), down ( D ), forward ( E ), backward ( F )
// 3 - zero ( A ), one ( B ), two ( C ), three ( D ), four ( E ), five ( F ), six ( G ), seven ( H ), eight ( I ), nine ( J ), ten ( K )
const byte CMD_RECOG_SI              =  'i';
const byte CMD_RECOG_SI_OK[4]        =  { STS_SUCCESS, STS_TIMEOUT, STS_ERROR, STM_END };
const byte CMD_RECOG_SI_PARAM[3]     =  { STM_CONTAGEM_GRUPO_PRE, 1, 4 };

// nao testado
// const byte CMD_TRAIN_SD              =  't';
// const byte CMD_TRAIN_SD_OK[6]        =  { STS_SUCCESS, STS_RESULT, STS_SIMILAR, STS_TIMEOUT, STS_ERROR, 0 };
// const byte CMD_TRAIN_SD_PARAM[3]     =  { STM_CONTAGEM_SIMPLES, 1, 4 };

// nao testado
// const byte CMD_GROUP_SD              =  'g';
// const byte CMD_GROUP_SD_OK[3]        =  { STS_SUCCESS, STS_OUT_OF_MEM, 0 };
// const byte CMD_GROUP_SD_PARAM[3]     =  

// nao testado
// const byte CMD_UNGROUP_SD            =  'u';
// const byte CMD_UNGROUP_SD_OK[2]      =  { STS_SUCCESS, 0 };

// nao testado
// const byte CMD_RECOG_SD              =  'd';
// const byte CMD_RECOG_SD_OK[2]        =  { STS_SUCCESS, 0 };

// nao testado
// const byte CMD_ERASE_SD              =  'e';
// const byte CMD_ERASE_SD_OK[2]        =  { STS_SUCCESS, 0 };

// nao testado
// const byte CMD_NAME_SD               =  'n';
// const byte CMD_NAME_SD_OK[2]         =  { STS_SUCCESS, 0 };

// nao testado
// const byte CMD_COUNT_SD              =  'c';
// const byte CMD_COUNT_SD_OK[2]        =  { STS_COUNT, 0 };

// nao testado
// const byte CMD_DUMP_SD               =  'p';
// const byte CMD_DUMP_SD_OK[2]         =  { STS_DATA, 0 };

// nao testado
// const byte CMD_MASK_SD               =  'm';
// const byte CMD_MASK_SD_OK[2]         =  { STS_MASK, 0 };

// nao testado
// const byte CMD_RESSETALL             =  'r';
// const byte CMD_RESSETALL_OK[2]       =  { STS_SUCCESS, 0 };

/**
 *  Retorna uma letra maiuscula que representa o ID do firmware
 */
const byte CMD_CMD_ID                =  'x';
const byte CMD_CMD_ID_OK[2]          =  { STS_ID, STM_END };
const byte CMD_CMD_ID_PARAM[2]       =  { ' ', STM_END };

const byte CMD_DELAY                 =  'y';
const byte CMD_DELAY_OK[2]           =  { STS_SUCCESS, STM_END };

const byte CMD_BAUDRATE              =  'a';
const byte CMD_BAUDRATE_OK[2]        =  { STS_SUCCESS, STM_END };

void setup ()
{
	Serial.begin ( 9600 );
	Serial.println ( "inicio" );
	dadosMontar ( (byte *) &CMD_LANGUAGE, (byte *) &CMD_LANGUAGE_OK, (byte *) &CMD_LANGUAGE_PARAM );
	Serial.println ( "fim" );
}

void loop ()
{
	
}
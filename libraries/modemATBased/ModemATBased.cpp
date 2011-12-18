//#include "ATList.h"

#include "WProgram.h"
#include "ModemATBased.h"

#include "ATList.h"

eSerialPort				ModemATBased::vceSerial;
const unsigned char *	ModemATBased::vcacucATString[ 8 ];
const unsigned char *	ModemATBased::vcacucATResponse[8];
const unsigned char *	ModemATBased::vcucpDataToCompare;
unsigned char			ModemATBased::vcaucATEndLine[ 8 ];
unsigned char			ModemATBased::vcaucSMStep;
unsigned char			ModemATBased::vcaucSMTotalStep;
		 char			ModemATBased::vcascPointerDataModem;


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
void ModemATBased::sendData ( unsigned char vaucData )
{
	switch ( ModemATBased::vceSerial )
	{
		#ifndef debug_ModemATBased
		case SerialPort::Port0:	Serial.print ( vaucData );
			break;
		#endif
		#if defined(UBRR1H)
		case SerialPort::Port1:	Serial1.print ( vaucData );
			break;
		#endif
		#if defined(UBRR2H)
		case SerialPort::Port2:	Serial2.print ( vaucData );
			break;
		#endif
		#if defined(UBRR3H)
		case SerialPort::Port3:	Serial3.print ( vaucData );
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
	switch ( ModemATBased::vceSerial )
	{
		#ifndef debug_ModemATBased
		case SerialPort::Port0:	return ( ( unsigned char ) Serial.read () );
		#endif
		#if defined(UBRR1H)
		case SerialPort::Port1:	return ( ( unsigned char ) Serial1.read () );
		#endif
		#if defined(UBRR2H)
		case SerialPort::Port2:	return ( ( unsigned char ) Serial2.read () );
		#endif
		#if defined(UBRR3H)
		case SerialPort::Port3:	return ( ( unsigned char ) Serial3.read () );
		#endif
	}
}

void ModemATBased::sendTextSms ( const unsigned char * vapucNumber, const unsigned char * vapucMessage )
{
	ModemATBased::vcacucATString[ 0 ]	 =  &modem_at_plus[ 0 ];
	ModemATBased::vcaucATEndLine[ 0 ]	 =  0;
	
	ModemATBased::vcacucATString[ 1 ]	 =  &modem_sms_text_mode[ 0 ];
	ModemATBased::vcacucATResponse[ 1 ]	 =  &modem_modem_ok[ 0 ];
	ModemATBased::vcaucATEndLine[ 1 ]	 =  1;
	
	ModemATBased::vcacucATString[ 2 ]	 =  &modem_at_plus[ 0 ];
	ModemATBased::vcaucATEndLine[ 2 ]	 =  0;
	
	ModemATBased::vcacucATString[ 3 ]	 =  &modem_sms_send_1of2[ 0 ];
	ModemATBased::vcaucATEndLine[ 3 ]	 =  0;
	
	ModemATBased::vcacucATString[ 4 ]	 =  vapucNumber;
	ModemATBased::vcaucATEndLine[ 4 ]	 =  0;
	
	ModemATBased::vcacucATString[ 5 ]	 =  &modem_sms_send_2of2[ 0 ];
	ModemATBased::vcacucATResponse[ 5 ]	 =  &modem_modem_ok[ 0 ];
	ModemATBased::vcaucATEndLine[ 5 ]	 =  1;
	
	ModemATBased::vcacucATString[ 6 ]	 =  vapucMessage;
	ModemATBased::vcaucATEndLine[ 6 ]	 =  0;
	
	ModemATBased::vcacucATString[ 7 ]	 =  &modem_bye[ 0 ];
	ModemATBased::vcacucATResponse[ 7 ]	 =  &modem_modem_ok[ 0 ];
	ModemATBased::vcaucATEndLine[ 7 ]	 =  1;
	
	ModemATBased::vcaucSMStep			 =  0;
	ModemATBased::vcaucSMTotalStep		 =  7;
	ModemATBased::vcascPointerDataModem	 = -1;
	ModemATBased::StateMachineRun ();
}

void ModemATBased::StateMachineRun ()
{
	ModemATBased::sendCommandConstBased ( ModemATBased::vcacucATString[ ModemATBased::vcaucSMStep ], ModemATBased::vcaucATEndLine[ ModemATBased::vcaucSMStep ] );
	
	if ( ( ModemATBased::vcaucSMStep != ModemATBased::vcaucSMTotalStep ) && ( ModemATBased::vcaucATEndLine[ ModemATBased::vcaucSMStep ] == 0 ) )
	{
		ModemATBased::vcaucSMStep ++;
		ModemATBased::StateMachineRun ();
	}
	
	else
	{
		ModemATBased::vcascPointerDataModem	 =  0;
		ModemATBased::vcucpDataToCompare	 =  ModemATBased::vcacucATResponse[ ModemATBased::vcaucSMStep ];
	}
}

void ModemATBased::sendCommandConstBased ( const unsigned char * vapcucString, unsigned char vaucEndLine )
{
	while ( * vapcucString != 0x00 )
	{
		ModemATBased::sendData ( * vapcucString );
		vapcucString ++;
	}
	
	while ( vaucEndLine != 0 )
	{
		ModemATBased::sendData ( '\r' );
		ModemATBased::sendData ( '\n' );
		vaucEndLine --;
	}
}

void ModemATBased::getDataModem ()
{
	//const unsigned char *teste;
	
	if ( ModemATBased::vcascPointerDataModem == -1 )
	{
		Serial.flush();
		return;
	}
	
	if ( ModemATBased::availableData () )
	{
		unsigned char lixo = ModemATBased::getData ();
//		teste = ModemATBased::vcacucATResponse[ ModemATBased::vcaucSMStep ];
		Serial.print ( "recebeu: " );
		Serial.println ( lixo );
		
		Serial.print ( "testou: " );
		Serial.println ( (unsigned char)(*ModemATBased::vcucpDataToCompare) );
		
		
		
		if ( lixo == (unsigned char)(*ModemATBased::vcucpDataToCompare) )
		{
			ModemATBased::vcucpDataToCompare ++;
			
			if ( (unsigned char)(*ModemATBased::vcucpDataToCompare) == 0x00 )
			{
				ModemATBased::vcaucSMStep ++;
				ModemATBased::StateMachineRun ();
			}
		}
	}
}
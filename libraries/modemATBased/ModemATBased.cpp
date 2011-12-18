//#include "ATList.h"

#include "WProgram.h"
#include "ModemATBased.h"

#include "ATList.h"

eSerialPort		ModemATBased::vceSerial;
const unsigned char * ModemATBased::vcacucATString[ 8 ];
unsigned char ModemATBased::vcaucATEndLine[ 8 ];

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

void ModemATBased::sendTextSms ( unsigned char * vapucNumber, unsigned char * vapucMessage )
{
	ModemATBased::vcacucATString[ 0 ]	 =  &modem_at_plus[ 0 ];
	ModemATBased::vcaucATEndLine[ 0 ]	 =  0;
	
	ModemATBased::vcacucATString[ 1 ]	 =  &modem_sms_text_mode[ 0 ];
	ModemATBased::vcaucATEndLine[ 1 ]	 =  1;
	
	ModemATBased::vcacucATString[ 2 ]	 =  &modem_at_plus[ 0 ];
	ModemATBased::vcaucATEndLine[ 2 ]	 =  0;
	
	ModemATBased::vcacucATString[ 3 ]	 =  &modem_sms_send_1of2[ 0 ];
	ModemATBased::vcaucATEndLine[ 3 ]	 =  0;
	
	ModemATBased::vcacucATString[ 4 ]	 =  ( const unsigned char * ) vapucNumber;
	ModemATBased::vcaucATEndLine[ 4 ]	 =  0;
	
	ModemATBased::vcacucATString[ 5 ]	 =  &modem_sms_send_2of2[ 0 ];
	ModemATBased::vcaucATEndLine[ 5 ]	 =  1;
	
	ModemATBased::vcacucATString[ 6 ]	 =  ( const unsigned char * ) vapucMessage;
	ModemATBased::vcaucATEndLine[ 6 ]	 =  0;
	
	ModemATBased::vcacucATString[ 7 ]	 =  &modem_bye[ 0 ];
	ModemATBased::vcaucATEndLine[ 7 ]	 =  1;
	
	ModemATBased::StateMachineRun ( 8 );
}

void ModemATBased::StateMachineRun ( unsigned char vaucLength )
{
	for ( unsigned char vlucContador = 0; vlucContador != ( vaucLength + 1 ); vlucContador ++ )
	{
		ModemATBased::sendCommandConstBased ( ModemATBased::vcacucATString[ vlucContador ], ModemATBased::vcaucATEndLine[ vlucContador ] );
	}
}

void ModemATBased::sendCommandConstBased ( const unsigned char * vapcucString, unsigned char vaucEndLine )
{
	while ( * vapcucString != 0x00 )
	{
		ModemATBased::sendData ( ( unsigned char ) * vapcucString );
		vapcucString ++;
	}
	
	while ( vaucEndLine )
	{
		ModemATBased::sendData ( '\r' );
		ModemATBased::sendData ( '\n' );
		vaucEndLine --;
	}
}
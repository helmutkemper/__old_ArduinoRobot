//#include "ATList.h"

#include "WProgram.h"
#include "ModemATBased.h"

#include "ATList.h"

eSerialPort				ModemATBased::vceSerial;
const unsigned char *	ModemATBased::vcacucATString[ 8 ];
const unsigned char *	ModemATBased::vcacucATResponse[8];
const unsigned char *	ModemATBased::vcucpDataToCompare;
unsigned char			ModemATBased::vcaucSMStep;
unsigned char			ModemATBased::vcaucSMTotalStep;
		 char			ModemATBased::vcascPointerDataModem = -1;
const unsigned char *   ModemATBased::vcpucTelefone;
const unsigned char *   ModemATBased::vcpucMessage;

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
    #ifdef debug_ModemATBased
    Serial.end ();
    Serial.begin ( 19200 );
    #endif
    
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
            #ifdef debug_ModemATBased
            Serial.print ( vaucData );
            #endif
            
			break;
            
		#endif
        
		#if defined(UBRR2H)
        
		case SerialPort::Port2:	Serial2.print ( vaucData );
            #ifdef debug_ModemATBased
            Serial.print ( vaucData );
            #endif
            
			break;
            
		#endif
        
		#if defined(UBRR3H)
        
		case SerialPort::Port3:	Serial3.print ( vaucData );
            #ifdef debug_ModemATBased
            Serial.print ( vaucData );
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
                Serial.print ( vlucSerialData );
            
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

void ModemATBased::sendTextSms ()
{
    ModemATBased::vcacucATString[ 0 ]	 =  &modem_echo_off[ 0 ];
    ModemATBased::vcacucATResponse[ 0 ]	 =  &modem_modem_ok[ 0 ];
    
    ModemATBased::vcacucATString[ 1 ]	 =  &modem_at_plus[ 0 ];
	ModemATBased::vcacucATResponse[ 1 ]	 =  0;
	
	ModemATBased::vcacucATString[ 2 ]	 =  &modem_sms_text_mode[ 0 ];
	ModemATBased::vcacucATResponse[ 2 ]	 =  &modem_modem_ok[ 0 ];
	
	ModemATBased::vcacucATString[ 3 ]	 =  &modem_at_plus[ 0 ];
    ModemATBased::vcacucATResponse[ 3 ]	 =  0;
	
	ModemATBased::vcacucATString[ 4 ]	 =  &modem_sms_send_confg[ 0 ];
    ModemATBased::vcacucATResponse[ 4 ]	 =  &modem_sms_text_redy_to_send[ 0 ];

	ModemATBased::vcacucATString[ 5 ]	 =  &modem_sms_send_text[ 0 ];
    ModemATBased::vcacucATResponse[ 5 ]	 =  0;
	
	ModemATBased::vcacucATString[ 6 ]	 =  &modem_bye[ 0 ];
	ModemATBased::vcacucATResponse[ 6 ]	 =  &modem_modem_ok[ 0 ];
                
	ModemATBased::vcaucSMStep			 =  0;
	ModemATBased::vcaucSMTotalStep		 =  6;
	ModemATBased::vcascPointerDataModem	 = -1;
	ModemATBased::StateMachineRun ();
}

void ModemATBased::StateMachineRun ()
{
    ModemATBased::sendCommandConstBased ( ModemATBased::vcacucATString[ ModemATBased::vcaucSMStep ] );
    
    if ( ModemATBased::vcacucATResponse[ ModemATBased::vcaucSMStep ] == 0 )
	{
        if ( ModemATBased::vcaucSMStep != ModemATBased::vcaucSMTotalStep )
        {
            ModemATBased::vcaucSMStep ++;
            ModemATBased::StateMachineRun ();
        }
	}
	
	else
	{
		ModemATBased::vcascPointerDataModem	 =  0;
		ModemATBased::vcucpDataToCompare	 =  ModemATBased::vcacucATResponse[ ModemATBased::vcaucSMStep ];
	}
}

void ModemATBased::sendCommandConstBased ( const unsigned char * vapcucString )
{
	while ( * vapcucString != 0x00 )
	{
		switch ( * vapcucString )
        {
            case kTelefon:
                
                ModemATBased::sendCommandConstBased ( ModemATBased::vcpucTelefone );
                break;
		
            case kMessage:
            
                ModemATBased::sendCommandConstBased ( ModemATBased::vcpucMessage );
                break;
            
            default:
                ModemATBased::sendData ( * vapcucString );
                //vapcucString ++;
                break;
        }
        
        vapcucString ++;
	}
}

void ModemATBased::sendCommandExternalPointerBased ( unsigned char * vapucExternalPointer )
{
    while ( * vapucExternalPointer != 0x00 )
    {
        ModemATBased::sendData ( * vapucExternalPointer );
        vapucExternalPointer ++;
    }
}

void ModemATBased::getDataModem ()
{
	if ( ModemATBased::vcascPointerDataModem == -1 )
	{
		Serial.print( (unsigned char)Serial1.read() );
		return;
	}
	
	if ( ModemATBased::availableData () )
	{
        unsigned char vlucSerialData =  ModemATBased::getData ();
        
		if ( ( vlucSerialData == (unsigned char)(*ModemATBased::vcucpDataToCompare) ) || ( (unsigned char)(*ModemATBased::vcucpDataToCompare) == kAnyWare ) )
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
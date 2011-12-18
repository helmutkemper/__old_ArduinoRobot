/*
 *  SayItModule.cpp
 *
 *  Created by Kemper on 09/2011.
 *  Copyright 2011 Kemper. All rights reserved.
 *
 *  This class was written by Kemper, http://www.kemper.com.br, and may be distributed or altered 
 *  without requiring the permission of the author. Should only respect the copyrights of same.
 *
 *  This is a Arduino class to control Parallax Say It Module.
 *  Please, download the manual or to buy a module, visit the website http://www.parallax.com and search for '30080'
 *
 */


#include "WProgram.h"
#include "SayItModule.h"

#ifdef expertMode
unsigned char			*(SayItModule::vcucpMemory);
#else
unsigned char			SayItModule::vceSMStepList[ StepRing ]	=  { CommandList::Break, CommandList::TimeOutInfinite, CommandList::LanguageEnglish, CommandList::recCustomTrigger, CommandList::Free };
#endif

voidPonteiroDeFuncao	SayItModule::vcaFuncoes[ 3 ];
//unsigned char			SayItModule::vceSMStepList[ StepRing ]	=  { CommandList::Break, CommandList::TimeOutInfinite, CommandList::LanguageEnglish, CommandList::recCustomTrigger, CommandList::Free };
unsigned char			SayItModule::vcucSMStepOut				=  0;
unsigned char			SayItModule::vcucSMStepSubordinate		=  0;
boolean					SayItModule::vcbSMStepBusy				=  false;

eSerialPort				SayItModule::vceSerial;

/** Construtor.
 *  O construtor da classe não é utilisado para econimizar memória.
 */
SayItModule::SayItModule ()
{

}

/** 
 *  
 *  
 *  
 *  
 */
void SayItModule::executeEventFunction ( unsigned char vaucType, unsigned char vaucIndex )
{
	if ( SayItModule::vcaFuncoes[ vaucType ] )
		SayItModule::vcaFuncoes[ vaucType ] ( vaucIndex );
}

/** 
 *  
 *  
 *  
 *  
 */
void SayItModule::defineEventFunction ( void ( * vafpExtFuntion ) ( unsigned char ), unsigned char vaucType )
{
	SayItModule::vcaFuncoes[ vaucType ]	 =  vafpExtFuntion;
}

/** 
 *  
 *  
 *  
 *  
 */
void SayItModule::setSerial ( eSerialPort vaeSerial )
{
	switch ( vaeSerial )
	{
		#ifndef debug_sayitmodule
		case SerialPort::Port0:	Serial.begin ( 9600 );
			break;
		#endif
		#if defined(UBRR1H)
		case SerialPort::Port1:	Serial1.begin ( 9600 );
/*			                    Serial1.print ( "aB" );
								delay ( 1000 );
								Serial1.end ();
								Serial1.begin ( 115200 );
								while ( true )
								{
								  if ( Serial1.available () )
								  {
								    if ( Serial1.read () == 'o' )
									{
									  digitalWrite ( 13, HIGH );
									  delay ( 300 );
									  digitalWrite ( 13, LOW );
									  delay ( 300 );
									  digitalWrite ( 13, HIGH );
									  delay ( 300 );
									  digitalWrite ( 13, LOW );
									  delay ( 300 );
									  digitalWrite ( 13, HIGH );
									  delay ( 300 );
									  digitalWrite ( 13, LOW );
									  delay ( 300 );
									  Serial1.flush ();
									  break;
									}
									
									else if ( Serial1.read () == 'v' )
									{
									  digitalWrite ( 13, HIGH );
									  delay ( 3000 );
									  digitalWrite ( 13, LOW );
									  delay ( 3000 );
									  digitalWrite ( 13, HIGH );
									  delay ( 3000 );
									  digitalWrite ( 13, LOW );
									  delay ( 3000 );
									  digitalWrite ( 13, HIGH );
									  delay ( 3000 );
									  digitalWrite ( 13, LOW );
									  delay ( 3000 );
									  break;
									}
								  }
								}*/
								//Serial1.begin ( 115200 );
								
			break;
		#endif
		#if defined(UBRR2H)
		case SerialPort::Port2:	Serial2.begin ( 9600 );
			break;
		#endif
		#if defined(UBRR3H)
		case SerialPort::Port3:	Serial3.begin ( 9600 );
			break;
		#endif
	}
	
	SayItModule::vceSerial	 =  vaeSerial;
}

/** 
 *  
 *  
 *  
 *  
 */
void SayItModule::sendData ( String vasData )
{
	switch ( SayItModule::vceSerial )
	{
		#ifndef debug_sayitmodule
		case SerialPort::Port0:	Serial.print ( vasData );
			break;
		#endif
		#if defined(UBRR1H)
		case SerialPort::Port1:	Serial1.print ( vasData );
			break;
		#endif
		#if defined(UBRR2H)
		case SerialPort::Port2:	Serial2.print ( vasData );
			break;
		#endif
		#if defined(UBRR3H)
		case SerialPort::Port3:	Serial3.print ( vasData );
			break;
		#endif
	}
	
	delay ( 100 );
}

/** 
 *  
 *  
 *  
 *  
 */
int SayItModule::availableData ( )
{
	switch ( SayItModule::vceSerial )
	{
		#ifndef debug_sayitmodule
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
unsigned char SayItModule::getData ( )
{
	switch ( SayItModule::vceSerial )
	{
		#ifndef debug_sayitmodule
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

/** 
 *  
 *  
 *  
 *  
 */
void SayItModule::incrementStep ( )
{
	#ifdef expertMode
	SayItModule::vcucpMemory++;
	#else
	if ( SayItModule::vcucSMStepOut < ( StepRing - 1 ) )
	{
		SayItModule::vcucSMStepOut ++;
	}

	else
	{
		SayItModule::vcucSMStepOut =  0;
	}
	#endif
}

/** 
 *  
 *  
 *  
 *  
 */
void SayItModule::run ()
{
	unsigned char vlucDataIn;
	
	if ( !SayItModule::availableData () )
		return;
	
	vlucDataIn	 =  SayItModule::getData ();
	
	#ifdef debug_sayitmodule
	Serial.print ( "Recebeu: " );
	Serial.println ( vlucDataIn );
	#endif
	
	#ifdef expertMode
	switch ( *( SayItModule::vcucpMemory ) )
	#else
	switch ( SayItModule::vceSMStepList[ SayItModule::vcucSMStepOut ] )
	#endif
	{
		case CommandList::Break:
		#ifdef enLanguageEnglish
		case CommandList::LanguageEnglish:
		#endif
		#ifdef enLanguageItalian
		case CommandList::LanguageItalian:
		#endif
		#ifdef enLanguageJapanese
		case CommandList::LanguageJapanese:
		#endif
		#ifdef enLanguageGerman
		case CommandList::LanguageGerman:
		#endif
		#ifdef enTimeOutDefault
		case CommandList::TimeOutDefault:
		#endif
		#ifdef enTimeOutInfinite
		case CommandList::TimeOutInfinite:
		#endif
		#ifdef enTimeOut10
		case CommandList::TimeOut10:
		#endif
		#ifdef enTimeOut20
		case CommandList::TimeOut20:
		#endif
		#ifdef enTimeOut30
		case CommandList::TimeOut30:
		#endif
													switch ( vlucDataIn )
													{
														case 'o':	SayItModule::incrementStep ();
																	SayItModule::execute ();
																	return;
																	
														default:	SayItModule::execute ();
																	return;
													}
		
		#ifdef enRecPreProgrammedTrigger
		case CommandList::recPreProgrammedTrigger:
		#endif
		#ifdef enRecPreProgrammedCommand
		case CommandList::recPreProgrammedCommand:
		#endif
		#ifdef enRecPreProgrammedDirection
		case CommandList::recPreProgrammedDirection:
		#endif
		#ifdef enRecPreProgrammedNumber
		case CommandList::recPreProgrammedNumber:
		#endif
		#ifdef enRecCustomTrigger
		case CommandList::recCustomTrigger:
		#endif
		#ifdef enRecCustomGroup1
		case CommandList::recCustomGroup1:
		#endif
		#ifdef enRecCustomGroup2
		case CommandList::recCustomGroup2:
		#endif
		#ifdef enRecCustomGroup3
		case CommandList::recCustomGroup3:
		#endif
		#ifdef enRecCustomGroup4
		case CommandList::recCustomGroup4:
		#endif
		#ifdef enRecCustomGroup5
		case CommandList::recCustomGroup5:
		#endif
		#ifdef enRecCustomGroup6
		case CommandList::recCustomGroup6:
		#endif
		#ifdef enRecCustomGroup7
		case CommandList::recCustomGroup7:
		#endif
		#ifdef enRecCustomGroup8
		case CommandList::recCustomGroup8:
		#endif
		#ifdef enRecCustomGroup9
		case CommandList::recCustomGroup9:
		#endif
		#ifdef enRecCustomGroup10
		case CommandList::recCustomGroup10:
		#endif
		#ifdef enRecCustomGroup11
		case CommandList::recCustomGroup11:
		#endif
		#ifdef enRecCustomGroup12
		case CommandList::recCustomGroup12:
		#endif
		#ifdef enRecCustomGroup13
		case CommandList::recCustomGroup13:
		#endif
		#ifdef enRecCustomGroup14
		case CommandList::recCustomGroup14:
		#endif
		#ifdef enRecCustomGroup15
		case CommandList::recCustomGroup15:
		#endif
		#ifdef enRecPassword
		case CommandList::recPassword:
		#endif
													if ( SayItModule::vcucSMStepSubordinate == 0 )
													{
														switch ( vlucDataIn )
														{
															case 'e':	SayItModule::vcucSMStepSubordinate =  1;
																		SayItModule::sendData ( " " );
																		return;
																		
															case 's':
															case 'r':	SayItModule::sendData ( " " );
																		return;
																		
															case 't':	SayItModule::sendData ( " " );
																		return;
														
															case 'A':
															case 'B':
															case 'C':
															case 'D':
															case 'E':
															case 'F':
															case 'G':
															case 'H':	
															case 'I':	
															case 'J':	
															case 'K':	
															case 'L':	
															case 'M':	
															case 'N':	
															case 'O':	
															case 'P':	
															case 'Q':	
															case 'R':	
															case 'S':	
															case 'T':	
															case 'U':	
															case 'V':	
															case 'W':	
															case 'X':	
															case 'Y':	
															case 'Z':	SayItModule::executeEventFunction ( Reconhecimento, vlucDataIn );

																		#ifdef debug_sayitmodule
																		Serial.print ( "Reconheceu comando de voz: " );
																		Serial.println ( vlucDataIn );
																		#endif*/
																		
																		//SayItModule::execute ();
																		return;
																	
															default:	SayItModule::execute ();
																		return;
														}
													}
													
													else if ( SayItModule::vcucSMStepSubordinate == 1 )
													{
														SayItModule::vcucSMStepSubordinate =  2;
														SayItModule::sendData ( " " );
														return;
													}
													
													else
													{
														SayItModule::vcucSMStepSubordinate =  0;
														SayItModule::execute ();
														return;
													}
		#ifdef enFirmwareVersion
		case CommandList::FirmwareVersion:			switch ( vlucDataIn )
													{
														case 'x':	SayItModule::sendData ( " " );
																	return;
														
														case 'A':
														case 'B':
														case 'C':
														case 'D':
														case 'E':
														case 'F':
														case 'G':
														case 'H':	
														case 'I':	
														case 'J':	
														case 'K':	SayItModule::incrementStep ();
																	SayItModule::execute ();
																	return;
																	
														default:	SayItModule::execute ();
																	return;
													}
		#endif
	}
}

/** 
 *  
 *  
 *  
 *  
 */
void SayItModule::clear ()
{
	SayItModule::vcucSMStepOut		 =  0;
	SayItModule::vcbSMStepBusy		 =  false;
	#ifndef expertMode
	SayItModule::vceSMStepList[0]	 =  CommandList::Free;
	#endif
}

void SayItModule::setGroup ( eCommandList vaeGroup )
{
	SayItModule::vcucSMStepOut		 =  0;
	#ifndef expertMode
	Serial.print ( "setGroup: " );
	Serial.println ( vaeGroup );
	SayItModule::vceSMStepList[0]	 =  vaeGroup;
	SayItModule::vceSMStepList[1]	 =  CommandList::Free;
	#endif
	SayItModule::execute ();
}

/** 
 *  
 *  
 *  
 *  
 */
void SayItModule::start ()
{
	#ifdef debug_sayitmodule
	Serial.begin ( 38400 );
	Serial.println ( "Debug started" );
	#endif
	
	if ( SayItModule::vcbSMStepBusy == true )
		return;
		
	SayItModule::vcucSMStepOut	 =  0;
	SayItModule::execute ();
}

/** 
 *  
 *  
 *  
 *  
 */
void SayItModule::execute ()
{
	SayItModule::vcbSMStepBusy			 =  true;
	SayItModule::vcucSMStepSubordinate	 =  0;
	
	#ifdef expertMode
	switch ( *( SayItModule::vcucpMemory ) )
	#else
	switch ( SayItModule::vceSMStepList[ SayItModule::vcucSMStepOut ] )
	#endif
	{
		case CommandList::Free:						SayItModule::vcbSMStepBusy =  false;
													return;
		
		// Abort recognition in progress if any or do nothing
		case CommandList::Break:					SayItModule::sendData ( "b" );
													#ifdef debug_sayitmodule
													Serial.println ( "send b" );
													#endif
													return;
		#ifdef enLanguageEnglish											
		case CommandList::LanguageEnglish:			SayItModule::sendData ( "lA" );
													#ifdef debug_sayitmodule
													Serial.println ( "send lA" );
													#endif
													return;
		#endif
		#ifdef enLanguageItalian
		case CommandList::LanguageItalian:			SayItModule::sendData ( "lB" );
													#ifdef debug_sayitmodule
													Serial.println ( "send lB" );
													#endif
													return;
		#endif
		#ifdef enLanguageJapanese
		case CommandList::LanguageJapanese:			SayItModule::sendData ( "lC" );
													#ifdef debug_sayitmodule
													Serial.println ( "send lC" );
													#endif
													return;
		#endif
		#ifdef enLanguageGerman
		case CommandList::LanguageGerman:			SayItModule::sendData ( "lD" );
													#ifdef debug_sayitmodule
													Serial.println ( "send lD" );
													#endif
													return;



		#endif
		#ifdef enTimeOutDefault
		case CommandList::TimeOutDefault:			SayItModule::sendData ( "o@" );
													#ifdef debug_sayitmodule
													Serial.println ( "send o@" );
													#endif
													return;
		#endif
		#ifdef enTimeOutInfinite
		case CommandList::TimeOutInfinite:			SayItModule::sendData ( "oA" );
													#ifdef debug_sayitmodule
													Serial.println ( "send oA" );
													#endif
													return;
		#endif
		#ifdef enTimeOut10
		case CommandList::TimeOut10:				SayItModule::sendData ( "oK" );
													#ifdef debug_sayitmodule
													Serial.println ( "send oK" );
													#endif
													return;
		#endif
		#ifdef enTimeOut20
		case CommandList::TimeOut20:				SayItModule::sendData ( "oU" );
													#ifdef debug_sayitmodule
													Serial.println ( "send oU" );
													#endif
													return;
		#endif
		#ifdef enTimeOut30
		case CommandList::TimeOut30:				SayItModule::sendData ( "o_" );
													#ifdef debug_sayitmodule
													Serial.println ( "send o_" );
													#endif
													return;
		#endif
		#ifdef enRecPreProgrammedTrigger
		case CommandList::recPreProgrammedTrigger:	SayItModule::sendData ( "iA" );
													#ifdef debug_sayitmodule
													Serial.println ( "send iA" );
													#endif
													return;
		#endif
		#ifdef enRecPreProgrammedCommand
		case CommandList::recPreProgrammedCommand:	SayItModule::sendData ( "iB" );
													#ifdef debug_sayitmodule
													Serial.println ( "send iB" );
													#endif
													return;
		#endif
		#ifdef enRecPreProgrammedDirection
		case CommandList::recPreProgrammedDirection:SayItModule::sendData ( "iC" );
													#ifdef debug_sayitmodule
													Serial.println ( "send iC" );
													#endif
													return;
		#endif
		#ifdef enRecPreProgrammedNumber
		case CommandList::recPreProgrammedNumber:	SayItModule::sendData ( "iD" );
													#ifdef debug_sayitmodule
													Serial.println ( "send iD" );
													#endif
													return;
		#endif
		#ifdef enRecCustomTrigger
		case CommandList::recCustomTrigger:			SayItModule::sendData ( "dA" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dA" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup1
		case CommandList::recCustomGroup1:			SayItModule::sendData ( "dB" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dB" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup2
		case CommandList::recCustomGroup2:			SayItModule::sendData ( "dC" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dC" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup3
		case CommandList::recCustomGroup3:			SayItModule::sendData ( "dD" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dD" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup4
		case CommandList::recCustomGroup4:			SayItModule::sendData ( "dE" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dE" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup5
		case CommandList::recCustomGroup5:			SayItModule::sendData ( "dF" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dF" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup6
		case CommandList::recCustomGroup6:			SayItModule::sendData ( "dG" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dG" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup7
		case CommandList::recCustomGroup7:			SayItModule::sendData ( "dH" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dH" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup8
		case CommandList::recCustomGroup8:			SayItModule::sendData ( "dI" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dI" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup9
		case CommandList::recCustomGroup9:			SayItModule::sendData ( "dJ" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dJ" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup10
		case CommandList::recCustomGroup10:			SayItModule::sendData ( "dK" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dK" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup11
		case CommandList::recCustomGroup11:			SayItModule::sendData ( "dL" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dL" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup12
		case CommandList::recCustomGroup12:			SayItModule::sendData ( "dM" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dM" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup13
		case CommandList::recCustomGroup13:			SayItModule::sendData ( "dN" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dN" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup14
		case CommandList::recCustomGroup14:			SayItModule::sendData ( "dO" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dO" );
													#endif
													return;
		#endif
		#ifdef enRecCustomGroup15
		case CommandList::recCustomGroup15:			SayItModule::sendData ( "dP" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dP" );
													#endif
													return;
		#endif
		#ifdef enRecPassword
		case CommandList::recPassword:				SayItModule::sendData ( "dQ" );
													#ifdef debug_sayitmodule
													Serial.println ( "send dQ" );
													#endif
													return;
		#endif
		#ifdef enFirmwareVersion
		case CommandList::FirmwareVersion:			SayItModule::sendData ( "x" );
													#ifdef debug_sayitmodule
													Serial.println ( "send x" );
													#endif
													return;
		#endif
	}
}

void SayItModule::setLabelSpeakerDependent ( unsigned char vaucGroup, unsigned char vaucPosition, unsigned char vaucLength, unsigned char *vapucLabel )
{
	// total + 2
}
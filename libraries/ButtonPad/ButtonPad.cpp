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

#include "ButtonPad.h"

const unsigned char *   ButtonPad::vcpucColumn1;
const unsigned char *   ButtonPad::vcpucColumn2;
const unsigned char *   ButtonPad::vcpucColumn3;
const unsigned char *   ButtonPad::vcpucColumn4;

const unsigned char *   ButtonPad::vcpucLine1;
const unsigned char *   ButtonPad::vcpucLine2;
const unsigned char *   ButtonPad::vcpucLine3;
const unsigned char *   ButtonPad::vcpucLine4;

const int           *   ButtonPad::ClickInterval;
const int           *   ButtonPad::FirstClickInterval;

const unsigned char *   ButtonPad::DataMatrix[16];

functionPointer         ButtonPad::eventFunction     =  0;

unsigned char           ButtonPad::vcucKeyId         =  0;
unsigned long           ButtonPad::vculMicroSteps    =  0;
unsigned long           ButtonPad::vculMicroseconds  =  millis();

void ButtonPad::resetTime ()
{
    ButtonPad::vculMicroseconds     =  millis ();
}

boolean ButtonPad::testTime ( unsigned long vaulMicroseconds )
{
    return ( ButtonPad::vculMicroseconds + vaulMicroseconds <= millis () );
}

void ButtonPad::configColumn ( const unsigned char * vapucColumn1, const unsigned char * vapucColumn2, const unsigned char * vapucColumn3, const unsigned char * vapucColumn4 )
{
    ButtonPad::vcpucColumn1     =  vapucColumn1;
    ButtonPad::vcpucColumn2     =  vapucColumn2;
    ButtonPad::vcpucColumn3     =  vapucColumn3;
    ButtonPad::vcpucColumn4     =  vapucColumn4;
    
    pinMode ( * ButtonPad::vcpucColumn1, INPUT );
    pinMode ( * ButtonPad::vcpucColumn2, INPUT );
    pinMode ( * ButtonPad::vcpucColumn3, INPUT );
    pinMode ( * ButtonPad::vcpucColumn4, INPUT );
    
    digitalWrite ( * ButtonPad::vcpucColumn1, HIGH );
    digitalWrite ( * ButtonPad::vcpucColumn2, HIGH );
    digitalWrite ( * ButtonPad::vcpucColumn3, HIGH );
    digitalWrite ( * ButtonPad::vcpucColumn4, HIGH );
}

void ButtonPad::configLine ( const unsigned char * vapucLine1, const unsigned char * vapucLine2, const unsigned char * vapucLine3, const unsigned char * vapucLine4 )
{
    ButtonPad::vcpucLine1       =  vapucLine1;
    ButtonPad::vcpucLine2       =  vapucLine2;
    ButtonPad::vcpucLine3       =  vapucLine3;
    ButtonPad::vcpucLine4       =  vapucLine4;
    
    pinMode ( * ButtonPad::vcpucLine1, OUTPUT );
    pinMode ( * ButtonPad::vcpucLine2, OUTPUT );
    pinMode ( * ButtonPad::vcpucLine3, OUTPUT );
    pinMode ( * ButtonPad::vcpucLine4, OUTPUT );
    
    digitalWrite ( * ButtonPad::vcpucLine1, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine2, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine3, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine4, HIGH );
}

void ButtonPad::run ()
{
    boolean vlbPass =  false;
    
    digitalWrite ( * ButtonPad::vcpucLine1, LOW );
    digitalWrite ( * ButtonPad::vcpucLine2, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine3, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine4, HIGH );
    
    if ( ButtonPad::testKey ( 0 ) )
    {
        vlbPass = true;
    }
    
    digitalWrite ( * ButtonPad::vcpucLine1, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine2, LOW );
    digitalWrite ( * ButtonPad::vcpucLine3, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine4, HIGH );
    
    if ( ButtonPad::testKey ( 4 ) )
    {
        vlbPass = true;
    }
    
    digitalWrite ( * ButtonPad::vcpucLine1, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine2, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine3, LOW );
    digitalWrite ( * ButtonPad::vcpucLine4, HIGH );
    
    if ( ButtonPad::testKey ( 8 ) )
    {
        vlbPass = true;
    }
    
    digitalWrite ( * ButtonPad::vcpucLine1, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine2, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine3, HIGH );
    digitalWrite ( * ButtonPad::vcpucLine4, LOW );
    
    if ( ButtonPad::testKey ( 12 ) )
    {
        vlbPass = true;
    }
    
    if ( !vlbPass )
    {
        if ( ( ButtonPad::vcucKeyId != 0 ) && ( ButtonPad::testTime ( 500 ) ) )
        {
            ButtonPad::eventFunction ( EventButtonPad::keyUp, ButtonPad::vcucKeyId - 1 );
        }
        
        ButtonPad::resetTime ();
        ButtonPad::vculMicroSteps   =  0;
        ButtonPad::vcucKeyId        =  0;
    }
}

boolean ButtonPad::testKey ( unsigned char vaucKeyId )
{
    unsigned char vlucData  =  0x00;
    
    bitWrite ( vlucData, 0, digitalRead ( * ButtonPad::vcpucColumn1 ) );
    bitWrite ( vlucData, 1, digitalRead ( * ButtonPad::vcpucColumn2 ) );
    bitWrite ( vlucData, 2, digitalRead ( * ButtonPad::vcpucColumn3 ) );
    bitWrite ( vlucData, 3, digitalRead ( * ButtonPad::vcpucColumn4 ) );
    
    switch ( vlucData )
    {
        case 0x7: ButtonPad::makeSubEvent ( vaucKeyId + 1 );
                  break;
                
        case 0xB: ButtonPad::makeSubEvent ( vaucKeyId + 2 );
                  break;
                
        case 0xD: ButtonPad::makeSubEvent ( vaucKeyId + 3 );
                  break;
                
        case 0xE: ButtonPad::makeSubEvent ( vaucKeyId + 4 );
                  break;
                  
        default:  return false;
    }
    
    return true;
}

void ButtonPad::makeSubEvent ( unsigned char vaucKeyId )
{
    if ( ButtonPad::vcucKeyId != vaucKeyId )
    {
        ButtonPad::resetTime ();
        ButtonPad::vcucKeyId      =  vaucKeyId;
        ButtonPad::vculMicroSteps =  0;
    }
    
    else if ( ( ButtonPad::testTime ( 500 ) ) && ( ButtonPad::vculMicroSteps == 0 ) )
    {
        ButtonPad::vculMicroSteps +=  *ButtonPad::FirstClickInterval + 500;
        ButtonPad::eventFunction ( EventButtonPad::keyDown, vaucKeyId - 1 );
        ButtonPad::eventFunction ( EventButtonPad::keyClick, vaucKeyId - 1 );
    }
    
    else if ( ( ButtonPad::testTime ( ButtonPad::vculMicroSteps + 500 ) ) && ( ButtonPad::vculMicroSteps != 0 ) )
    {
        ButtonPad::vculMicroSteps +=  *ButtonPad::ClickInterval + 500;
        ButtonPad::eventFunction ( EventButtonPad::keyClick, vaucKeyId - 1 );
    }
}
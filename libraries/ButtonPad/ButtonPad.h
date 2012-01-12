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

#ifndef ButtonPad_h
#define ButtonPad_h

namespace EventButtonPad
{
    enum eEventButtonPad
    {
        None,
        keyUp,
        keyClick,
        keyDown
    };
}
using namespace EventButtonPad;

extern "C"
{
	typedef void ( * functionPointer )( eEventButtonPad, unsigned char );
}

class ButtonPad
{
    private:
        
        static const unsigned char *   vcpucColumn1;
        static const unsigned char *   vcpucColumn2;
        static const unsigned char *   vcpucColumn3;
        static const unsigned char *   vcpucColumn4;

        static const unsigned char *   vcpucLine1;
        static const unsigned char *   vcpucLine2;
        static const unsigned char *   vcpucLine3;
        static const unsigned char *   vcpucLine4;
        
        static unsigned char           vcucKeyId;
        static unsigned long           vculMicroseconds;
        static unsigned long           vculMicroSteps;
        
        static void                    resetTime ();
        static boolean                 testTime ( unsigned long vaulMicroseconds );
        static boolean                 testKey ( unsigned char vaucKeyId );
        static void                    makeSubEvent ( unsigned char vaucKeyId );
        
    public:
        
        static functionPointer         eventFunction;
        static const int           *   ClickInterval;
        static const int           *   FirstClickInterval;
        static void                    run ();
        static void                    configColumn ( const unsigned char * vapucColumn1, const unsigned char * vapucColumn2, const unsigned char * vapucColumn3, const unsigned char * vapucColumn4 );
        static void                    configLine ( const unsigned char * vapucLine1, const unsigned char * vapucLine2, const unsigned char * vapucLine3, const unsigned char * vapucLine4 );
        
};

#endif
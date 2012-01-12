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


#include <ButtonPad.h>

const unsigned char kColumn0 =  31;
const unsigned char kColumn1 =  33;
const unsigned char kColumn2 =  35;
const unsigned char kColumn3 =  37;

const unsigned char kLine3   =  39;
const unsigned char kLine2   =  41;
const unsigned char kLine1   =  43;
const unsigned char kLine0   =  45;

const int ClickInterval      =  700;
const int FirstClickInterval =  3000;


void setup ()
{
  Serial.begin ( 19200 );
  ButtonPad::eventFunction       =  &event;
  ButtonPad::ClickInterval       =  &ClickInterval;
  ButtonPad::FirstClickInterval  =  &FirstClickInterval;
  ButtonPad::configColumn ( &kColumn0, &kColumn1, &kColumn2, &kColumn3 );
  ButtonPad::configLine ( &kLine0, &kLine1, &kLine2, &kLine3 );
}

void loop ()
{
  ButtonPad::run ();
}

void event ( eEventButtonPad vaeEvent, unsigned char vaucKeyId )
{
  switch ( vaeEvent )
  {
    case EventButtonPad::keyDown:  Serial.write ( "down: " );
                                   break;
                                   
    case EventButtonPad::keyUp:    Serial.write ( "up: " );
                                   break;
                                   
     case EventButtonPad::keyClick:Serial.write ( "click: " );
                                   break;
  }
  
  Serial.print ( vaucKeyId, HEX );
  Serial.write ( "\r\n" );

}

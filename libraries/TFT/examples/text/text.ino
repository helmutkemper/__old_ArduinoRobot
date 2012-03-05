// Draw Texts - Demonstrate drawChar and drawString


#include <stdint.h>
#include <TouchScreen.h> 
#include <TFT.h>

#ifdef SEEEDUINO
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM 14   // can be a digital pin, this is A0
  #define XP 17   // can be a digital pin, this is A3 
#endif

#ifdef MEGA
  #define YP A2   // must be an analog pin, use "An" notation!
  #define XM A1   // must be an analog pin, use "An" notation!
  #define YM 54   // can be a digital pin, this is A0
  #define XP 57   // can be a digital pin, this is A3 
#endif 

void setup()
{

Tft.init();  //init TFT library

  Tft.drawString("Happy!",0,160,1,CYAN);
  Tft.drawString("Happy!",0,200,2,WHITE);
  Tft.drawString("Happy!",0,240,4,WHITE);
}

void loop()
{
  

}

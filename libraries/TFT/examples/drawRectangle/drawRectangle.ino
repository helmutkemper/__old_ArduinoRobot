// Draw Boxes - Demonstrate drawRectangle and fillRectangle

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

/*  Demo of 
    drawRectangle(unsigned int poX, unsigned int poY, unsigned int length,unsigned int width,unsigned int color);
    fillRectangle(unsigned int poX, unsigned int poY, unsigned int length, unsigned int width, unsigned int color);
*/
 Tft.drawRectangle(10, 3, 200,60,BLUE);
 Tft.fillRectangle(0, 80, 100,65,YELLOW);
 Tft.drawRectangle(30, 160, 60, 60,RED);
}

void loop()
{
  
}

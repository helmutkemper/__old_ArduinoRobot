// Draw Circles - Demonstrate drawCircle and fillCircle APIs

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
    void drawCircle(int poX, int poY, int r,unsigned int color) and
    void fillCircle(int poX, int poY, int r,unsigned int color);
*/
Tft.drawCircle(100, 100, 30,YELLOW);
Tft.drawCircle(100, 200, 40,CYAN);
Tft.fillCircle(200, 100, 30,RED);
Tft.fillCircle(200, 200, 30,BLUE);
}

void loop()
{
  
}

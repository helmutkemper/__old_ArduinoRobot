#include "Ultrasonic.h"
//Ultrasonic(int TP, int EP)
Ultrasonic ultrasonic1( 52, 53 );
Ultrasonic ultrasonic2( 50, 51 );

int dis1, dis2;
int ledPin = 13;
int ledExt = 47;
int total = 35;

// setup initializes serial and the button pin
void setup()
{
  Serial.begin (9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledExt, OUTPUT);
}

void loop()
{
  dis1 = ultrasonic1.Ranging ( CM );
  Serial.print ( "Sensor 1: " );
  Serial.println ( dis1 );
  dis2 = ultrasonic2.Ranging ( CM );
  Serial.print ( "Sensor 2: " );
  Serial.println ( dis2 );
  
  if ( ( dis1 > total ) or ( dis2 > total ) )
  {
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledExt, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
    digitalWrite(ledExt, LOW);   // sets the LED on
  }
  //delay(1000);                  // waits for a second
      // sets the LED off
  //delay(1000);
}

#include <SoftwareServo.h>

SoftwareServo servo1;
SoftwareServo servo2;

void setup()
{
  pinMode(13,OUTPUT);
  servo1.attach(3);
  servo1.setMaximumPulse(2200);
  servo1.write(90);
  servo2.attach(4);
  servo2.setMaximumPulse(2200);
  Serial.begin(9600);
  Serial.print("Ready");
}

void loop()
{
  static int value = 0;
  static char CurrentServo = 0;

  if ( Serial.available()) {
    char ch = Serial.read();
    switch(ch) {
      case 'C':
        servo1.write(90);
      break;
      case 'D':
        servo1.write(60);
      break;
      case 'A':
//        servo1.attach(3);
        Serial.print ("entrou");
        CurrentServo='A';
        digitalWrite(13,LOW);
        break;
      case 'B':
//        servo2.attach(4);
        CurrentServo='B';
        digitalWrite(13,HIGH);
        break;
      case '0' ... '9':
        value=(ch-'0')*20;
        if (CurrentServo=='A')
        {
          servo1.write(value);
        }
        else if (CurrentServo=='B')
        {
          servo2.write(value);
        }
        break;
    }
  }
  SoftwareServo::refresh();
}

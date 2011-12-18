//Remember when using GPRS Shield with Seeeduino Stalker v2.0 
//please dismount the OK_READ Jumper (i.e. open it).
//This will disconnect the Battery Charger IC's OK pin from
//the microcontrollers Digital Pin 7 and hence allow unhindered
//communication with GPRS Shield using NewSoftSerial Library. 
 
 
//Replace the following items in the code:
//1. Replace the Access Point Name "TATA.DOCOMO.INTERNET" 
//and the DNS server name "10.6.6.6" in the AT+CGDCONT and AT+CSTT
//commands with those of your own service provider.
//
//2. Replace the Pachube API Key with your personal ones assigned
//to your account at pachube.com
//
//3. You may choose a different name for the the data stream.
//I have choosen "TMP102". If you use a different name, you will have
//to replace this string with the new name.
//
 
//Please fetch tmp102.h and tmp102.cpp from "Stlker logger AM06 Serial.zip"
//available from Seeeduino Stalker v2.0's Wiki Page
#include <Wire.h>
 
 
float convertedtemp; // We then need to multiply our two bytes by a scaling factor, mentioned in the datasheet.
int tmp102_val; // an int is capable of storing two bytes, this is where we "chuck" the two bytes together.
 
 
void setup()
{
  Serial1.begin(19200);  //GPRS Shield baud rate
  Serial.begin(19200);
 
setup_start:
 
  Serial.println("Turn on GPRS Modem and wait for 1 minute.");
  Serial.println("and then press a key");
  Serial.println("Press c for power on configuration");
  Serial.println("press any other key for uploading");
  Serial.flush();
  while(Serial.available() == 0);
  if(Serial.read()=='c')
  {
    Serial.println("Executing AT Commands for one time power on configuration");
 
 
 
    Serial1.flush();
 
 
 
    Serial1.println("ATE0"); //Command echo off
    Serial.println("ATE0   Sent");
    if(Serial1_wait_for_bytes(4,10) == 0)
    {  
      Serial.println("Timeout");
      goto setup_start;
    }
    else
    {
      Serial.print("Received:");
      while(Serial1.available()!=0)
      {
        Serial.print((unsigned char)Serial1.read());
      }
      Serial.print("\n");
    }
 
 
 
 
 
 
    Serial1.println("AT+CIPMUX=0"); //We only want a single IP Connection at a time.
    Serial.println("AT+CIPMUX=0   Sent");
    if(Serial1_wait_for_bytes(4,10) == 0)
    {  
      Serial.println("Timeout");
      goto setup_start;
    }
    else
    {
      Serial.print("Received:");
      while(Serial1.available()!=0)
      {
        Serial.print((unsigned char)Serial1.read());
      }
      Serial.print("\n");
    }
 
 
 
 
 
 
    Serial1.println("AT+CIPMODE=0"); //Selecting "Normal Mode" and NOT "Transparent Mode" as the TCP/IP Application Mode
    Serial.println("AT+CIPMODE=0    Sent!");
    if(Serial1_wait_for_bytes(4,10) == 0)
    {  
      Serial.println("Timeout");
      goto setup_start;
    }
    else
    {
      Serial.print("Received:");
      while(Serial1.available()!=0)
      {
        Serial.print((unsigned char)Serial1.read());
      }
      Serial.print("\n");
    }
 
 
 
 
 
 
    Serial1.println("AT+CGDCONT=1,\"IP\",\"TATA.DOCOMO.INTERNET\",\"10.6.6.6\",0,0"); //Defining the Packet Data
//Protocol Context - i.e. the Protocol Type, Access Point Name and IP Address
    Serial.println("AT+CGDCONT=1,\"IP\",\"TATA.DOCOMO.INTERNET\",\"10.6.6.6\",0,0   Sent!");
    if(Serial1_wait_for_bytes(4,10) == 0)
    {  
      Serial.println("Timeout");
      goto setup_start;
    }
    else
    {
      Serial.print("Received:");
      while(Serial1.available()!=0)
      {
        Serial.print((unsigned char)Serial1.read());
      }
      Serial.print("\n");
    }
 
 
 
 
 
 
    Serial1.println("AT+CSTT=\"TATA.DOCOMO.INTERNET\""); //Start Task and set Access Point Name (and username and password if any)
    Serial.println("AT+CSTT=\"TATA.DOCOMO.INTERNET\"   Sent!");
    if(Serial1_wait_for_bytes(4,10) == 0)
    {  
      Serial.println("Timeout");
      goto setup_start;
    }
    else
    {
      Serial.print("Received:");
      while(Serial1.available()!=0)
      {
        Serial.print((unsigned char)Serial1.read());
      }
      Serial.print("\n");
    }
 
 
 
 
 
 
    Serial1.println("AT+CIPSHUT"); //Close any GPRS Connection if open
    Serial.println("AT+CIPSHUT  Sent!");
    if(Serial1_wait_for_bytes(7,10) == 0)
    {  
      Serial.println("Timeout");
      goto setup_start;
    }
    else
    {
      Serial.print("Received:");
      while(Serial1.available()!=0)
      {
        Serial.print((unsigned char)Serial1.read());
      }
      Serial.print("\n");
    }
  }
}
 
void loop()
{
loop_start:
 
  Serial.println("Press a key to read temperature and upload it");
  Serial.flush();
  while(Serial.available() == 0);
  Serial.read();
 
 
  Serial.print("TMP102 Temperature = ");
  Serial.println(convertedtemp);
 
  Serial1.println("AT+CIPSTART=\"TCP\",\"kemper.com.br\",\"80\""); //Open a connection to Pachube.com
  Serial.println("AT+CIPSTART=\"TCP\",\"kemper.com.br\",\"80\"  Sent!");
  if(Serial1_wait_for_bytes(12,255) == 0)
  {  
    Serial.println("Timeout");
    goto loop_start;
  }
  else
  {
    Serial.print("Received:");
    while(Serial1.available()!=0)
    {
      Serial.print((unsigned char)Serial1.read());
    }
    Serial.print("\n");
  }
 
  Serial1.flush();
  Serial1.println("AT+CIPSEND"); //Start data through TCP connection
  Serial.println("AT+CIPSEND  Sent!");
  if(Serial1_wait_for_bytes(1,100) == 0)
  {  
    Serial.println("Timeout");
    goto loop_start;
  }
  else
  {
    Serial.print("Received:");
    while(Serial1.available()!=0)
    {
      Serial.print((unsigned char)Serial1.read());
    }
    Serial.print("\n");
  }
 
 
  Serial1.flush();
 for (byte contador=0;contador != 5; contador++)
 {
  //Emulate HTTP and use PUT command to upload temperature datapoint using Comma Seperate Value Method
  Serial1.print("GET /modem/modem.php?teste=6 HTTP/1.1\r\n");
  Serial.println("GET /modem/modem.php?teste=6 HTTP/1.1  Sent!");
  delay(300);
 
  Serial1.print("Host: kemper.com.br\r\n"); 
  Serial.println("Host: kemper.com.br  Sent!");
  delay(300);
 
  Serial1.print("Connection: Keep-Alive\r\n"); //REPLACE THIS KEY WITH YOUR OWN PACHUBE API KEY
  Serial.println("Connection: Keep-Alive  Sent!"); //REPLACE THIS KEY WITH YOUR OWN PACHUBE API KEY
  delay(300);
 
  Serial1.print("Accept: */*\r\n"); 
  Serial.println("Accept: */*  Sent!"); 
//  delay(300);
 
//  Serial1.print("Accept-Language: en-us\r\n"); 
//  Serial.println("Accept-Language: en-us  Sent!"); 
//  delay(300);
   Serial1.print("Connection: close\r\n\r\n"); 
  Serial.print("Connection: close  Sent!");
  delay(300);
    
}
//  delay(300);
//  Serial1.print("\r\n"); 
//  delay(300);
  Serial1.print(0x1A,BYTE);
  delay(300); //Send End Of Line Character to send all the data and close connection
  if(Serial1_wait_for_bytes(20,255) == 0)
  {  
    Serial.println("Timeout");
    goto loop_start;
  }
  else
  {
    Serial.print("Received:");
    while(Serial1.available()!=0)
    {
      Serial.print((unsigned char)Serial1.read());
    }
    Serial.print("\n");
  }
 
 
 
 
  Serial1.flush();
  Serial1.println("AT+CIPSHUT"); //Close the GPRS Connection
  Serial.println("AT+CIPSHUT  Sent!");
  if(Serial1_wait_for_bytes(4,100) == 0)
  {  
    Serial.println("Timeout");
    goto loop_start;
  }
  else
  {
    Serial.print("Received:");
    while(Serial1.available()!=0)
    {
      Serial.print((unsigned char)Serial1.read());
    }
    Serial.print("\n");
  }
}
 
 
 
 
 
 
 
 
 
char Serial1_wait_for_bytes(char no_of_bytes, int timeout)
{
  while(Serial1.available() < no_of_bytes)
  {
    delay(200);
    timeout-=1;
    if(timeout == 0)
    {
      return 0;
    }
  }
  return 1;
}

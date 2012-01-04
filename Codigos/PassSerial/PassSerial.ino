//Serial Relay - Arduino will patch a 
//serial link between the computer and the GPRS Shield
//at 19200 bps 8-N-1
//Computer is connected to Hardware UART
//GPRS Shield is connected to the Software UART 
 
//
//AT+CMGF=1
//AT+CMGS="99268744"
//SIM900 and Arduino say Hi!
//
 
byte dadoSerial;

void setup()
{
  Serial1.begin(19200);               // the GPRS baud rate   
  Serial.begin(19200);                 // the GPRS baud rate   
}
 
void loop()
{
    if(Serial.available())
    {
      dadoSerial =  ( unsigned char ) Serial.read ();
      
      if ( dadoSerial == '#' )
        Serial1.print(26);
        
      else
        Serial1.write( dadoSerial );
    }  
    
    if(Serial1.available())
    {
       Serial.write((unsigned char)Serial1.read());
     }   
 
}

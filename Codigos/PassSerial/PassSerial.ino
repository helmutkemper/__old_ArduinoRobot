//Serial Relay - Arduino will patch a 
//serial link between the computer and the GPRS Shield
//at 19200 bps 8-N-1
//Computer is connected to Hardware UART
//GPRS Shield is connected to the Software UART 
//AT+CNMI=0,3,2 
//
//AT+CMGF=1
//AT+CMGS="97344690"
//SIM900 and Arduino say Hi!
//
 
byte dadoSerial;
byte dadoSerialModem;

void setup()
{
  pinMode ( 2, INPUT );
  pinMode ( 3, INPUT );
  Serial1.begin(9600);               // the GPRS baud rate   
  Serial.begin(9600);                 // the GPRS baud rate   
}
 
void loop()
{
    if(Serial.available())
    {
      dadoSerial =  ( unsigned char ) Serial.read ();
      
      if ( dadoSerial == '#' )
        Serial1.write(byte(26));
        
      else
        Serial1.write( dadoSerial );
    }  
    
    if(Serial1.available())
    {
      dadoSerialModem =  Serial1.read();
      
      if ( dadoSerialModem == NULL )
        Serial.write ( "NULL detectado\r\n" );
      
       Serial.write(dadoSerialModem);
     }   
 
}

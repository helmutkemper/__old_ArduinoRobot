// /dev/tty.usbserial-A8008HpZ

const byte pinoLed = 13;

void setup ()
{
  Serial.begin ( 9600 );
  pinMode ( pinoLed, INPUT );
}

void loop ()
{
  if ( !Serial.available () )
  {
    return;
  }
  Serial.print ("funciona!");
  while ( true )
  {
    digitalWrite ( pinoLed, HIGH );
    delay ( 100 );
    digitalWrite ( pinoLed, LOW );
    delay ( 100 );
  }
}

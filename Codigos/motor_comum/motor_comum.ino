const unsigned char A = 51;
const unsigned char B = 53;

void setup ()
{
  pinMode ( A, OUTPUT );
  pinMode ( B, OUTPUT );
  
  Serial.begin ( 9600 );
}

void loop ()
{
  if ( Serial.available () )
  {
    switch ( Serial.read () )
    {
      case 'A':
      case 'a': digitalWrite ( A, HIGH );
                digitalWrite ( B, LOW );
                Serial.write ( "A ok\r\n" );
                break;
                
      case 'B':
      case 'b': digitalWrite ( A, LOW );
                digitalWrite ( B, HIGH );
                Serial.write ( "B ok\r\n" );
                break;
                
       default: digitalWrite ( A, LOW );
                digitalWrite ( B, LOW );
                Serial.write ( "Parou\r\n" );
    }
  }
}

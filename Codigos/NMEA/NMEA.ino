const unsigned char   kucaNmea[]  =  "$GPRMC";
const unsigned char * vgucNmea;
      int            vgscGetingData =  0;
      unsigned char   vgucGpsRmc[80];
      
void setup ()
{
  Serial.begin ( 115200 );
  startGps ();
}

void loop ()
{
//  getGpsData ();
}

void startGps ()
{
  Serial3.begin ( 4800 );
  vgscGetingData =  0;
  vgucNmea       =  &kucaNmea[0];
}

void serialEvent3 ()
{
    unsigned char vlucData =  Serial3.read ();
    
    if ( vlucData == '\n' )
    {
      vgscGetingData =  0;
      vgucNmea       =  &kucaNmea[0];
    }
    
    vgucGpsRmc[   vgscGetingData       ] =  vlucData;
    vgucGpsRmc[ ( vgscGetingData + 1 ) ]   =  0x00;
    
    if ( ( vgscGetingData <= 0x05 ) && ( vlucData == *vgucNmea ) )
    {
      vgucNmea++;
      vgscGetingData++;
    }
    
    else if ( ( vgscGetingData > 0x05 ) && ( vlucData == '\r' ) )
    {
      Serial3.end ();
      Serial3.flush ();
      
      vgscGetingData =  0;
      
      while ( vgucGpsRmc[ vgscGetingData ] != 0x00 )
      {
        Serial.write ( vgucGpsRmc[ vgscGetingData++ ] );
      }
      Serial.write ( "\r\nTx ok\r\n" );
      return;
    }
    
    else if ( vgscGetingData > 0x05 )
    {
      vgscGetingData++;
    }
    
    else
    {
      vgucNmea       =  &kucaNmea[0];
      vgscGetingData =  0;
    }
}




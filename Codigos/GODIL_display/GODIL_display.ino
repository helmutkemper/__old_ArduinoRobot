
const unsigned char reset = 2;
const unsigned char clock = 3;
const unsigned char data  = 4;

void setup ()
{
  Serial.begin ( 9600 );
  
  pinMode ( reset, OUTPUT );
  pinMode ( clock, OUTPUT );
  pinMode ( data, OUTPUT );
}

void loop ()
{
  if ( Serial.available () )
  {
    switch ( Serial.read () )
    {
      case 'r': digitalWrite ( reset, LOW ); break;
      case 'R': digitalWrite ( reset, HIGH ); break;
      
      case 'c':
      case 'C': digitalWrite ( clock, LOW );
                digitalWrite ( clock, HIGH );
                break;
                
      case '0': digitalWrite ( data, LOW ); break;
      case '1': digitalWrite ( data, HIGH ); break;
    }
  }
}

// R
// f
// b
// pt
// c
// a
// g
// d
// e
// r
// +--a--+
// |     |
// f     b
// |     |
// +--g--+
// |     |
// e     c
// |     |
// +--d--+
// 

//      E D G A C P B F 
// 0. - 0c0c1c0c0c0c0c0c
//      E D G A C P B F 
// 1. - 1c1c1c1c0c0c0c1c
//      E D G A C P B F 
// 2. - 0c0c0c0c1c0c0c1c
//      E D G A C P B F 
// 3. - 1c0c0c0c0c0c0c1c
//      E D G A C P B F 
// 4. - 1c1c0c1c0c0c0c0c
//      E D G A C P B F 
// 5. - 1c0c0c0c0c0c1c0c
//      E D G A C P B F 
// 6. - 0c0c0c0c0c0c1c0c
//      E D G A C P B F 
// 7. - 1c1c1c0c0c0c0c1c
//      E D G A C P B F 
// 8. - 0c0c0c0c0c0c0c0c
//      E D G A C P B F 
// 9. - 1c0c0c0c0c0c0c0c
//      E D G A C P B F 
// A. - 0c1c0c0c0c0c0c0c
//      E D G A C P B F 
// b. - 0c0c0c1c0c0c1c0c
//      E D G A C P B F 
// C. - 0c0c1c0c1c0c1c0c
//      E D G A C P B F 
// d. - 0c0c0c1c0c0c0c1c
//      E D G A C P B F 
// E. - 0c0c0c0c1c0c1c0c
//      E D G A C P B F 
// F. - 0c1c0c0c1c0c1c0c

//      E D G A C P B F 
//  0 - 0c0c1c0c0c1c0c0c
//      E D G A C P B F 
//  1 - 1c1c1c1c0c1c0c1c
//      E D G A C P B F 
//  2 - 0c0c0c0c1c1c0c1c
//      E D G A C P B F 
//  3 - 1c0c0c0c0c1c0c1c
//      E D G A C P B F 
//  4 - 1c1c0c1c0c1c0c0c
//      E D G A C P B F 
//  5 - 1c0c0c0c0c1c1c0c
//      E D G A C P B F 
//  6 - 0c0c0c0c0c1c1c0c
//      E D G A C P B F 
//  7 - 1c1c1c0c0c1c0c1c
//      E D G A C P B F 
//  8 - 0c0c0c0c0c1c0c0c
//      E D G A C P B F 
//  9 - 1c0c0c0c0c1c0c0c
//      E D G A C P B F 
//  A - 0c1c0c0c0c1c0c0c
//      E D G A C P B F 
//  b - 0c0c0c1c0c1c1c0c
//      E D G A C P B F 
//  C - 0c0c1c0c1c1c1c0c
//      E D G A C P B F 
//  d - 0c0c0c1c0c1c0c1c
//      E D G A C P B F 
//  E - 0c0c0c0c1c1c1c0c
//      E D G A C P B F 
//  F - 0c1c0c0c1c1c1c0c

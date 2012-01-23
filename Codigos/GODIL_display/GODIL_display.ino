const unsigned char GODILdigitsWidthOutPoint[16] =  { 0b00100000, 0b11110001, 0b00001001, 0b10000001, 0b11010000, 0b10000010, 0b00000010, 0b11100001, 0b00000000, 0b10000000, 0b01000000, 0b00010010, 0b00101010, 0b00010001, 0b00001010, 0b01001010 };

const unsigned char l0 =  0b00100000 ;
const unsigned char l1 =  0b11110001 ;
const unsigned char l2 =  0b00001001 ;
const unsigned char l3 =  0b10000001 ;
const unsigned char l4 =  0b11010000 ;
const unsigned char l5 =  0b10000010 ;
const unsigned char l6 =  0b00000010 ;
const unsigned char l7 =  0b11100001 ;
const unsigned char l8 =  0b00000000 ;
const unsigned char l9 =  0b10000000 ;
const unsigned char lA =  0b01000000 ;
const unsigned char lb =  0b00010010 ;
const unsigned char lC =  0b00101010 ;
const unsigned char ld =  0b00010001 ;
const unsigned char lE =  0b00001010 ;
const unsigned char lF =  0b01001010 ;

const unsigned char L0 =  0b00100100;
const unsigned char L1 =  0b11110101;
const unsigned char L2 =  0b00001101;
const unsigned char L3 =  0b10000101;
const unsigned char L4 =  0b11010100;
const unsigned char L5 =  0b10000110;
const unsigned char L6 =  0b00000110;
const unsigned char L7 =  0b11100101;
const unsigned char L8 =  0b00000100;
const unsigned char L9 =  0b10000100;
const unsigned char LA =  0b01000100;
const unsigned char Lb =  0b00010110;
const unsigned char LC =  0b00101110;
const unsigned char Ld =  0b00010101;
const unsigned char LE =  0b00001110;
const unsigned char LF =  0b01001110;

const unsigned char reset = 2;
const unsigned char clock = 3;
const unsigned char data  = 4;

void setup ()
{
  unsigned char contador   =  0;
  
  Serial.begin ( 1200 );
  
  pinMode ( reset, OUTPUT );
  pinMode ( clock, OUTPUT );
  pinMode ( data, OUTPUT );
  
  toGODIL ( L0 );
  toGODIL ( L0 );
  toGODIL ( L0 );
  
  Serial.write ( "[L1][RMArduino             ][F]" );
  delay ( 1000 );
  
  toGODIL ( L0 );
  toGODIL ( L0 );
  toGODIL ( L1 );
}

void toGODIL ( unsigned char vaucDataToSend )
{
  unsigned char vlucBitCounter;
  
  for ( unsigned char vlucBitCounter = 0; vlucBitCounter != 8; vlucBitCounter ++ )
  {
    digitalWrite ( data, bitRead ( vaucDataToSend, 7 ) );
    
    digitalWrite ( clock, LOW );
    digitalWrite ( clock, HIGH );
    
    vaucDataToSend =  vaucDataToSend << 1;
  }
  
  digitalWrite ( reset, HIGH );
  digitalWrite ( reset, LOW );
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

// look for IR codes and print them as they are received

#include <NECIRrcv.h>
#define IRPIN 4    // pin that IR detector is connected to

NECIRrcv ir(IRPIN) ;

void setup()
{
  Serial.begin( 19200 ) ;
  Serial.println("NEC IR code reception") ;
  ir.begin() ;
}

void loop()
{
  unsigned long ircode ;
  
  while (ir.available()) {
    ircode = ir.read() ;
    ir.flush();
    Serial.print("got code: 0x") ;
    Serial.println(ircode,HEX) ;
  }
}
 
/*
+-----+
|     |
| (O) |
|     |
+--+--+
|  |  |
|  |  R  220Ω
|  |  |
|  |  |  vcc
|  |
|  | terra
|
| dado

NEC IR code reception
got code: 0xBA45FF00 power
got code: 0xB946FF00 mode
got code: 0xB847FF00 mute
got code: 0xBB44FF00 play/pause
got code: 0xBF40FF00 voltar
got code: 0xBC43FF00 avancar
got code: 0xF807FF00 eq
got code: 0xEA15FF00 v-
got code: 0xF609FF00 v+
got code: 0xE916FF00 0
got code: 0xE619FF00 rpt
got code: 0xF20DFF00 u/sd
got code: 0xF30CFF00 1
got code: 0xE718FF00 2
got code: 0xA15EFF00 3
got code: 0xF708FF00 4
got code: 0xE31CFF00 5
got code: 0xA55AFF00 6
got code: 0xBD42FF00 7
got code: 0xAD52FF00 8
got code: 0xB54AFF00 9
*/

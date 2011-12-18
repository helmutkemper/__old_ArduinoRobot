#include <SayItModule.h>
#include <Servo.h>

#define kpProximoPasso           255
#define debug_robot
#define tempoGrau                  4

const byte pinoLed             =  13;
const byte pinoUltrasom        =   2;
const byte pinoServoHorizontal =   9;
const byte pinoServoVertical   =  10;

const byte pinoMotorDireitaA   =  31;
const byte pinoMotorDireitaB   =  33;

const byte pinoMotorEsquerdaA  =  49;
const byte pinoMotorEsquerdaB  =  51;

const byte pinoCorrenteServoHorizontal   =  14;
const byte pinoCorrenteServoVertical     =  15;




// 
// Reconhecimento de voz
// 
boolean       vgbRecVozIniciado         =  false;
unsigned char vgucRecVozGrupo           =  0;
unsigned char vgucaRecVozComandos[ 5 ]  =  { CommandList::Break, CommandList::LanguageEnglish, CommandList::TimeOutInfinite, CommandList::recCustomTrigger, CommandList::Free };

// 
// Servos
// 
Servo ServoHorizontal;
Servo ServoVertical;

// 
// Timers
// 
unsigned long vgulTempoAtual     =  millis ();
unsigned long vgulTempoEsperado  =  millis ();

// 
// Maquinas de estados
// 

#if defined ( debug_robot )
boolean vgbRetornoMaquinaEstadosDebug   =  false;
#endif

void ( * vgfapMSPassos[ 5 ] ) ()     =  { 0, 0, 0, 0, 0 };
void ( * vgfapMSSubPassos[ 5 ] ) ()  =  { 0, 0, 0, 0, 0 };

unsigned char vgucMSEndereco;
unsigned char vgucMSSubEndereco;
unsigned char vgbMSSubPassoOcupada   =  false;

//
// comando - rotacione o sensor
//

unsigned char vgucaAngulo[3];
unsigned char vgucEnderecoAngulo;






namespace recVoz
{
  enum eReconhecimentoVoz
  {
    porFavor,

    apresente_se,
    escaneie_a_area,
    explore_o_local,
    pare,
    desligue_se,
    aceite_o_comando,
    
    mova_se,
    gire,
    rotacione_sensor,
    suba_o_sensor,
    desca_o_sensor,
    alinhe_sensores,
    
    para_frente,
    para_traz,
    para_a_direita,
    para_a_esquerda,
    
    zero,
    um,
    dois,
    tres,
    quatro,
    cinco,
    seis,
    sete,
    oito,
    nove,
    graus,
    
    informe
  };
}
using namespace recVoz;

//boolean       pass             =  false;
//byte          apontadorSerial  =  0;
//byte          portaSerial[ 5 ];
//int           servoTempo;
//long          *duracao;





// **************************************************************************************************************************************************************************************************
// 
// Servos - Inicio
// 
// **************************************************************************************************************************************************************************************************

void desligueServos ()
{
  #if defined ( debug_robot )
  Serial.println ( "desligueServos ()" );
  #endif
  
  ServoHorizontal.detach ();
  ServoVertical.detach ();
  vgbRecVozIniciado =  false;
}

void iniciarServos ()
{
  #if defined ( debug_robot )
  Serial.println ( "iniciarServos ()" );
  #endif
  
  //setTempo ( tempoGrau * 180 );
  
  ServoHorizontal.attach ( pinoServoHorizontal );
  ServoHorizontal.write ( 90 );
  
  ServoVertical.attach ( pinoServoVertical );
  ServoVertical.write ( 90 );
}

void centralizaServos ()
{
  #if defined ( debug_robot )
  Serial.println ( "centralizaServos ()" );
  #endif
  
  setTempo ( tempoGrau * 180 );
  
  ServoHorizontal.write ( 90 );
  ServoVertical.write ( 90 );
}

void servoHorizontalRelativo ( int vasiAnguloRelativo )
{
  #if defined ( debug_robot )
  Serial.println ( "servoHorizontalRelativo ()" );
  #endif
  
  vasiAnguloRelativo  +=  ServoHorizontal.read ();
  ServoHorizontal.write ( vasiAnguloRelativo );
}

void servoHorizontalAbsoluto ( unsigned int vauiAnguloAbsoluto )
{
  #if defined ( debug_robot )
  Serial.println ( "servoHorizontalAbsoluto ()" );
  #endif
  
  ServoHorizontal.write ( vauiAnguloAbsoluto );
}

void servoVerticalRelativo ( int vasiAnguloRelativo )
{
  #if defined ( debug_robot )
  Serial.println ( "servoVerticalRelativo ()" );
  #endif
  
  vasiAnguloRelativo  +=  ServoHorizontal.read ();
  ServoVertical.write ( vasiAnguloRelativo );
}

void servoVerticalAbsoluto ( unsigned int vauiAnguloAbsoluto )
{
  #if defined ( debug_robot )
  Serial.println ( "servoVerticalAbsoluto ()" );
  #endif
  
  ServoVertical.write ( vauiAnguloAbsoluto );
}

// **************************************************************************************************************************************************************************************************
// 
// Servos - Fim
// 
// **************************************************************************************************************************************************************************************************







// **************************************************************************************************************************************************************************************************
// 
// Maquinas de estados - Inicio
// 
// **************************************************************************************************************************************************************************************************

void MaqEstdRun ( unsigned char vaucEndereco )
{
  /*if ( testaFimTempo () == false )
    Serial.println ( "Abortado por tempo" );*/
  
  if ( vgbMSSubPassoOcupada == true )
    Serial.println ( "Abortado por sub maquina" );
  
  if ( vaucEndereco != kpProximoPasso )
  {
    vgucMSEndereco =  vaucEndereco;
    
    #if defined ( debug_robot )
    Serial.print ( "Endereco recebido: " );
    Serial.println ( String ( vgucMSEndereco ) );
    #endif
  }
  /*#if defined ( debug_robot )
  else
  {
    Serial.print ( "Proximo passo" );
  }
  #endif*/
  
  
  if ( /*( testaFimTempo () == false ) ||*/ ( vgfapMSPassos[ vgucMSEndereco ] == 0 ) /*|| ( vgbMSSubPassoOcupada == true )*/ )
  {
    #if defined ( debug_robot )
    if ( vgbRetornoMaquinaEstadosDebug == true )
    {
      vgbRetornoMaquinaEstadosDebug =  false;
      Serial.println ( "MaqEstdRun ()" );
      Serial.println ( "Retornou por nao haver proximo passo" );
    }
    #endif
    return;
  }
  
  #if defined ( debug_robot )
    Serial.println ( "MaqEstdRun ()" );
  
    switch ( vaucEndereco )
    {
      case 0:   Serial.println ( "Endereco: 0" ); break;
      case 1:   Serial.println ( "Endereco: 1" ); break;
      case 2:   Serial.println ( "Endereco: 2" ); break;
      case 3:   Serial.println ( "Endereco: 3" ); break;
      case 4:   Serial.println ( "Endereco: 4" ); break;
      case 5:   Serial.println ( "Endereco: 5" ); break;
      case 255: Serial.println ( "Endereco: 255" ); break;
      default:  Serial.println ( "Endereco: erro!" );
    }
  #endif
  
  ( * vgfapMSPassos[ vgucMSEndereco ++ ] ) ();
  
  #if defined ( debug_robot )
    if ( vgfapMSPassos[ vgucMSEndereco ] == 0 )
      Serial.println ( "Todos os passos executados" );
  #endif
}

void MaqSubEstdRun ( byte vabtEndereco )
{
  #if defined ( debug_robot )
  Serial.println ( "MaqSubEstdRun ()" );
  #endif
  
  if ( testaFimTempo () == false )
    return;
    
  if ( vgfapMSSubPassos[ vgucMSSubEndereco ] == 0 )
  {
    vgbMSSubPassoOcupada =  false;
    return;
  }
    
  vgbMSSubPassoOcupada =  true;
    
  if ( vabtEndereco != kpProximoPasso )
  {
    vgucMSSubEndereco =  vabtEndereco;
  }
  
  (*vgfapMSSubPassos[ vgucMSSubEndereco ++ ])();
}

// **************************************************************************************************************************************************************************************************
// 
// Maquinas de estados - Fim
// 
// **************************************************************************************************************************************************************************************************







// **************************************************************************************************************************************************************************************************
// 
// Ultrasom - Inicio
// 
// **************************************************************************************************************************************************************************************************

long sensorDistanciaCM ( byte pinoSensor )
{
  #if defined ( debug_robot )
  Serial.println ( "sensorDistanciaCM ()" );
  #endif
  
  pinMode ( pinoSensor, OUTPUT );
  digitalWrite ( pinoSensor, LOW );
  delayMicroseconds ( 2 ) ;
  digitalWrite ( pinoSensor, HIGH );
  delayMicroseconds ( 5 );
  digitalWrite ( pinoSensor, LOW );
  pinMode ( pinoSensor, INPUT );
  
  return pulseIn ( pinoSensor, HIGH ) / 29 / 2;
}

// **************************************************************************************************************************************************************************************************
// 
// Ultrasom - Fim
// 
// **************************************************************************************************************************************************************************************************







// **************************************************************************************************************************************************************************************************
// 
// Reconhecimento de voz - Inicio
// 
// **************************************************************************************************************************************************************************************************

void recVozSetup ()
{
  #if defined ( debug_robot )
  Serial.println ( "recVozSetup ()" );
  #endif
  
  SayItModule::vcucpMemory = &vgucaRecVozComandos[ 0 ];
  SayItModule::setSerial ( SerialPort::Port1 );
  SayItModule::defineEventFunction ( &recVozReconheceu, Reconhecimento );
  SayItModule::defineEventFunction ( &recVozErro, Erro );
  SayItModule::defineEventFunction ( &recVozLivre, Livre );
  SayItModule::start ();
  
  
  // apagar
  //ServoVertical.attach ( pinoServoHorizontal );
  //ServoVertical.write  ( 90 );
  
}

void recVozReconheceu ( unsigned char vaucIndex )
{
  #if defined ( debug_robot )
  Serial.println ( "recVozReconheceu ()" );
  #endif
  
  digitalWrite ( pinoLed, HIGH );
  delay ( 200 );
  digitalWrite ( pinoLed, LOW );
  
  //vgsiaMSMemoria[ vgucMSEndereco ]
  switch ( vgucRecVozGrupo )
  {
    case 0:
      
      switch ( vaucIndex )
      {
        case 'A': //por favor
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 0 - Comando A" );
          #endif
          
          if ( vgbRecVozIniciado == false )
          {
            vgfapMSPassos[ 0 ] =  &iniciarServos;
            vgfapMSPassos[ 1 ] =  &setRecVozGrupo1;
            vgfapMSPassos[ 2 ] =  0;
            
            vgbRecVozIniciado           =  true;
          }
          
          else
          {
            vgfapMSPassos[ 0 ] =  &setRecVozGrupo1;
            vgfapMSPassos[ 1 ] =  0;
          }
          
          MaqEstdRun ( 0 );
          
          #if defined ( debug_robot )
          vgbRetornoMaquinaEstadosDebug   =  true;
          #endif
          
          break;
      }
      
      break;
      
    case 1:
    
      switch ( vaucIndex )
      {
    
        case 'A': // apresente-se
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 1 - Comando A" );
          #endif
        
          break;
          
        case 'B': // escaneie a area
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 1 - Comando B" );
          #endif
          
          ServoHorizontal.write ( 70 );
          ServoVertical.write ( 45 );
          
          for ( unsigned int vluiVertical = 45; vluiVertical <= 135; vluiVertical += 15 )
          {
            ServoVertical.write ( vluiVertical );
            delay ( 500 );
          }
          
          centralizaServos ();
          delay ( 500 );
          
          desligueServos ();
          
          setRecVozGrupoTrigger ();
          
          break;
          
        case 'C': // explore o local
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 1 - Comando C" );
          #endif
        
          break;
          
        case 'D': // pare
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 1 - Comando D" );
          #endif
        
          break;
          
        case 'E': // desligue-se
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 1 - Comando E" );
          #endif
          
          vgfapMSPassos[ 0 ] =  &desligueServos;
          vgfapMSPassos[ 1 ] =  &setRecVozGrupoTrigger;
          vgfapMSPassos[ 2 ] =  0;
            
          MaqEstdRun ( 0 );
          
          #if defined ( debug_robot )
          vgbRetornoMaquinaEstadosDebug   =  true;
          #endif
          
          break;
          
        case 'F': // aceite o comando
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 1 - Comando F" );
          #endif
          
          vgfapMSPassos[ 0 ] =  &setRecVozGrupo2;
          vgfapMSPassos[ 1 ] =  0;
            
          MaqEstdRun ( 0 );
          
          #if defined ( debug_robot )
          vgbRetornoMaquinaEstadosDebug   =  true;
          #endif
          
          break;
      }
      
      break;
      
    case 2:
    
      switch ( vaucIndex )
      {
        
        case 'A': // mova-se
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 2 - Comando A" );
          #endif
          
          vgfapMSPassos[ 0 ] =  &setRecVozGrupoTrigger;
          vgfapMSPassos[ 1 ] =  0;
            
          MaqEstdRun ( 0 );
          
          #if defined ( debug_robot )
          vgbRetornoMaquinaEstadosDebug   =  true;
          #endif
          
          break;
          
        case 'B': // gire
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 2 - Comando B" );
          #endif
          
          vgfapMSPassos[ 0 ] =  &setRecVozGrupoTrigger;
          vgfapMSPassos[ 1 ] =  0;
            
          MaqEstdRun ( 0 );
          
          #if defined ( debug_robot )
          vgbRetornoMaquinaEstadosDebug   =  true;
          #endif
          
          break;
          
        case 'C': // rotacione o sensor
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 2 - Comando C" );
          #endif
          
          vgfapMSPassos[ 0 ] =  &setRecVozGrupo4;
          vgfapMSPassos[ 1 ] =  0;
            
          MaqEstdRun ( 0 );
          
          #if defined ( debug_robot )
          vgbRetornoMaquinaEstadosDebug   =  true;
          #endif
          
          break;
          
        case 'D': // suba o sensor
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 2 - Comando D" );
          #endif
          
          servoHorizontalAbsoluto ( 30 );
          setRecVozGrupoTrigger ();
          
          break;
          
        case 'E': // desca o sensor
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 2 - Comando E" );
          #endif
          
          servoHorizontalAbsoluto ( 150 );
          setRecVozGrupoTrigger ();
          
          break;
          
        case 'F': // alinhe sensores
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 2 - Comando F" );
          #endif
            
            vgfapMSPassos[ 0 ] =  &setRecVozGrupoTrigger;
            vgfapMSPassos[ 1 ] =  &centralizaServos;
            vgfapMSPassos[ 2 ] =  0;
            
            MaqEstdRun ( 0 );
          
          #if defined ( debug_robot )
          vgbRetornoMaquinaEstadosDebug   =  true;
          #endif
            
          break;
          
      }
      break;
      
    case 3:
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 3 - Nao programado" );
          #endif
    
      break;
      
    case 4:
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 4 - Nao programado" );
          #endif
    
      break;
      
    case 5:
          
        case 'A': // zero
          
          #if defined ( debug_robot )
          Serial.println ( "grupo 2 - Comando C" );
          #endif
          
          vgfapMSPassos[ 0 ] =  &setRecVozGrupo4;
          vgfapMSPassos[ 1 ] =  0;
            
          MaqEstdRun ( 0 );
          
          #if defined ( debug_robot )
          vgbRetornoMaquinaEstadosDebug   =  true;
          #endif
          
          break;
        
        case 'B': // um
          
          break;
          
        case 'C': // dois
          
          break;
          
        case 'D': // tres
          
          break;
          
        case 'E': // quatro
          
          break;
          
        case 'F': // cinco
          
          break;
          
        case 'G': // seis
          
          break;
          
        case 'H': // sete
          
          break;
          
        case 'I': // oito
          
          break;
          
        case 'J': // nove
          
          break;
          
      break;
  }
}




void rotacioneSensorInicio ()
{
  vgucaAngulo[ 0 ]   =  0;
  vgucaAngulo[ 1 ]   =  0;
  vgucaAngulo[ 2 ]   =  0;
  vgucEnderecoAngulo =  0;  
}







void setRecVozGrupoTrigger ()
{
  #if defined ( debug_robot )
  Serial.println ( "setRecVozGrupoTrigger ()" );
  #endif
  
  vgucRecVozGrupo               =  0;
  vgucaRecVozComandos[ 0 ]      =  CommandList::recCustomTrigger;
  vgucaRecVozComandos[ 1 ]      =  CommandList::Free;
  SayItModule::vcucpMemory      =  &vgucaRecVozComandos[ 0 ];
  SayItModule::execute ();
}

void setRecVozGrupo1 ()
{
  #if defined ( debug_robot )
  Serial.println ( "setRecVozGrupo1 ()" );
  #endif
  
  vgucRecVozGrupo               =  1;
  vgucaRecVozComandos[ 0 ]      =  CommandList::recCustomGroup1;
  vgucaRecVozComandos[ 1 ]      =  CommandList::Free;
  SayItModule::vcucpMemory      =  &vgucaRecVozComandos[ 0 ];
  SayItModule::execute ();
}

void setRecVozGrupo2 ()
{
  #if defined ( debug_robot )
  Serial.println ( "setRecVozGrupo2 ()" );
  #endif
  
  vgucRecVozGrupo               =  2;
  vgucaRecVozComandos[ 0 ]      =  CommandList::recCustomGroup2;
  vgucaRecVozComandos[ 1 ]      =  CommandList::Free;
  SayItModule::vcucpMemory      =  &vgucaRecVozComandos[ 0 ];
  SayItModule::execute ();
}

void setRecVozGrupo3 ()
{
  #if defined ( debug_robot )
  Serial.println ( "setRecVozGrupo3 ()" );
  #endif
  
  vgucRecVozGrupo               =  3;
  vgucaRecVozComandos[ 0 ]      =  CommandList::recCustomGroup3;
  vgucaRecVozComandos[ 1 ]      =  CommandList::Free;
  SayItModule::vcucpMemory      =  &vgucaRecVozComandos[ 0 ];
  SayItModule::execute ();
}

void setRecVozGrupo4 ()
{
  #if defined ( debug_robot )
  Serial.println ( "setRecVozGrupo4 ()" );
  #endif
  
  vgucRecVozGrupo               =  4;
  vgucaRecVozComandos[ 0 ]      =  CommandList::recCustomGroup4;
  vgucaRecVozComandos[ 1 ]      =  CommandList::Free;
  SayItModule::vcucpMemory      =  &vgucaRecVozComandos[ 0 ];
  SayItModule::execute ();
}

void setRecVozGrupo5 ()
{
  #if defined ( debug_robot )
  Serial.println ( "setRecVozGrupo5 ()" );
  #endif
  
  vgucRecVozGrupo               =  5;
  vgucaRecVozComandos[ 0 ]      =  CommandList::recCustomGroup5;
  vgucaRecVozComandos[ 1 ]      =  CommandList::Free;
  SayItModule::vcucpMemory      =  &vgucaRecVozComandos[ 0 ];
  SayItModule::execute ();
}

void recVozErro ( unsigned char vaucIndex )
{
  
  #if defined ( debug_robot )
  Serial.println ( "recVozErro ()" );
  #endif
  
}

void recVozLivre ( unsigned char vaucIndex )
{
  
  #if defined ( debug_robot )
  Serial.println ( "recVozLivre ()" );
  #endif
  
}

// **************************************************************************************************************************************************************************************************
// 
// Reconhecimento de voz - Fim
// 
// **************************************************************************************************************************************************************************************************







// **************************************************************************************************************************************************************************************************
// 
// Timers - Inicio
// 
// **************************************************************************************************************************************************************************************************

void setTempo ( unsigned long vaulMilesegundosRelativos )
{
  #if defined ( debug_robot )
  Serial.println ( "setTempo ()" );
  #endif
  
  vgulTempoAtual     =  millis ();
  vgulTempoEsperado  =  vgulTempoAtual + vaulMilesegundosRelativos;
}

boolean testaFimTempo ()
{
  #if defined ( debug_robot )
  Serial.println ( "testaFimTempo ()" );
  #endif
  
  return ( vgulTempoEsperado < millis () );
}

// **************************************************************************************************************************************************************************************************
// 
// Timers - Fim
// 
// **************************************************************************************************************************************************************************************************





const byte kbPassoVertical[ 3 ]    =  { 45, 80, 110 };
const byte kbPassoHorizontal[ 3 ]  =  { 30, 45, 90 };

byte    vgbtPassoVertical             =  0;
byte    vgbtPassoHorizontal           =  0;
boolean vgbEscanearAreaOcupado        =  false;

void escanerArea ()
{
  #if defined ( debug_robot )
  Serial.println ( "escanerArea ()" );
  #endif
  
  vgbtPassoVertical      =  0;
  vgbtPassoHorizontal    =  0;
  vgbEscanearAreaOcupado =  0;
  escanerAreaPasso ();
}

void escanerAreaPasso ()
{
  
  #if defined ( debug_robot )
  Serial.println ( "escanerAreaPasso ()" );
  #endif
  
}



void setup ()
{
  #if defined ( debug_robot )
  Serial.println ( "setup ()" );
  #endif
  
  pinMode ( pinoLed, INPUT );
  
  pinMode ( pinoMotorDireitaA, OUTPUT );
  pinMode ( pinoMotorDireitaB, OUTPUT );

  pinMode ( pinoMotorEsquerdaA, OUTPUT );
  pinMode ( pinoMotorEsquerdaB, OUTPUT );
  
  digitalWrite ( pinoMotorDireitaA, HIGH );
  digitalWrite ( pinoMotorDireitaB, LOW );

  digitalWrite ( pinoMotorEsquerdaA, HIGH );
  digitalWrite ( pinoMotorEsquerdaB, LOW );
  
  
  Serial.begin ( 9600 );
  
  analogReference ( INTERNAL1V1 );
  analogRead ( pinoCorrenteServoVertical );
  
  recVozSetup ();
}

void loop ()
{
  // Atencao - o sub passo deve rodar antes
  // MaqSubEstdRun ( kpProximoPasso );
  
  MaqEstdRun ( kpProximoPasso );
  SayItModule::run ();
  
  
  //Serial.println ( analogRead ( pinoCorrenteServoVertical ) );
  //delay (500);
//  Serial.print ( sensorDistanciaCM ( pinoUltrasom ) );
//  Serial.println ( "cm" );

/*  if ( Serial.available() )
  {
    portaSerial[ apontadorSerial ] =  Serial.read ();
    
    if ( ( portaSerial[ apontadorSerial ] == 10 ) || ( portaSerial[ apontadorSerial ] == 13 ) )
    {
      pass = true;
    }
    else
    {
      apontadorSerial ++;
    }
  }
  
  if ( pass )
  {
    /*
    switch ( apontadorSerial )
    {
      case 1:
        //Serial.println ( "0" );
        servoTempo = ( portaSerial[ 0 ] - 0x30 );
        break;
      
      case 2:
        //Serial.println ( "1" );
        servoTempo = ( portaSerial[ 1 ] - 0x30 ) + ( portaSerial[ 0 ] - 0x30 ) * 10;
        break;
        
      case 3:
        //Serial.println ( "2" );
        servoTempo = ( portaSerial[ 2 ] - 0x30 ) + ( portaSerial[ 1 ] - 0x30 ) * 10 + ( portaSerial[ 0 ] - 0x30 ) * 100;
        break;
        
      case 4:
        //Serial.println ( "3" );
        servoTempo = ( portaSerial[ 3 ] - 0x30 ) + ( portaSerial[ 2 ] - 0x30 ) * 10 + ( portaSerial[ 1 ] - 0x30 ) * 100 + ( portaSerial[ 0 ] - 0x30 ) * 1000;
        break;
        
      case 5:
        //Serial.println ( "4" );
        servoTempo = ( portaSerial[ 4 ] - 0x30 ) + ( portaSerial[ 3 ] - 0x30 ) * 10 + ( portaSerial[ 2 ] - 0x30 ) * 100 + ( portaSerial[ 1 ] - 0x30 ) * 1000 + ( portaSerial[ 0 ] - 0x30 ) * 10000;
        break;
    }
    */
    /*
    servoTempo = ( portaSerial[ 3 ] - 0x30 ) + ( portaSerial[ 2 ] - 0x30 ) * 10 + ( portaSerial[ 1 ] - 0x30 ) * 100;
    
    if ( ( portaSerial[ 0 ] == 'H' ) || ( portaSerial[ 0 ] == 'h' ) )
    {
      ServoHorizontal.write ( servoTempo );
    }
    
    else if ( ( portaSerial[ 0 ] == 'V' ) || ( portaSerial[ 0 ] == 'v' ) )
    {
      ServoVertical.write ( servoTempo );
    }
    */
//    ServoHorizontal.attach ( pinoServoHorizontal );
//    ServoHorizontal.writeMicroseconds ( servoTempo );
//    delay ( 1000 );
//    ServoHorizontal.detach ();
    
 //   Serial.println ( String ( servoTempo ) );
    /*
    pass = false;
    apontadorSerial = 0;
    Serial.flush ();
  }*/
  
}

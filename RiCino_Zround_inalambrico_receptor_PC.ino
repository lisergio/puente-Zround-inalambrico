


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


RF24 radio(15,16);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

int m,s,mu=0,md=0,su=0,sd=0,l=0,lu=0,ld=0,lc=0,led_rojo=4,led_verde=8,zround=0,RECV_PIN=10,tx=0,tx2=0,cronoiniciado=0,conectar=1;                                
long int tiempo,tiempo_inicio;
char mensaje[3];

//*********************************************************************************

void setup()
{
  Serial.begin(19200);          // Abrimos el puerto a 19200, que es la configuracion del puerto de Zround
  pinMode(led_rojo,OUTPUT);
  pinMode(led_verde,OUTPUT);
  radio.begin();
  radio.setRetries(15,15);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  delay(100);
  radio.startListening();  
  
  conectar_zround();
}

//*********************************************************************************

void loop()
{
  
}

//*********************************************************************************

void conectar_zround()              // Esperamos a la conexion del software zroud o al inicio de carrera
{
  int destello=0;                  // parpadeo del led rojo indicando la espera de la conexion  
  while (conectar==1)
  {
   if (destello<=25)
   {
    destello++;
    digitalWrite(led_rojo,LOW);
   } 
   else
   {
    digitalWrite(led_rojo,HIGH);
    destello=0;
   }
    
  while (Serial.available() > 0)    // guardamos el mensaje entrante por el puerto
  {
    for (int i = 0; i < 3; i++)
    {
       mensaje[i]=Serial.read();
       delay(50);
    }
  }

  if (mensaje[0]=='%')              // Comprobamos si es la peticion de conexion de zround " %C& "
  {
    if (mensaje[1]=='C')
    {
      if (mensaje[2]=='&')
      {

          int cuenta = 0;
          while (cuenta <= 20)
          {
          Serial.write("%A&");      // Enviamos confirmacion de la conexion  " %A& "
          delay(100);
          cuenta++;
          }
         
          int parpadeo=0;
          while (parpadeo<=5)
          {
          digitalWrite(led_rojo,HIGH);    // El led rojo parpadea 6 veces indicando la conexion
          delay(200);
          digitalWrite(led_rojo,LOW);
          delay(200);
          parpadeo++;
          } 
        mensaje[0]=('0');              
      }
    }
  }
 
  if (mensaje[0]=='%')        // Comprobamos si es el comienzo del entreno o carrera " %I& "
  {   
    if (mensaje[1]=='I')
    {
      if (mensaje[2]=='&')
      {
         digitalWrite(led_verde,HIGH);
         digitalWrite(led_rojo,LOW);
         tiempo_inicio=millis();
         conectar=0;
         cronoiniciado=1;
         zround=1;
         inicio_crono();
      }
    }
  }
  delay(50);
  }
 
}  
  
//*********************************************************************************

void inicio_crono()
{ 
while (zround==1)
{
  while (Serial.available() > 0)
  {
  for (int i = 0; i < 3; i++)
    {
     mensaje[i]=Serial.read();
     delay(50);
    }
  }   


 tiempo_inicio=millis();
 cronoiniciado=1;
 
 while (cronoiniciado==1)
 {  
  tiempo=millis()-tiempo_inicio;
  m=tiempo/60000;                     
  mu=m%10;                           
  md=(m-mu)/10;                       
  s=(tiempo/1000)-(m*60);            
  su=s%10;
  sd=(s-su)/10;                       
  l=tiempo-(s*1000)-(m*60000);        
  lu=l%10;                           
  ld=((l-lu)/10)%10;                  
  lc=(l-(ld*10)-lu)/100;                            
                         

  if ( su == 0)
  {
    if (lu==0 && ld==0 && lc==0)
    {
    Serial.print("%T");
    Serial.print(tiempo,HEX);
    Serial.println("&");
    }
  }
  if (su == 5)
  {
    if (lu==0 && ld==0 && lc==0)
    {
    Serial.print("%T");
    Serial.print(tiempo,HEX);
    Serial.println("&");
    }    
  }

    while (radio.available() )
    {            
      radio.read( &tx2, sizeof(int) );
      contar_vuelta_2();
    }

  while (Serial.available() > 0)
  {
    for (int i = 0; i < 3; i++)
    {
       mensaje[i]=Serial.read();
       delay(50);
    }
  }
  
 if (mensaje[0]=='%')          // Comprobamos si es el final del entreno o carrera " %F& "
  {
    if (mensaje[1]=='F')
      {
        if (mensaje[2]=='&')
        {
          cronoiniciado=0;
          digitalWrite(led_rojo,LOW);
          digitalWrite(led_verde,LOW);
          conectar=1;
          zround=0;
          conectar_zround();
        }
      }
   }      
}

delay(10);
}
}
//*********************************************************************************


 
void contar_vuelta_2()
{
if (tx2!=0)
{
  if (tx2<41)
  {
    Serial.print("%L0");
  }
  else
  {
    Serial.print("%L");
  }
  Serial.print(tx2 ,HEX);
  Serial.print(tiempo,HEX);
  Serial.print("&");
  Serial.println();
  tx2=0;
}
}

//*********************************************************************************



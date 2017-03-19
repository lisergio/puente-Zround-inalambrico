#include <IRremote.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(15,16);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;
int tx=0;
int tx2=0;



void setup()
{
  Serial.begin(19200);
radio.begin();
radio.setRetries(15,15);
radio.openWritingPipe(pipes[0]);
radio.openReadingPipe(1,pipes[1]);
radio.startListening();
irrecv.enableIRIn();
}

void loop()
{ 
  if (irrecv.decode(&results))       
  {
   radio.stopListening();  
    comprobar_transponder();
    bool ok = radio.write( &tx2, sizeof(int) ); 
    tx2=0;
   radio.startListening();    
    irrecv.resume();
  }

}


void comprobar_transponder()
{
if(results.value==0x10)
{
  tx2=1;
}

if(results.value==0x810)
{
  tx2=2;
}

if(results.value==0x410)
{
  tx2=3;
}

if(results.value==0xC10)
{
  tx2=4;
}

if(results.value==0x210)
{
  tx2=5;
}

if(results.value==0xA10)
{
  tx2=6;
}

if(results.value==0x610)
{
  tx2=7;
}

if(results.value==0xE10)
{
  tx2=8;
}

if(results.value==0x110)
{
  tx2=9;
}

if(results.value==0x910)
{
  tx2=10;
}

if(results.value==0x510)
{
  tx2=11;
}

if(results.value==0xD10)
{
  tx2=12;
}

if(results.value==0x310)
{
  tx2=13;
}

if(results.value==0xB10)
{
  tx2=14;
}

if(results.value==0x710)
{
  tx2=15;
}

if(results.value==0xF10)
{
  tx2=16;
}

if(results.value==0x90)
{
  tx2=17;
}

if(results.value==0x890)
{
  tx2=18;
}

if(results.value==0x490)
{
  tx2=19;
}

if(results.value==0xC90)
{
  tx2=20;
}

if(results.value==0xEAB)
{
  tx2=21;
}

if(results.value==0x6BC)
{
  tx2=22;
}
if(results.value==0x00FFFF01)
{
  tx2=23;
}
if(results.value==0x00FFFF02)
{
  tx2=24;
}
if(results.value==0x00FFFF03)
{
  tx2=25;
}
if(results.value==0x00FFFF04)
{
  tx2=26;
}
if(results.value==0x00FFFF05)
{
  tx2=27;
}
if(results.value==0x00FFFF06)
{
  tx2=28;
}
if(results.value==0x00FFFF07)
{
  tx2=29;
}
if(results.value==0x00FFFF08)
{
  tx2=30;
}
if(results.value==0x00FFFF09)
{
  tx2=31;
}
if(results.value==0x00FFFF0A)
{
  tx2=32;
}
if(results.value==0x00FFFF0B)
{
  tx2=33;
}
if(results.value==0x00FFFF0C)
{
  tx2=34;
}
if(results.value==0x00FFFF0D)
{
  tx2=35;
}
if(results.value==0x00FFFF0E)
{
  tx2=36;
}
if(results.value==0x00FFFF0F)
{
  tx2=37;
}
if(results.value==0x00FFFF10)
{
  tx2=38;
}
if(results.value==0x00FFFF11)
{
  tx2=39;
}
if(results.value==0x00FFFF12)
{
  tx2=40;
}
irrecv.resume();
}



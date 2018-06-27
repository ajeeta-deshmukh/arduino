
#include <SoftwareSerial.h>

SoftwareSerial BT(10,11); //TX,RX respectively

void setup() {
  // put your setup code here, to run once:
  
BT.begin(9600);
Serial.begin(9600);
pinMode(3,OUTPUT);
pinMode(4,OUTPUT);
}

void loop() {
 // put your main code here, to run repeatedly:
 while(BT.available()){
   delay(10);
   char c= BT.read();
   Serial.println(c);
   if(c=='a')
   {
     digitalWrite(3,HIGH);
   }
    if(c=='A')
   {
     digitalWrite(3,LOW);
   }
    if(c=='b')
   {
     digitalWrite(4,HIGH);
   }
    if(c=='B')
   {
     digitalWrite(4,LOW);
   }
 }
} 

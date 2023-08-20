// RST          9           
// SDA(SS)      10                      
// MOSI         11         
// MISO         12            
// SCK          13 

byte sda = 10;
byte rst = 9;
#include <KRrfid.h>
const int buzer=5;
const int kontak=3;
const int starter=4;
const int led=2;

void setup() {
Serial.begin(9600);
rfidBegin();
pinMode(buzer,OUTPUT);
pinMode(starter,OUTPUT);
pinMode(kontak,OUTPUT);
pinMode(led,OUTPUT);
digitalWrite(starter, LOW);
digitalWrite(kontak, LOW);
}

void loop() {
getTAG();
if(TAG!="") {
  digitalWrite(buzer, HIGH);
  delay(100);
  digitalWrite(buzer, LOW);
  digitalWrite(led, LOW);
        
  if(digitalRead(kontak)==LOW) 
  { digitalWrite(kontak,HIGH);
  digitalWrite(starter,HIGH);
  delay(1000);
  digitalWrite(starter,LOW);
  }
  else
  { digitalWrite(kontak,LOW); delay(500);
  }
  Serial.print("TAG : ");
  Serial.println(TAG);
  TAG="";    
  }
   
  }

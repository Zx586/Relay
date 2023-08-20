//Youbeagger for indonesia
//sains for education
//kunci motor ektp
#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 8

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;

int j=0;

String RFIDKey1 = "DA:34:83:82"; //kartu ID ku 
String RFIDKey2 = "F7:83:6C:B5"; //kartu ID istriku

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

  Serial.print("Tap card key: ");
  Serial.println(strID);
  if(strID.indexOf(RFIDKey1)>=0 or strID.indexOf(RFIDKey2)>=0){
    
    if(j==2){j=0;}
    if(j==0){
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      }

    if(j==1){
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
      }  
      j++;
    }
    else{
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
    }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

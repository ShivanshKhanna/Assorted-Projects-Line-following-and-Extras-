#include <SPI.h>
#include <MFRC522.h>

#define RST         9 
#define SS        10        

MFRC522 mfrc522(SS, RST);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Begin serial communication
  while (!Serial);  
  SPI.begin();      
  mfrc522.PCD_Init();   
  delay(4); 
  mfrc522.PCD_DumpVersionToSerial();  // Show details of card, card reader results after reading
  Serial.println(F("Scan Card for Data")); //User based sentence, required as a gesture where others can scan their cards for dumping their info into the serial monitor
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
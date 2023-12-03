#include <SPI.h>
#include <MFRC522.h>

#define SS 10  
#define RST 9
MFRC522 mfrc522(SS, RST);
MFRC522::MIFARE_Key key;

int block = 4;

const int SpeedA = 150;
const int SpeedB = 160;

#define ENA 3
#define ENB 5
const int IN1 = 4;
const int IN2 = 6;
const int IN3 = 7;
const int IN4 = 8;

const int drive = 400;
const int stationary = 150;

void setup() {
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(5);
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
int readBlock(int blockNumber, byte arrayAddress[]) 
{
 int largestModulo4Number=blockNumber/4*4;
 int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector
 byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
   if (status != MFRC522::STATUS_OK) {
     Serial.print(F("PCD_Authenticate() failed (read): "));
     Serial.println(mfrc522.GetStatusCodeName(status));
     return 3;//return "3" as error message
    }

byte buffersize = 18; //we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size... 
status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return 4;//return "4" as error message
   }
}

void off(){
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW );
  digitalWrite(IN4,LOW);
  delay(stationary);
}
void Forward() {
  analogWrite(ENA,SpeedA);
  analogWrite(ENB,SpeedB);
  
  digitalWrite(IN1,HIGH );
  digitalWrite(IN2,LOW );
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH );

  delay(drive);
  off();
}
void Backward() {
  analogWrite(ENA,SpeedA);
  analogWrite(ENB,SpeedB);
  
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);

  delay(drive);
  off();
}
void Left() {
  analogWrite(ENA, SpeedA);
  analogWrite(ENB, SpeedB);
  
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  delay(drive);
  off();
}
void Right() {
  analogWrite(ENA, SpeedA);
  analogWrite(ENB, SpeedB);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4,LOW);

  delay(drive);
  off();
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  byte buffer1[18];
  readBlock(block, buffer1);
  String value = "";
  for (uint8_t i = 0; i < 16; i++) {
     Serial.write(buffer1[i]);
  } 
for(uint8_t i = 0; i < 16; i++){
    byte action = buffer1[i];
    if(action == 'f'){  //changed to '?'
        Serial.println("Forward");
        Forward();
      } else if(action == 'b'){ //changed to '☐' *Much smaller in serial monitor
           Serial.println("Backward");
           Backward();
      } else if(action == 'l'){ //changed to '%'
        Serial.println("Left");
           Left();
      } else if(action == 'r'){ //changed to '⸮'
        Serial.println("Right");
        Right();
      }  else{
               Serial.println("0");
              delay(100);
           }
    }
    delay(1000);
}
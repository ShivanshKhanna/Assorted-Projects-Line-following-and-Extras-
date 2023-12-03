//Shiva's Code involves source code from Last minute Engineers and template code

//*This code uses elements from Last minute Engineers, specifically code involved with reading a block (Last minute Engineers, n.d.)
//*This code is a template that has been added onto, where this template has been provided in the classroom

//*Stated errors:
//* Conversion errors in two if statements, mostly involving byte to char
//* Repeated 0 values (default), when no character matches my listed ones, however, my card has every single character and some default characters towards the end

#include <SPI.h> //Include SPI protocol library
#include <MFRC522.h> //Include RFID library

#define SS 10  //Define signal select pin
#define RST 9 //define reset pin
 MFRC522 mfrc522(SS, RST);//Involvement of both pins required to work RFID, and to reduce and reset current draw
 MFRC522::MIFARE_Key key; //Create Mifare_key object named key

int block = 4; //block value
byte buffer1[18]; //Set up buffer, by using byte

//Motors
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
  SPI.begin();      // Begin SPI library
  mfrc522.PCD_Init();   // Init MFRC522, access to card reader details
  delay(5); //Delay required for RFID, possibly for a starting up procedure needed to ensure functionality
  Serial.begin(9600); //Begin serial monitor

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
//RFID
int readBlock(int blockNumber, byte arrayAddress[]) //Involvement of both blocknumber and array address of the RFID, mainly for reading memory values of either an external card or the reader
{
 int largestModulo4Number=blockNumber/4*4;
 int trailerBlock=largestModulo4Number+3; //Every 4 fourth block is a trailer, block, making sure that important details (security info) cannot be overwritten          //*My problem is between two asterisks (*--), mainly focused around conversion error from byte to char
 byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid)); //Status Authentication, allows transfer to take place
 if (status != MFRC522::STATUS_OK) { //Checks if statement is satisfied and completes contents
  Serial.print("PCD_Authenticate() failed (read): "); //Prints authentication failed                               
  Serial.println(mfrc522.GetStatusCodeName(status));
  return 3;//return "3" as error message
}

 byte buffersize = 18; //we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size... 
 status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
 if (status != MFRC522::STATUS_OK) { //Checking if statement is satisfied
  Serial.print("MIFARE_read() failed: "); //Failed transfer is printed
  Serial.println(mfrc522.GetStatusCodeName(status));
  return 4;//return "4" as error message
  }
}                                                                                                                                                                   // * ---------------
void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  readBlock(block, buffer1);
  String value = "";
   for (uint8_t i = 0; i < 16; i++) {
     Serial.write(buffer1[i]);
  }

   for(uint8_t i = 0; i <16; i++){
     switch (buffer1[i]){
      case 'f':
        Serial.println("Forward");
        Forward();
        break;
      case 'b':
        Serial.println("Backward");
        Backward();
        break;
      case 'l':
        Serial.println("Left");
        Left();
        break;
      case 'r':
        Serial.println("Right");
        Right();
        break;
      default:
        Serial.println("0");
        Forward();
        delay(100);
        break; 

//case //'m'
//Serial.println("Rotate Left");  //This is a future plan for involving the micro-servo
//break;
//case 's'
//Serial.println("Rotate right")
//break 
    }
    value += (char)buffer1[i];
  }
  value.trim();
  Serial.println(value);
    delay(1000);
}
//Motors
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
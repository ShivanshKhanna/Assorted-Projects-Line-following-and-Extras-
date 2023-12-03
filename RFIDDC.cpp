 *    2) Setup scanning of a card into the buffer variable
 *    3) Set the HIGH and LOW values in the functions
 *    4) ???

const int SpeedA = 240;
const int SpeedB = 250;

#define ENA 3
#define ENB 5
const int IN1 = 4;
const int IN2 = 6;
const int IN3 = 7;
const int IN4 = 8;

const int driveTime = 400;
const int stationary = 150;

int block = 4;
byte readbackblock[18];

void setup() {
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {

readBlock(block, readbackblock);
mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  // This is where our values from our will come in
  byte buffer1[18];

  // This is used to write out the string of commands at the end
  String value = "";
  for (uint8_t i = 0; i < 16; i++)
  {
    // You will read the value from the card (stored in block 4) into byte1 here



    switch (uffer1[i]){
      case 'f':
       Serial.println("Forward");
        forward();
        break;
      case 'F':
       Serial.println("Forward");
        forward();
        break;

      case 'b':
       Serial.println("Backward");
        backward();
        break;
      case 'B':
     Serial.println("Backward");
        backward();
        break;

      case 'l':
Serial.println("Left");
        left();
        break;
      case 'L':
Serial.println("Left");
        left();
        break;

      case 'r':
Serial.println("Right");
        right();
        break;
     case 'R':
Serial.println("Right");
        right();
        break;

      default:
        Serial.println("No");
        delay(100);
        break;
      }
    value += (char)buffer1[i];
  }
  value.trim();
  Serial.println(value);
  delay(1000);
}

void off(){
  analogWrite(ENA, 0 );
  analogWrite(ENB, 0);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW );
  digitalWrite(IN4,LOW);
  delay(stationary);
}
void forward() {
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
  
  digitalWrite(IN1,HIGH );
  digitalWrite(IN2,LOW );
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH );

  delay(driveTime);
  off();
}
void backward() {
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
  
  digitalWrite(IN1,LOW );
  digitalWrite(IN2,HIGH );
  digitalWrite(IN3,HIGH );
  digitalWrite(IN4,LOW );

  delay(driveTime);
  off();
}
void left() {
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
  
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);

  delay(driveTime);
  off();
}
void right() {
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB);
  
  digitalWrite(IN1, HIGH );
  digitalWrite(IN2,LOW );
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4,LOW );

  delay(driveTime);
  off();
}
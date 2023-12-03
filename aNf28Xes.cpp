#include <QTRSensors.h>

QTRSensors qtr;
const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];

const int SpeedA = 200;
const int SpeedB = 190;

const int ENA = 3;
const int ENB = 5;
const int IN1 = 4;
const int IN2 = 6;
const int IN3 = 7;
const int IN4 = 8;
const int drive = 50;

void setup() {
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3}, SensorCount);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // turn on Arduino's LED to indicate we are in calibration mode

  // Call calibrate() 400 times to make calibration take about 10 seconds.
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.begin(9600);                                           
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  delay(1000);
}
void off(){
  analogWrite(ENA,0);
  analogWrite(ENB,0);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW );
  digitalWrite(IN4,LOW);
  delay(100);
}
void forward() {
  analogWrite(ENA,SpeedA);
  analogWrite(ENB,SpeedB);
  
  digitalWrite(IN1,LOW );
  digitalWrite(IN2,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(IN3,HIGH );
 
  delay(drive);
  off();
}
void left() {
  analogWrite(ENA, SpeedA);
  analogWrite(ENB, SpeedB);
  
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
 
  delay(drive);
  off();
}
void right() {
  analogWrite(ENA, SpeedA);
  analogWrite(ENB, SpeedB);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4,LOW);
 
  delay(drive);
  off();
}

void loop() {
  uint16_t position = qtr.readLineBlack(sensorValues);
  qtr.readCalibrated(sensorValues);
  for (uint8_t i = 0; i < SensorCount; i++)
  {  
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(position);

//RIGHT
if(sensorValues[0] <= 1000 && sensorValues[0] >= 500 && sensorValues[1] >= 0 && sensorValues[1] < 500 && sensorValues[2] >= 0 && sensorValues[2] < 500 && sensorValues[3] >= 0 && sensorValues[3] < 500){
  right();
  return;
 } else if (sensorValues[0] <= 1000 && sensorValues[0] >= 500 && sensorValues[1] <= 1000 && sensorValues[1] >= 500 && sensorValues[2] >= 0 && sensorValues[2] < 500 && sensorValues[3] >= 0 && sensorValues[3] < 500){
      right();
      return;
      } else if  (sensorValues[0] <= 1000 && sensorValues[0] >= 500 && sensorValues[1] <= 1000 && sensorValues[1] >= 500 && sensorValues[2] <= 1000 && sensorValues[2] >= 500 && sensorValues[3] >= 0 && sensorValues[3] < 500){
          right();
          return;
} 
if(sensorValues[0] >= 0 && sensorValues[0] < 500 && sensorValues[1] >= 0 && sensorValues[1] < 500 && sensorValues[2] >= 0 && sensorValues[2] < 500 && sensorValues[3] <= 1000 && sensorValues[3] >= 500){
     left();
     return;
   } else if (sensorValues[0] >= 0 && sensorValues[0] < 500 && sensorValues[1] >= 0 && sensorValues[1] < 500 && sensorValues[2] <= 1000 && sensorValues[2] >= 500 && sensorValues[3] <= 1000 && sensorValues[3] >= 500){
      left();
      return;
      } else if (sensorValues[0] >= 0 && sensorValues[0] < 500 && sensorValues[1] >= 0 && sensorValues[1] < 500 && sensorValues[2] >= 0 && sensorValues[2] < 500 && sensorValues[3] <= 1000 && sensorValues[3] >= 500){
          left();
          return;
}
if(sensorValues[0] < 1000 && sensorValues[0] >= 500 && sensorValues[1] < 1000 && sensorValues[1] >= 500 && sensorValues[2] >= 0 && sensorValues[2] < 500 &&  sensorValues[3] < 1000 && sensorValues[3] >= 500 ){
  forward();
return;
    } else if(sensorValues[i] < 1000 && sensorValues[i] >= 500){
        right();
        } else if(sensorValues[0] >= 0 && sensorValues[0] < 500 && sensorValues[1] >= 0 && sensorValues[1] < 500 && 
    sensorValues[2] >= 0 && sensorValues[2] < 500 && sensorValues[0] >= 0 && sensorValues[0] < 500){
  left();
  }
}


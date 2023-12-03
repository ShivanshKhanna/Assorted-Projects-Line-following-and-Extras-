//Millis Function for different components
unsigned long Previoustime_MSU = millis();

//Time Periods
long MSUperiod = 5000;

//Servo
#include <Servo.h>
Servo myservo; //Attach built in controller for commands

//Ultrasonic Sensor
const int trigPin = A0; //Attaches Trigger pin to Analog pin A0
const int echoPin = A1; //Attached Echo pin to Analog pin A1

void setup()
{
  unsigned long Currentmillis = millis(); //Current Millis
  
//Ultrasonic Sensor
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT); 
Serial.begin(9600);
  
//Micro-servo
  myservo.attach(8); //Attach to pin 8
  myservo.write(90); //Rotate to 90 degrees, as a beginning value
}

void loop()
{
 unsigned long Currentmillis = millis(); //Current millis
     int cm = Ultrasonic();
  
if(Currentmillis - Previoustime_MSU > MSUperiod){ //If current milliseconds is not greater than Previous time, function will not happen
  SERVO();
  
  Previoustime_MSU = CurrentMillis;
} 
}

int Ultrasonic(){
  long duration, cm;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH);
  
    cm = duration /29 /2;
  
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    delay(100);
  

    return cm;  
}
  


void SERVO(){
   myservo.write(150);
  if(cm < 50){
     // Left Motor Rotate Backward
     // Right Motor Rotate Forward
     //Left and Right Motors move forward
    }
  delay(MSUperiod);
  myservo.write(30);
   if(cm < 50){
     // Left Motor Rotate Forward
     // Right Motor Rotate Backward
     //Left and Right Motors move forward
    }
   delay(MSUperiod);
  myservo.write(90);
}


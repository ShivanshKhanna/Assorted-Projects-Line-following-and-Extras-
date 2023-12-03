//Millis Function for different components
unsigned long Previoustime_MSU = millis();
 unsigned long Currentmillis = millis(); //Current Millis

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
  
if(Currentmillis - Previoustime_MSU > MSUperiod){ //If current milliseconds is not greater than Previous time, function will not happen
  SERVO();
  
  Previoustime_MSU = Currentmillis;
} 
}

int Ultrasonic(){                                     _______________________________________________
  long duration, cm;
    digitalWrite(trigPin, LOW);
  if(Currentmillis - Previoustime_MSU > 0.002){
    digitalWrite(trigPin, HIGH);}
    if(Currentmillis - Previoustime_MSU > 0.01){
      digitalWrite(trigPin, LOW); }
  
    duration = pulseIn(echoPin, HIGH);
  
    cm = duration /29 /2;
  
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    
    return cm;  
}
  void SERVO(){
  int cm = Ultrasonic();
  
 myservo.write(150);
  if(cm < 50){
     // Left Motor Rotate Backward
     // Right Motor Rotate Forward
     //Left and Right Motors move forward
    }
  if(Currentmillis - Previoustime_MSU > MSUperiod){
    myservo.write(30);}
   if(cm < 50){
     // Left Motor Rotate Forward
     // Right Motor Rotate Backward
     //Left and Right Motors move forward
    }
   if(Currentmillis - Previoustime_MSU > MSUperiod){
    myservo.write(30);}
  myservo.write(90);
}                                                 _____________________________________________________


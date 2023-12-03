//Millis:
unsigned long Previous_Millis = 0;

//Delay:
const int MSdelay = 20;
const int Udelay = 30;

//Micro-servo:
int Angle_1 = 90;
int Angle_2 = 150;
int Angle_3 = 30;

#include <Servo.h>
Servo myservo;

//Ultrasonic Sensor:
#include <NewPing.h>

#define TRIG A0
#define ECHO A1  
#define MAX  150 

NewPing sonar(TRIG, ECHO, MAX);

void setup() {
  myservo.attach(A5);
  myservo.write(Angle_1);
  Serial.begin(115200); //Larger rate of data bits per second, allows lines of data and other printed elements to be updated frequently.
}

void loop() {
unsigned long Current_Millis = millis(); //value approaches larger numbers, this requires long for storage of the integers.

if(Current_Millis - Previous_Millis >= MSdelay){ //Millis If loop, causes repetition every 20 miliseconds
Previous_Millis = Current_Millis; //Updated Millis counter
myservo.write(Angle_1); //First position of 90 degrees
Angle_1++; //Increase from 90 by 1 degree
delay(Udelay); //delay for 30 miliseconds
Serial.print("Distance: "); //Print distance in serial monitor
Serial.print(sonar.ping_cm()); //Print distance from ping out and in
Serial.println("cm"); //print cm after distance and create new line
if(Angle_1 == Angle_2) Angle_1 = Angle_3; //After angle of micro-servo reaches 150 degrees return to 30
}
}

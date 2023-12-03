//Millis:
unsigned long Previous_Millis = 0;

//Delay:
const int MSdelay = 20;
const int Udelay = 30;
const int SSdelay = 10;

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

//Sound Sensor
const int sound = A4;

void setup() {
  pinMode(sound, INPUT);
  myservo.attach(A5);
  myservo.write(Angle_1);
  Serial.begin(115200); 
}

void loop() {
unsigned long Current_Millis = millis();
 int current_total = 0; //Sound sensor code (set as 0)

if(Current_Millis - Previous_Millis >= SSdelay){ //Millis if statement for repetition every 10 milliseconds
 Previous_Millis = Current_Millis; //updated Millis value
 for(int i = 0; i < 100; i++){ //100 sound samples in for loop
current_total += analogRead(sound); //added values of readings
delay(5); //delayed for 5 milliseconds (small, so therefore unreasonable for another millis if statement)
 }
int avg = current_total / 100; //average sound reading
Serial.println(avg);

if(avg >= 30){ //if statement on if average reading is above 30

for(int i = 0; i < 240; i++;){ //Repeat for 240 degree increments, enough for 2 cycles
  myservo.write(Angle_1); //90 degrees
Angle_1++; //Increase by 1 degree
delay(Udelay); //Delay for ultrasonic sensor (30 milliseconds)
Serial.print("Distance: "); //print distance
Serial.print(sonar.ping_cm()); //print distance reading
Serial.println("cm"); //print cm and create new line
if(Angle_1 == Angle_2) Angle_1 = Angle_3; // Once at 150 degrees return to 30 degrees
delay(5); //after 5 milliseconds return to angle 1 (90 degrees)
 myservo.write(Angle_1); 
   }
}
}
}
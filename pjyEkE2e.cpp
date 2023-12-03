//Millis Function for different components
unsigned long PreviousMS = 0; //Value will approach larger numbers, thus requires long for data storage of numbers
int MSangle = 90; //Beginning angle
 
//Time Periods
const int MSdelay = 20; //Constant delay for micro-servo
const int UDelay = 30; //Delay for Ultrasonic Sensor pinging in and out
 
//Servo
#include <Servo.h> //Included library
Servo myservo; //Attach built-in controller for commands
#include <NewPing.h> //Library required for combining the function of the trigger and echo pins

#define TRIG A0  //Analog pin corresponding to the Trigger pin
#define ECHO A1  //Analog pin corresponding to Echo pin
#define MAXDIS 130 // Maximum distance required, changed to fit the project, a distance which will be maxed for pinging out 

NewPing sonar(TRIG, ECHO, MAXDIS); //Set up of library which has been used to define the pins required for sending out and in high-frequency waves
 
void setup()
{
  //Micro-servo
  myservo.attach(A5); //Attach to pin 8
  myservo.write(MSangle); //Rotate to 90 degrees, as a beginning value
  Serial.begin(115200); // Begin serial monitor, where the rate of data bits per second is 115200 baud allowing lines to be printed at a faster rate as opposed to 9600 baud
}
 
void loop()
{
unsigned long CurrentMS = millis(); //Value will approach larger numbers, thus requires long for data storage of numbers
 
  if(CurrentMS - PreviousMS >= MSdelay){ //If current milliseconds is not greater than Previous time, function will not happen
  PreviousMS = CurrentMS; //Required for updating and moving event
    myservo.write(MSangle); //Rotates servo to 90 degrees
   MSangle++; //Increases servo angle by 1
   delay(30);
    Serial.print("Distance from object); //Print distance and await the measured distance.
  Serial.print(sonar.ping_cm()); // Ping in and out, convert into cm and print value of 0 when measured distance is outside view of 130 cm
  Serial.println("cm");
    if(MSangle == 150) MSangle = 30; //when angle is 150 degrees, decrease by -1 to 30 degrees
}
}
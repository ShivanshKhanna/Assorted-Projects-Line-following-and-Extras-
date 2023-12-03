 
#include <NewPing.h>

#define TRIGGER_PIN  A1  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A0  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}

#include <NewPing.h>

#define TRIG A1 //pin definition of trigger pin
#define ECHO A0 //pin definition of echo pin
#define MAX 150 //Max distance detection, max distance waves are sent out

NewPing sonar(TRIG, ECHO, MAX); //Setup of pins and max distance

void setup(){
Serial.begin(9600); // Serial Monitor
}

void loop(){
  delay(10); //Delay 10ms
  Serial.print("DISTANCE: "); //print distance as a phrase
  Serial.print(sonar.ping_cm()); 
  //Complete ping out and ping in for a pulse sending waves out and recieving it, then converting into centimetres
  
  Serial.println("cm");
}

const int Input1 = 8;
const int Input2 = 7;
const int Input3 = 6;
const int Input4 = 4;

#define EnA 5
#define EnB 3

void setup() {
  // put your setup code here, to run once:
pinMode(Input1, OUTPUT); //All logic and enable pins are outputs, as an increase of speed or direction is noticeable
pinMode(Input2, OUTPUT);
pinMode(Input3, OUTPUT);
pinMode(Input4, OUTPUT);
pinMode(EnA, OUTPUT);
pinMode(EnB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(EnA, 200);
digitalWrite(Input1, HIGH); //Forwards                                                                                                                                                                                                                  
digitalWrite(Input2, LOW);

analogWrite(EnB, 200);
digitalWrite(Input3, LOW); //Forwards                                                                                                                                                                                                                  
digitalWrite(Input4, HIGH);

}

const int Input1 = 8; //Defined logic pins for Motors A and B
const int Input2 = 7;
const int Input3 = 6;
const int Input4 = 4;
#define EnableA 5 //Defined enable pins f
#define EnableB 3

void setup() {
  // put your setup code here, to run once:
pinMode(Input1, OUTPUT); //All logic and enable pins are outputs, as an increase of speed or direction is noticeable
pinMode(Input2, OUTPUT);
pinMode(EnableA, OUTPUT);
pinMode(Input3, OUTPUT);
pinMode(Input4, OUTPUT);
pinMode(EnableB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(EnableA, 200); //Similar speeds f
analogWrite(EnableB, 200);
digitalWrite(Input1, HIGH); //Forwards
digitalWrite(Input2, LOW);
digitalWrite(Input3, LOW); //Forwards
digitalWrite(Input4, HIGH);
}

//MILLIS
unsigned long Previousmillis = 0;
unsigned long Currentmillis = millis();

const int Input1 = 8; //Defined logic pins for Motors A and B
const int Input2 = 7;
const int Input3 = 6;
const int Input4 = 4;

#define EnableA 5 //Defined enable pins for controlling speed of both A and B
#define EnableB 3

void setup(){
pinMode(Input1, OUTPUT); //All logic and enable pins are outputs, as an increase of speed or direction is noticeable
pinMode(Input2, OUTPUT);
pinMode(Input3, OUTPUT);
pinMode(Input4, OUTPUT);
pinMode(EnableA, OUTPUT);
pinMode(EnableB, OUTPUT);
}

void loop(){
  LEFT();
if(millis() - Previousmillis >= 100){   //Use of millis function, everything 300 seconds
  Previousmillis = millis();
  RIGHT();
}
  if(millis() - Previousmillis >= 100){   //Use of millis function, everything 300 seconds
  Previousmillis = millis();
  }
}

void FORWARD(){
if(millis() - Previousmillis >= 300){   //Use of millis function, everything 300 seconds
  Previousmillis = millis();
analogWrite(EnableA, 200); //Similar speeds for both motors
analogWrite(EnableB, 200);

digitalWrite(Input1, HIGH); //Forwards
digitalWrite(Input2, LOW);

digitalWrite(Input3, LOW); //Motor B is placed adjacent, thus has an opposite logic output, moving it in the same direction
digitalWrite(Input4, HIGH);
}
}

void LEFT(){
analogWrite(EnableA, 155); //Differing speeds for either motor
analogWrite(EnableB, 175);

digitalWrite(Input1, LOW); //Moves Backwards at 155 speed
digitalWrite(Input2, HIGH);

digitalWrite(Input3, LOW); //Moves Forwards at 175 speed
digitalWrite(Input4, HIGH);

FORWARD(); //Completes function
}


void RIGHT(){
analogWrite(EnableA, 175); //Differing speeds
analogWrite(EnableB, 155);

digitalWrite(Input1, HIGH); //Moves Forwards at 175 speed
digitalWrite(Input2, LOW);

digitalWrite(Input3, HIGH); //Moves Backwards at 155 speed
digitalWrite(Input4, LOW);

FORWARD(); //Completes function
}
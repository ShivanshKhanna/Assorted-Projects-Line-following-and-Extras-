//MILLIS
unsigned long Previousmillis = 0;
unsigned long Currentmillis = millis();

const int Input1 = 3; //Defined logic pins for Motors A and B
const int Input2 = 4;
const int Input3 = 5;
const int Input4 = 6;

#define EnableA = 10; //Defined enable pins for controlling speed of both A and B
#define EnableB = 11;

void setup(){
pinMode(Input1, OUTPUT); //All logic and enable pins are outputs, as an increase of speed or direction is noticeable
pinMode(Input2, OUTPUT);
pinMode(Input3, OUTPUT);
pinMode(Input4, OUTPUT);
pinMode(EnableA, OUTPUT);
pinMode(EnableB, OUTPUT);
}

void FORWARD(){
if(Currentmillis - Previousmillis >= 300){   //Use of millis function, everything 300 seconds
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
}
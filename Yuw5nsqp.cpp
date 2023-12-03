const int Input1 = 8; //Defined logic pins for Motors A and B
const int Input2 = 7;
const int Input3 = 6;
const int Input4 = 4;
#define EnableA 5
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
 void FORW(){
analogWrite(EnableA, 190);
analogWrite(EnableB, 200);
digitalWrite(Input1, HIGH); //Forwards
digitalWrite(Input2, LOW);
digitalWrite(Input3, LOW); //Forwards
digitalWrite(Input4, HIGH);
}
void BACK(){
digitalWrite(Input1, LOW); //Backwards
digitalWrite(Input2, HIGH);
digitalWrite(Input3, HIGH); //Backwards
digitalWrite(Input4, LOW);
}
void LEFT(){
analogWrite(EnableA, 175); 
digitalWrite(Input1, LOW); //Backwards
digitalWrite(Input2, HIGH);
digitalWrite(Input3, LOW); //Forwards
digitalWrite(Input4, HIGH);
}
void RIGHT(){
analogWrite(EnableA, 190); 
analogWrite(EnableB, 185);
digitalWrite(Input1, HIGH); //forwards
digitalWrite(Input2, LOW);
digitalWrite(Input3, HIGH); //backwards
digitalWrite(Input4, LOW);
}

void loop() {
FORW();
delay(1000);
BACK();
delay(1000);
LEFT();
delay(1000);
RIGHT();
delay(2000);
}
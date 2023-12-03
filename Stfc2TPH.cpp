const int soundPin = A4;
int highest = 0;

int previous = 0;

 void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(soundPin, INPUT);

}

 

void loop() {
 int runningTotal = 0;
for(int i = 0; i < 100; i++){
runningTotal += analogRead(soundPin);
delay(5);
 }
int averageSound = runningTotal / 100;
Serial.println(averageSound);

 if(averageSound > highest){

    highest = averageSound;

    previous = averageSound;

    Serial.println("Highest sound recorded!");

    return;

  }

if(averageSound > previous){

    Serial.println("Higer than last time");

  }else if(averageSound < previous){

    Serial.println("Lower than last time");

  } else{

    Serial.println("Same as last time");

  }



  previous = averageSound;
}
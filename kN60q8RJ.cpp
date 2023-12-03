//Ultrasonic Sensor
const int trigPin = A1;
const int echoPin = A0;

//Millis
unsigned long Previousmillis = 0;
unsigned long Currentmillis = millis();

void setup(){
//Ultrasonic Sensor
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT); 
Serial.begin(9600);
}

void loop(){
ULTSONIC();
}

int ULTSONIC()
{
  if(Currentmillis - Previousmillis >= 21){
    Previousmillis = Currentmillis;
    
    long duration, cm;
    digitalWrite(trigPin, LOW);
    
  if(Currentmillis - Previousmillis >= 0.002){
    Previousmillis = Currentmillis;  
    digitalWrite(trigPin, HIGH);
    }
    
  if(Currentmillis - Previousmillis >= 0.01){
    Previousmillis = Currentmillis;
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH);
  
    cm = duration /29 /2;
  
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    
    if(Currentmillis - Previousmillis >= 10){
    Previousmillis = Currentmillis;
     
    return cm;  
     }
    }
  }
}
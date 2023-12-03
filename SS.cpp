const int sound = A4; //Defined sound pin

void setup(){
Serial.begin(115200); //Faster rate of data bits per second, for more sound readings(values)
pinMode(sound, INPUT); //As the sound accumulated has to be picked up by the microphone, this is an input
}

void loop(){
int current_total = 0; //total value is set to 0
for(int i = 0; i < 100; i++;){ //for loop takes 100 samples in increments
current_total += analogRead(sound); //addition of sound reading
delay(5); //has to be delayed in order for the next sample to be taken
}
int avg = total / 100; //divided by 100 to get the average sound reading since 100 samples were taken
Serial.println(avg);//prints average sound reading and creates a new line

//Average sound reading allows for general readings to be processed, this will be useful when used with other components

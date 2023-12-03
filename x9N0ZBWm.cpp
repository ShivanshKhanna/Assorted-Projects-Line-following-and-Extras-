#include <Adafruit_NeoPixel.h>
#define PIN 8
#define NUMPIXELS 2
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int red = 0;
int green = 0;
int blue = 0;

void setup (){
strip.begin();
strip.show();
strip.clear();
}

void loop(){
show(strip.Color(0, 255, 0));
delay(1000);
strip.clear();
show(strip.Color(255, 0, 0);
delay(1000);
strip.clear();
}


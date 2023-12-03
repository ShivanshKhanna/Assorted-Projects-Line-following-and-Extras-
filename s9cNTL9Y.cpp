#include <LiquidCrystal_I2C.h>
#include <Wire.h>;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
lcd.begin();
lcd.backlight();
}

void loop(){
lcd.clear(); //Clear LCD screen
delay(1000);
lcd.setCursor(0,0); //Set to first unit (top left)
lcd.print("Payment"); //Show Payment on LCD screen, only on first layer
    
lcd.setCursor(0,1); //Set to bottom left unit
lcd.print("$3.00"); //Show $3.00 on LCD screen
}
    

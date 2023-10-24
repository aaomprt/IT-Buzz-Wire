#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  pinMode(7, INPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  if (digitalRead(7) == 0){
    analogWrite(9, 100);
    tone(6, 1000, 1*1000);
    delay(1*1000);
    lcd.print("Try again")
  } else {
    analogWrite(9, 0);
    noTone(6);
  }
  delay(0.005*1000);

}
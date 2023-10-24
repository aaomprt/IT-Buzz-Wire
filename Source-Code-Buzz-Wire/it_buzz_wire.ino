#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

// ท ล ซ ม ร# ล ท ซ
#define NOTE_B5 988
#define NOTE_A5 880
#define NOTE_G5 784
#define NOTE_E5 659
#define NOTE_DS5 622

#define melodyPin 6

LiquidCrystal_PCF8574 lcd(0x27);

//song melody
int alliwant_melody[] = {
  NOTE_B5, NOTE_A5, NOTE_G5, NOTE_E5, NOTE_DS5,
  NOTE_A5,
  NOTE_B5,
  NOTE_G5
};

//song tempo
int alliwant_tempo[] = {
  4, 4, 4, 4, 4,
  2,
  4, 2
};

//byte setup
int show = -1;
byte dotOff[] = { 0b00000, 0b01110, 0b10001, 0b10001,
                  0b10001, 0b01110, 0b00000, 0b00000 };
byte dotOn[] = { 0b00000, 0b01110, 0b11111, 0b11111,
                 0b11111, 0b01110, 0b00000, 0b00000 };

void setup() {
  pinMode(7, INPUT); //Game wire
  pinMode(8, INPUT); //You won wire
  pinMode(9, OUTPUT); //LED
  pinMode(6, OUTPUT); //Buzzer
  
  //setup LCD
  int error;

  Serial.begin(115200);
  Serial.println("LCD...");

  while (!Serial)
    ;

  Serial.println("Probing for PCF8574 on address 0x27...");

  Wire.begin();
  Wire.beginTransmission(0x27);
  error = Wire.endTransmission();
  Serial.print("Error: ");
  Serial.print(error);

  if (error == 0) {
    Serial.println(": LCD found.");
    show = 0;
    lcd.begin(16, 2);  // initialize the lcd

    lcd.createChar(1, dotOff);
    lcd.createChar(2, dotOn);

  } else {
    Serial.println(": LCD not found.");
  }

}

void loop() {
  lcd.setBacklight(255);

  if (digitalRead(7) == 0){
    analogWrite(9, 100);
    tone(6, 1000, 1*1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Try again");
    delay(1*1000);
  } 
  
  else if (digitalRead(8) == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);

    //song "all i want for Christmas is you"
    int size = sizeof(alliwant_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
      analogWrite(9, 100);

      lcd.print("You Won!");

      int noteDuration = 1000 / alliwant_tempo[thisNote];

      buzz(melodyPin, alliwant_melody[thisNote], noteDuration);

      int pauseBetweenNotes = noteDuration * 1.30;
      analogWrite(9, 0);
      delay(pauseBetweenNotes);
      analogWrite(9, 100);

      buzz(melodyPin, 0, noteDuration);

      lcd.clear();
    }
  } 
  
  else {
    analogWrite(9, 0);
    noTone(6);
    lcd.setCursor(0, 0);
    lcd.print("Game Start!");
  }
  delay(0.005*1000);
}

void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000 / frequency / 2;

  long numCycles = frequency * length / 1000;

  for (long i = 0; i < numCycles; i++) {
    digitalWrite(targetPin, HIGH);        // ส่งสัญญาณ HIGH ออก
    delayMicroseconds(delayValue);        // delay ตามค่าที่คำนวณได้
    digitalWrite(targetPin, LOW);         // ส่งสัญญาณ LOW ออก
    delayMicroseconds(delayValue);        // delay ตามค่าที่คำนวณได้
  }
}


#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 10;
const int LEDPin = 6;
const int piezoPin = 8;

long duration;
int distance;

byte wall[8] = {
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011,
  0b00011
};

byte carBack[8] = {
  0b00011,
  0b00010,
  0b00010,
  0b01100,
  0b01000,
  0b01111,
  0b00011,
  0b00001
};

byte carBMid[8] = {
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11000,
  0b10000
};

byte carFMid[8] = {
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b00011,
  0b00001
};

byte carFront[8] = {
  0b11000,
  0b01000,
  0b01000,
  0b00110,
  0b00010,
  0b11110,
  0b11000,
  0b10000
};

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  Serial.begin(9600);
    
  lcd.init();
  lcd.clear();
  lcd.backlight();
}



void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.034 / 2;
  
    
  Serial.println(distance);
  
  LEDFade();
  
  piezoSound();

  showDistance();
}



void LEDFade() {
  if (distance <= 2) {
    digitalWrite(LEDPin, HIGH);
  }

  else if (distance <= 5) {
    digitalWrite(LEDPin, HIGH);
    delay(100);
    digitalWrite(LEDPin, LOW);
    delay(100);
  }
  else if (distance <= 7) {
    digitalWrite(LEDPin, HIGH);
    delay(300);
    digitalWrite(LEDPin, LOW);
    delay(200);
  }

  else if  (distance <= 10) {
    digitalWrite(LEDPin, HIGH);
    delay(500);
    digitalWrite(LEDPin, LOW);
    delay(500);
  }
  else
    digitalWrite(LEDPin, LOW);
}


void piezoSound() {
  if (distance <= 2) {
    Serial.println("BOOM");
    digitalWrite(piezoPin, HIGH);
  }

  else if (distance <= 5) {
    Serial.println("IMPACT");
    digitalWrite(piezoPin, HIGH);
    delay(100);
    digitalWrite(piezoPin, LOW);
    delay(100);
  }
  else if (distance <= 7) {
    Serial.println("Vey Close Distance");
    digitalWrite(piezoPin, HIGH);
    delay(300);
    digitalWrite(piezoPin, LOW);
    delay(200);
  }

  else if  (distance <= 10) {
    Serial.println("Close Distance");
    digitalWrite(piezoPin, HIGH);
    delay(500);
    digitalWrite(piezoPin, LOW);
    delay(500);
  }
  else
   digitalWrite(piezoPin, LOW);
}

void showDistance() {
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Distance:");

  lcd.setCursor(0, 1);
  lcd.print(distance);

  if (distance <= 2) {
  lcd.createChar(0, wall);
  lcd.createChar(1, carBack);
  lcd.createChar(2, carBMid);
  lcd.createChar(3, carFMid);
  lcd.createChar(4, carFront);
  lcd.setCursor(10, 0);
  lcd.write((byte)0);
  lcd.setCursor(10, 1);
  lcd.write((byte)0);
  lcd.setCursor(11, 1);
  lcd.write((byte)1);
  lcd.setCursor(12, 1);
  lcd.write((byte)2);
  lcd.setCursor(13, 1);
  lcd.write((byte)3);
  lcd.setCursor(14, 1);
  lcd.write((byte)4);
  }

  else if (distance <= 5) {
  lcd.createChar(0, wall);
  lcd.createChar(1, carBack);
  lcd.createChar(2, carBMid);
  lcd.createChar(3, carFMid);
  lcd.createChar(4, carFront);
  lcd.setCursor(10, 0);
  lcd.write((byte)0);
  lcd.setCursor(10, 1);
  lcd.write((byte)0);
  lcd.setCursor(12, 1);
  lcd.write((byte)1);
  lcd.setCursor(13, 1);
  lcd.write((byte)2);
  lcd.setCursor(14, 1);
  lcd.write((byte)3);
  }

  else if  (distance <= 7) {  
  lcd.createChar(0, wall);
  lcd.createChar(1, carBack);
  lcd.createChar(2, carBMid);
  lcd.createChar(3, carFMid);
  lcd.createChar(4, carFront);
  lcd.setCursor(10, 0);
  lcd.write((byte)0);
  lcd.setCursor(10, 1);
  lcd.write((byte)0);
  lcd.setCursor(13, 1);
  lcd.write((byte)1);
  lcd.setCursor(14, 1);
  lcd.write((byte)2);
  }
  
  else if  (distance <= 10) {
  lcd.createChar(0, wall);
  lcd.createChar(1, carBack);
  lcd.createChar(2, carBMid);
  lcd.createChar(3, carFMid);
  lcd.createChar(4, carFront);
  lcd.setCursor(10, 0);
  lcd.write((byte)0);
  lcd.setCursor(10, 1);
  lcd.write((byte)0);
  lcd.setCursor(14, 1);
  lcd.write((byte)1);

  }
  delay(300);
}

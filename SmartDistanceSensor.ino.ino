#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Ultrasonic pins
const int trigPin = 8;
const int echoPin = 12;
const int BuzzerPin = 10; 

long duration;
float distance;
int level;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BuzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Distance:");
}

void loop() {
  // Trigger ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

 
  duration = pulseIn(echoPin, HIGH, 30000);


  distance = duration * 0.034 / 2;

  lcd.setCursor(0, 1);
  lcd.print("                "); 
  lcd.setCursor(0, 1);
  lcd.print(distance);
  //lcd.print(" cm");

  // Map distance to buzzer frequency (closer = higher pitch)
  // Map distance to level (0–4)
  level = map(distance, 0, 100, 4, 0);
  level = constrain(level, 0, 4);

  // Map level to frequency (sound)
  int frequency = map(level, 0, 4, 700, 3000);

  // Play tone only if object is detected
  if (level > 0 && duration > 0) {
    tone(BuzzerPin, frequency);
  } else {
    noTone(BuzzerPin);
  }

  // Display LEVEL on LCD
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print("cm L:");
  lcd.print(level);


  delay(100); 
}

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buzzerPin = 6;
const int redLED = 7;
const int greenLED = 8;

const int trigPin = 9;
const int echoPin = 10;

const int tempPin = A0;

bool personWarAuf = false;

void setup()
{
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(16, 2);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART HOME");
  lcd.setCursor(0, 1);
  lcd.print("Wecker System");

  delay(3000);
}

void loop()
{
  // Abstand messen
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long dauer = pulseIn(echoPin, HIGH);
  float abstand = dauer * 0.0343 / 2;

  // Temperatur messen
  int sensorWert = analogRead(tempPin);
  float spannung = sensorWert * 5.0 / 1023.0;
  float temperatur = (spannung - 0.5) * 100;

  // Person noch nicht aufgestanden
  if (abstand < 100)
  {
    personWarAuf = false;

    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("AUFSTEHEN!");

    lcd.setCursor(0, 1);
    lcd.print("Abst:");
    lcd.print((int)abstand);
    lcd.print("cm");

    // Weckmelodie
    tone(buzzerPin, 523);
    delay(250);

    tone(buzzerPin, 659);
    delay(250);

    tone(buzzerPin, 784);
    delay(250);

    tone(buzzerPin, 659);
    delay(250);

    tone(buzzerPin, 523);
    delay(500);

    noTone(buzzerPin);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Noch im Bett");

    lcd.setCursor(0, 1);
    lcd.print("< 100 cm");

    delay(1500);
  }

  // Person ist aufgestanden
  else
  {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);

    // Erfolgsmelodie nur einmal
    if (!personWarAuf)
    {
      tone(buzzerPin, 523);
      delay(150);

      tone(buzzerPin, 659);
      delay(150);

      tone(buzzerPin, 784);
      delay(150);

      tone(buzzerPin, 1047);
      delay(300);

      noTone(buzzerPin);

      personWarAuf = true;
    }

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Person AUF!");

    lcd.setCursor(0, 1);
    lcd.print("Abst:");
    lcd.print((int)abstand);
    lcd.print("cm");

    delay(2500);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(temperatur, 1);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Abst:");
    lcd.print((int)abstand);
    lcd.print("cm");

    delay(2500);
  }
}

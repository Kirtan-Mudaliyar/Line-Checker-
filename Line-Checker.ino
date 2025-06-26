#include <LiquidCrystal.h>

int trig = 12;
int echo = 13;
int RS = 14;
int E = 16;
int D4 = 25;
int D5 = 26;
int D6 = 27;
int D7 = 4;
int button_15 = 17;
int button_20 = 18;
int button_30 = 19;
int single_buzz = 21;
int ultimate_buzz = 22;
int f = 0;
int t = 0;
int th = 0;
bool prevReading1 = HIGH;
bool prevReading2 = HIGH;
bool prevReading3 = HIGH;
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long debounceDelay = 50;
int prevDisplay = -1;

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup()
{
  Serial.begin(115200);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(button_15, INPUT_PULLUP);
  pinMode(button_20, INPUT_PULLUP);
  pinMode(button_30, INPUT_PULLUP);
  pinMode(single_buzz, OUTPUT);
  pinMode(ultimate_buzz, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  delay(100);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Enter number of");
  lcd.setCursor(0, 1);
  lcd.print("Line checks :)");
  delay(3000);
  lcd.clear();
}

void loop()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  int distance = (duration * 0.0343) / 2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm\n");
  delay(1000);
  int reading1 = digitalRead(button_15);
  int reading2 = digitalRead(button_20);
  int reading3 = digitalRead(button_30);
  unsigned long currentTime = millis();

  if (distance < 30 && distance > 0)
  {
    if (reading1 != HIGH && prevReading1 == HIGH && (currentTime - lastDebounceTime1) > debounceDelay)
    {
      lastDebounceTime1 = currentTime;
      for (int i = 1; i <= 15; i++)
      {
        f++;
        if (prevDisplay != f)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Line Checks:");
          lcd.setCursor(0, 1);
          lcd.print(f);
          prevDisplay = f;
        }
        digitalWrite(single_buzz, HIGH);
        delay(2000);
        digitalWrite(single_buzz, LOW);
      }
      digitalWrite(ultimate_buzz, HIGH);
      delay(10000);
      digitalWrite(ultimate_buzz, LOW);
    }
    prevReading1 = reading1;

    if (reading2 != HIGH && prevReading2 == HIGH && (currentTime - lastDebounceTime2) > debounceDelay)
    {
      lastDebounceTime2 = currentTime;
      for (int i = 1; i <= 20; i++)
      {
        t++;
        if (prevDisplay != t)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Line Checks:");
          lcd.setCursor(0, 1);
          lcd.print(t);
          prevDisplay = t;
        }
        digitalWrite(single_buzz, HIGH);
        delay(2000);
        digitalWrite(single_buzz, LOW);
      }
      digitalWrite(ultimate_buzz, HIGH);
      delay(10000);
      digitalWrite(ultimate_buzz, LOW);
    }
    prevReading2 = reading2;

    if (reading3 != HIGH && prevReading3 == HIGH && (currentTime - lastDebounceTime3) > debounceDelay)
    {
      lastDebounceTime3 = currentTime;
      for (int i = 1; i <= 30; i++)
      {
        th++;
        if (prevDisplay != th)
        {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Line Checks:");
          lcd.setCursor(0, 1);
          lcd.print(th);
          prevDisplay = th;
        }
        digitalWrite(single_buzz, HIGH);
        delay(2000);
        digitalWrite(single_buzz, LOW);
      }
      digitalWrite(ultimate_buzz, HIGH);
      delay(10000);
      digitalWrite(ultimate_buzz, LOW);
    }
    prevReading3 = reading3;
  }
  delay(10);
}

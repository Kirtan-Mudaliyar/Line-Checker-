#include <LiquidCrystal.h>
#include <BluetoothSerial.h>

int trig = 12;
int echo = 13;
int RS = 14;
int E = 16;
int D4 = 25;
int D5 = 26;
int D6 = 27;
int D7 = 4;
int single_buzz = 21;
int ultimate_buzz = 22;

int f = 0;
int prevDisplay = -1;
int linecheck_no = 0;  // Added here

BluetoothSerial linecheck;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

void setup() {
  Serial.begin(115200);
  linecheck.begin("ESP32 Wroom Devkit");
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
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
  delay(5000);
  lcd.clear();
}

void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  int distance = (duration * 0.0343) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (linecheck.available()) {
    linecheck_no = linecheck.parseInt();  // Better than read()
    Serial.print("Received linecheck_no: ");
    Serial.println(linecheck_no);
  }

  if (linecheck.hasClient()) {
    Serial.println("Device connected!");
    lcd.setCursor(0, 0);
    lcd.print("ESP32 Connected");
    lcd.setCursor(0, 1);
    lcd.print("Got number :)");
    delay(3000);
    lcd.clear();
  } else {
    Serial.println("Waiting for connection...");
    lcd.setCursor(0, 0);
    lcd.print("Waiting...");
  }

  if (distance < 30 && distance > 0)
   {
    for (int i = 1; i <= linecheck_no; i++)
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
    linecheck_no = 0;  // Reset after execution
  }

  delay(10);
}

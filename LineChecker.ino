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
int linecheck_no = 0;

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
  // Check connection
  if (linecheck.hasClient()) {
    lcd.setCursor(0, 0);
    lcd.print("ESP32 Connected ");
    lcd.setCursor(0, 1);
    lcd.print("Waiting number...");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Waiting for BT ");
    lcd.setCursor(0, 1);
    lcd.print("to connect...   ");
    delay(500);
    return;  // Don't proceed if no client connected
  }

  // Read number from Bluetooth
  if (linecheck.available()) {
    linecheck_no = linecheck.parseInt();  // Safer than read()
    Serial.print("Received number: ");
    Serial.println(linecheck_no);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Got number :)");
    lcd.setCursor(0, 1);
    lcd.print("Checks: ");
    lcd.print(linecheck_no);
    delay(3000);
    lcd.clear();
  }

  // Measure distance
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  int distance = (duration * 0.0343) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Start counting if within range and number is received
  if (distance < 30 && distance > 0 && linecheck_no > 0) {
    for (int i = 1; i <= linecheck_no; i++) {
      f++;
      if (prevDisplay != f) {
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
    linecheck_no = 0; // Reset for next time
  }

  delay(200);
}

#include <LiquidCrystal.h>         // For controlling the LCD
#include <BluetoothSerial.h>       // For Bluetooth communication

// Comments for the each block were added with help of chat-gp (but not logic, its purely by me)
// Pin definitions
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

// State variables
int f = 0;                         // Counter for number of line checks
int prevDisplay = -1;             // To avoid re-printing same count on LCD
int linecheck_no = 0;             // Number received from user via Bluetooth

BluetoothSerial linecheck;        // Bluetooth Serial object
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);  // LCD setup

// These are used to track timeout when no object is detected
unsigned long noObjectStartTime = 0;
bool noObjectDetected = false;

void setup() {
  Serial.begin(115200);
  linecheck.begin("LineCheck_BT");  // Start Bluetooth service

  // Setup pin modes
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(single_buzz, OUTPUT);
  pinMode(ultimate_buzz, OUTPUT);

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  delay(100);

  // Initialize LCD and show welcome message
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Enter number of");
  lcd.setCursor(0, 1);
  lcd.print("Line checks :)");
  delay(5000);
  lcd.clear();
}

void loop() {
  // 📶 Show Bluetooth connection status
  if (linecheck.hasClient()) {
    lcd.setCursor(0, 0);
    lcd.print("ESP32 Connected");         
    lcd.setCursor(0, 1);
    lcd.print("Wait for num");         
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Waiting for BT ");
    lcd.setCursor(0, 1);
    lcd.print("to connect...   ");
    delay(500);
    return; // Exit loop if not connected
  }

  // 📥 Check and read number from the app
  if (linecheck.available()) {
    linecheck_no = linecheck.parseInt();  // Safely read integer
    Serial.print("Received number: ");
    Serial.println(linecheck_no);

    // Show confirmation on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Got Line Count");
    lcd.setCursor(0, 1);
    lcd.print("Checks: ");
    lcd.print(linecheck_no);

    // Reset counters for new session
    f = 0;
    prevDisplay = -1;

    delay(3000);
    lcd.clear();
  }

  // 📏 Measure distance using ultrasonic sensor
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  int distance = (duration * 0.0343) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 🧠 Logic to count line checks or timeout

  // 🔹 Logic for sending current counted line check number when no contact is detected for more than 10s is built with help of ChatGPT
  // If distance is valid and target not yet reached
  if (linecheck_no > 0 && f < linecheck_no) {
    
    if (distance <= 25 && distance > 0) {
      // Reset timeout logic if object appears again
      noObjectDetected = false;
      noObjectStartTime = 0;

      // 🔔 Buzz and count
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
    } else {
      // 🔹 Logic for sending current count when no object detected under 10s is built with help of ChatGPT
      // Start tracking "no object" time
      if (!noObjectDetected) {
        noObjectDetected = true;
        noObjectStartTime = millis();
      } 
      // If no object for more than 10 seconds
      else if (millis() - noObjectStartTime >= 10000) {
        // Show final count and send it to app
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("No Object Here");       // ✅ Fixed: was 17 chars
        lcd.setCursor(0, 1);
        lcd.print("Final Count: ");
        lcd.print(f);

        Serial.print("Final Count Sent: ");
        Serial.println(f);
        linecheck.println(f);  // 📤 Send to app

        // Final buzz for alert
        digitalWrite(ultimate_buzz, HIGH);
        delay(5000);
        digitalWrite(ultimate_buzz, LOW);

        // Reset everything
        linecheck_no = 0;
        f = 0;
        prevDisplay = -1;
        noObjectDetected = false;

        delay(3000);
        lcd.clear();
      }
    }
  }

  delay(200);  // Short delay to avoid flooding
}

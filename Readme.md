<h1>🏃‍♂️ Line Checker – Personal Workout Counter</h1>

<p>
  <img src="images/demo.png" alt="Line Checker Demo" width="60%" />
</p>

<p>
  <b>An exercise companion that counts your line checks during workouts using push buttons, buzzers, LCD, and an ultrasonic sensor.</b>
</p>

---

## 🧠 Project Background

This project was inspired by a personal need during my exercise sessions — counting line checks manually became repetitive and error-prone.

So, I decided to apply my embedded systems knowledge to solve a real-world problem in my daily life.  
This Line Checker automatically tracks line checks based on your selection (15 / 20 / 30) and ensures focus during workouts without losing count.

---

## 📋 Features

<ul>
  <li>🚶 Real-time detection using an ultrasonic sensor</li>
  <li>🔘 Push buttons for selecting 15, 20, or 30 line check modes</li>
  <li>📟 LCD displays the current count</li>
  <li>🔊 Buzzers provide short feedback after each check and a long buzz at the end</li>
</ul>

---

## 🛠️ How It Works

<ol>
  <li>On power-up, LCD prompts: <code>Enter number of Line checks :)</code></li>
  <li>Object must be within 30 cm (i.e., proximity detection for safety or interaction)</li>
  <li>User presses one of the buttons to start the count (15/20/30)</li>
  <li>Each count:
    <ul>
      <li>Increments line check count</li>
      <li>Displays on LCD</li>
      <li>Plays short buzzer sound</li>
    </ul>
  </li>
  <li>Final count ends with a long buzzer beep</li>
</ol>

---

## 🧪 Simulation Notes

> Compatible with [Wokwi Arduino Simulator](https://wokwi.com/).  
> ⚠️ *Wokwi pushbuttons default to a "pressed" state — verify actual logic with physical hardware for accuracy.*

---

## 📌 Circuit Connections

<table>
  <tr><th>Component</th><th>Pin</th></tr>
  <tr><td>Ultrasonic Sensor (Trig)</td><td>D12</td></tr>
  <tr><td>Ultrasonic Sensor (Echo)</td><td>D13</td></tr>
  <tr><td>LCD (RS, E, D4–D7)</td><td>D14, D16, D25–D27, D4</td></tr>
  <tr><td>Button - 15 Line Checks</td><td>D17</td></tr>
  <tr><td>Button - 20 Line Checks</td><td>D18</td></tr>
  <tr><td>Button - 30 Line Checks</td><td>D19</td></tr>
  <tr><td>Single Buzzer</td><td>D21</td></tr>
  <tr><td>Final Buzzer</td><td>D22</td></tr>
</table>

---

## 📸 Hardware Setup

<p>
  <img src="images/Circuit.png" alt="Circuit Hardware Setup" width="70%" />
</p>

---

## 📁 Project Structure

```plaintext
📦 Line-Checker/
 ┣ 📜 LineChecker.ino
 ┣ 📜 README.md
 ┣ 📁 images/
 ┃ ┣ 📸 demo.png
 ┃ ┗ 📸 hardware_setup.png

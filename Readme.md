<h1 align="center">🚦 Line Checker</h1>

<p align="center">
  <img src="images/demo.png" alt="Line Checker Demo" width="60%" />
</p>

<p align="center">
  <b>A smart inspection system with ultrasonic detection, LCD, buzzers, and push buttons.</b>
</p>

---

## 📋 Features

<ul>
  <li>🎯 Detects objects using ultrasonic sensor</li>
  <li>🔘 Button modes: 15, 20, or 30 Line Checks</li>
  <li>📟 LCD shows current line check count</li>
  <li>🔊 Buzzer beeps after each count and longer beep at end</li>
</ul>

---

## 🧠 How It Works

<ol>
  <li>LCD displays: <code>Enter number of Line checks :)</code></li>
  <li>If object is within 30 cm, pressing a button starts the counter</li>
  <li>For each count:
    <ul>
      <li>LCD updates</li>
      <li>Short buzzer beep</li>
    </ul>
  </li>
  <li>After final count, long buzzer rings</li>
</ol>

---

## 🔌 Circuit Pins

<table>
  <tr><th>Component</th><th>Pin</th></tr>
  <tr><td>Ultrasonic Trig</td><td>D12</td></tr>
  <tr><td>Ultrasonic Echo</td><td>D13</td></tr>
  <tr><td>LCD RS / E / D4–D7</td><td>D14, D16, D25–D27, D4</td></tr>
  <tr><td>Button - 15 Line Checks</td><td>D17</td></tr>
  <tr><td>Button - 20 Line Checks</td><td>D18</td></tr>
  <tr><td>Button - 30 Line Checks</td><td>D19</td></tr>
  <tr><td>Single Buzzer</td><td>D21</td></tr>
  <tr><td>Final Buzzer</td><td>D22</td></tr>
</table>

---

## 🧪 Simulation Notes

> This project is compatible with the [Wokwi Arduino Simulator](https://wokwi.com/).  
> ⚠️ *Wokwi pushbuttons default to 'pressed' state — make sure to verify physical behavior during hardware implementation.*

---

## 🛠 Real-Life Tips

- Add hardware debounce if buttons are noisy.
- Ensure ultrasonic sensor is properly aligned.
- Use reliable power source for LCD and buzzers.

---

## 📁 File Structure

```plaintext
📦 Line-Checker/
 ┣ 📜 LineChecker.ino
 ┣ 📜 README.md
 ┣ 📁 images/
 ┃ ┗ 📸 demo.png
 ┃ ┗ 📸 hardware_setup.png

Optidock - Smart Parking System
  An IoT-based smart car parking solution using Arduino, ESP8266, and IR sensors to monitor parking slots in real-time.
  Integrated with a Flutter mobile app powered by Blynk IoT for displaying live availability and automated gate control.

Features
  Real-time parking slot detection using IR sensors

  Automated gate control based on slot availability

  Mobile app built with Flutter and Blynk IoT

  LCD display for on-site availability updates

  Reduces congestion and manual intervention

Hardware Used
  Arduino Uno

  ESP8266 WiFi Module

  IR Sensors

  I2C LCD Display

  Servo Motor

Software Stack
  Arduino IDE (C/C++)

  Flutter (Dart)

  Blynk IoT Platform

  Visual Studio Code

How It Works
  1) IR sensors detect vehicle presence in each slot.

  2) Arduino processes sensor input and updates LCD and ESP8266.

  3) ESP8266 sends real-time status to the Blynk cloud.

  4) Flutter app fetches and displays slot data using the Blynk API.

  5) Gate opens automatically if a free slot is available.

Optidock - Smart Parking System

Optidock is an IoT-based smart car parking system designed to optimize parking space utilization and reduce traffic congestion through automation.
The system uses Arduino Uno, ESP8266, and IR sensors to detect vehicle presence and monitor parking slot status in real-time.
A mobile application built with Flutter and Blynk IoT displays live slot availability using a grid layout with color-coded indicators.
Optidock features automated gate control based on availability, ensuring a seamless, efficient, and eco-friendly parking experience. 
Ideal for small to medium parking lots, the system minimizes manual intervention while enhancing user convenience.
________________________________________
Features

  •	Real-time parking slot detection using IR sensors
  
  •	Automated gate control based on slot availability
  
  •	Mobile app built with Flutter and Blynk IoT
  
  •	LCD display for on-site availability updates
  
  •	Reduces congestion and manual intervention
________________________________________
Hardware Used

  •	Arduino Uno
  
  •	ESP8266 WiFi Module
  
  •	IR Sensors
  
  •	I2C LCD Display
  
  •	Servo Motor
________________________________________
Software Stack

  •	Arduino IDE (C/C++)
  
  •	Flutter (Dart)
  
  •	Blynk IoT Platform
  
  •	Visual Studio Code
________________________________________
How It Works

  1.	IR sensors detect vehicle presence in each slot.
  2.	
  3.	Arduino processes sensor input and updates LCD and ESP8266.
  4.	
  5.	ESP8266 sends real-time status to the Blynk cloud.
  6.	
  7.	Flutter app fetches and displays slot data using the Blynk API.
  8.	
  9.	Gate opens automatically if a free slot is available.

# Arduino WiFi Car 🚗📡

An Arduino-powered smart car that can be remotely controlled over the internet using **port forwarding**. Designed for IoT enthusiasts, this car setup combines real-time control with wireless communication using WiFi (ESP8266/ESP32).

## 🌟 Features

- 🔧 **Arduino-Based Smart Car**  
  Uses an Arduino board connected to motors and sensors for movement and obstacle detection.

- 🌐 **WiFi Control via Port Forwarding**  
  - Control the car remotely from anywhere using internet access.
  - Set up port forwarding on the router to make the Arduino server accessible globally.

- 🧭 **Real-Time Movement**  
  - Forward, backward, left, right, and stop commands.
  - Responsive controls over a custom web interface or HTTP requests.

- 📲 **Custom Web Interface**  
  - Simple UI for remote control.
  - Accessible through the public IP and forwarded port.

- 🛑 **Basic Obstacle Avoidance** *(optional)*  
  - Ultrasonic sensor support for auto-stop or rerouting (if implemented).

## 🛠️ Tech Stack

| Component     | Use                                       |
|---------------|--------------------------------------------|
| Arduino UNO   | Core microcontroller                       |
| ESP8266/ESP32 | WiFi communication                         |
| L298N Driver  | Motor control                              |
| Motors        | Drive the wheels                           |
| Ultrasonic    | Optional: Obstacle detection               |
| Web Interface | Control the car remotely via browser       |
| Port Forwarding | Access car over the internet using IP    |

## 📁 Folder Structure


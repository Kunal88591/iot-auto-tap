# 💧 Smart Automated Water Tap System (ESP8266 + IoT Dashboard)

This project is a smart IoT-enabled **automatic water tap** system using **ESP8266**, **IR sensor**, and a **solenoid valve**. The system logs real-time usage, sends data to a backend server via WiFi, and displays all data live on a custom-built web dashboard.

---

## 🚀 Features

- ✋ Auto water flow using IR motion detection
- 📡 Wireless control with ESP8266 via WiFi
- 🔌 Solenoid valve controlled through relay
- 🌐 Data sent to live server using HTTP POST
- 📈 Real-time dashboard built with React.js
- 💾 Logs stored in MongoDB Atlas
- 📱 Optional legacy control via Blynk app

---

## 🔧 Hardware Components

| Component            | Description                            |
|----------------------|----------------------------------------|
| ESP8266 (NodeMCU)    | WiFi-enabled microcontroller           |
| IR Proximity Sensor  | Detects hand motion                   |
| Relay Module (2CH)   | Switch to control solenoid valve       |
| Solenoid Valve       | Allows or blocks water flow            |
| IN4007 Diode         | Protects against reverse EMF           |
| LM2596 Buck Converter| Voltage regulator for safe power       |
| Power Source         | 5V adapter or battery                  |

---

## 💻 Software Stack

| Layer        | Technology         | Purpose                        |
|--------------|--------------------|--------------------------------|
| Firmware     | Arduino IDE (C++)  | Program ESP8266                |
| Frontend     | React.js + Tailwind CSS | Real-time UI dashboard     |
| Backend      | Node.js + Express  | API + real-time handling       |
| Database     | MongoDB Atlas      | Store logs and usage data      |
| Real-time    | Socket.io or MQTT  | Live sync from ESP to frontend |
| Hosting      | Vercel + Render    | Deploy frontend/backend        |

---




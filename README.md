# 💧 Smart Water Tap Automation
> **Touchless | IoT-Enabled | Real-Time Monitoring | Voice Controlled**

## 📌 Introduction
**Smart Water Tap Automation** is an **IoT-powered, touchless tap system** designed to **reduce water wastage, improve hygiene, and promote sustainable living**.  
It uses **ESP8266, IR sensing, flow monitoring, Google Assistant, and Blynk IoT** for **automatic, manual, and remote control** of water flow.

---

## 🚀 Features
- **Touchless Operation** – IR proximity sensor detects hand movement.
- **IoT Remote Control** – Operate via **Blynk mobile app**.
- **Voice Control** – Google Assistant commands through **Sinric Pro**.
- **Real-Time Usage Display** – OLED shows live water consumption.
- **Auto Shutoff Safety** – 30-second timer prevents overflow.
- **Manual Override** – Push button control for emergencies.
- **Low-Cost & Scalable** – Uses affordable components.

---

## 🛠 Hardware Components
| Component | Purpose |
|-----------|---------|
| **ESP8266 (NodeMCU)** | Wi-Fi-enabled microcontroller |
| **IR Proximity Sensor** | Detects hand presence |
| **12V Solenoid Valve** | Controls water flow |
| **Relay Module** | Switch for solenoid control |
| **YF-S201 Flow Sensor** | Measures water usage |
| **OLED Display (I2C)** | Shows live water usage |
| **Push Button** | Manual override |
| **Blynk IoT Platform** | Remote control & monitoring |
| **Buck Converter (LM2596)** | Voltage regulation |

---

## 📐 System Workflow
1. **Detection** – IR sensor detects hand presence.
2. **Activation** – ESP8266 triggers relay, opening solenoid valve.
3. **Monitoring** – Flow sensor measures water usage, displayed on OLED and sent to Blynk.
4. **Safety** – Auto shutoff after 30 seconds + manual override button.
5. **Voice Control** – Commands via Google Assistant → Sinric Pro → ESP8266.

---

## 🗣 Voice Commands
- `"Hey Google, turn on the tap"`
- `"Hey Google, turn off the tap"`

---

## 📲 Mobile App (Blynk) Features
- View **real-time water consumption** remotely.
- Control tap ON/OFF from anywhere.
- Monitor system status.

---

## 🌍 Applications
- 🏥 Hospitals – Reduce contamination risk.
- 🏠 Smart Homes – Convenience + sustainability.
- 🚻 Public Restrooms – Save water in high-traffic areas.
- 🏫 Schools – Educate students on conservation.
- 🍳 Commercial Kitchens – Optimize water usage.

---

## ✅ Advantages Over Manual Taps
- Hygienic touchless use.
- Automatic shutoff prevents wastage.
- Affordable and scalable design.
- Real-time data for water conservation.

---

## 🔮 Future Scope
- AI-based predictive water usage analytics.
- Solar-powered operation for off-grid use.
- Multi-tap centralized monitoring.
- Custom Android/iOS app.

---


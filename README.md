# Smart Water Tap Automation 🚰💧

An **IoT-enabled, touchless water tap** system designed to reduce water wastage, improve hygiene, and provide **real-time monitoring** using **ESP8266, IR sensors, flow sensors, and Google Assistant integration**.

## 📜 Overview
Traditional taps contribute to significant **water wastage** and pose **hygiene risks** due to frequent touch.  
This project automates tap control using **infrared sensing**, **voice commands**, and **remote IoT monitoring** via the Blynk app, ensuring **efficiency, cleanliness, and sustainability**.

## ✨ Features
- **Touchless Operation**: IR proximity sensor triggers water flow automatically.
- **IoT Control**: Remote access through Blynk mobile app.
- **Google Assistant Integration**: Control via voice commands using Sinric Pro.
- **Real-Time Monitoring**: OLED display + app show live water usage.
- **Auto Shutoff**: 30-second timer prevents overflow.
- **Manual Override**: Push button ensures operation during failures.
- **Low-Cost & Scalable**: Uses affordable, off-the-shelf components.

## 🛠 Hardware Components
| Component | Function |
|-----------|----------|
| **ESP8266 (NodeMCU)** | Microcontroller with Wi-Fi for IoT |
| **IR Proximity Sensor** | Detects hand presence |
| **12V Solenoid Valve** | Controls water flow |
| **Relay Module** | Switch for solenoid control |
| **YF-S201 Flow Sensor** | Measures flow rate & total usage |
| **OLED Display (I2C)** | Shows real-time water usage |
| **Push Button** | Manual control |
| **Blynk IoT Platform** | Remote monitoring & control |
| **Buck Converter (LM2596)** | Voltage regulation |

## 📐 System Architecture
1. **Detection** – IR sensor detects hand presence.
2. **Activation** – ESP8266 triggers relay to open solenoid valve.
3. **Monitoring** – Flow sensor measures water usage; data sent to OLED + Blynk app.
4. **Safety** – Auto-shutoff & manual override.
5. **Voice Control** – Google Assistant commands via Sinric Pro.

## 🗣 Voice Assistant Commands
- `"Hey Google, turn on the tap"`
- `"Hey Google, turn off the tap"`

## 📲 Blynk App Functions
- View live water consumption.
- Remotely turn tap on/off.
- Monitor device status.

## 📌 Applications
- Public restrooms.
- Hospitals & healthcare facilities.
- Smart homes.
- Educational institutions.
- Commercial kitchens.

## ✅ Advantages
- Hygienic touchless use.
- Reduced water wastage.
- Affordable & scalable.
- Real-time analytics for conservation.

## 🔮 Future Scope
- AI-based predictive analytics.
- Solar-powered operation.
- Multi-tap centralized control.
- Custom mobile app for enhanced UI.


---

### 👨‍💻 Contributors
 
- **Kunal Meena** 
  
- **Sahil**  

Supervisor: **Prof. Prabin K. Padhy**  
Department of Electronics and Communication Engineering, IIITDM Jabalpur

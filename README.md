# 🌱 Greenhouse Controller with AI-Powered Crop Disease Detection, pH, and Moisture Monitoring  

This project is a **smart IoT-based greenhouse management system** that integrates:  

- 🌿 **AI-driven crop disease detection** using a trained machine learning model.  
- ⚗️ **pH monitoring and automatic control** to maintain optimal soil conditions.  
- 💧 **Soil moisture sensing and automated irrigation** to optimize water usage.  
- 📡 **Real-time sensor data monitoring** via Firebase/MQTT.  
- 🖥️ **Web dashboard (React + Firebase)** for remote control and visualization.  

## 🚀 Features  

✅ **Crop Disease Detection**: Uses an ESP32-CAM or Raspberry Pi camera to capture plant images, analyze them with an ML model, and provide disease classification & recommendations.  
✅ **Automated pH Control**: Monitors soil pH and adjusts acidity/alkalinity using a solenoid valve-based liquid dispenser.  
✅ **Soil Moisture Monitoring & Irrigation**: Detects moisture levels and activates a water pump when needed.  
✅ **Temperature & Humidity Sensing**: Ensures optimal greenhouse climate control.  
✅ **Cloud Connectivity**: Sends real-time sensor data to Firebase and allows remote access.  

## 🔧 Tech Stack & Hardware  

### **Hardware:**  
- **ESP32 / ESP32-CAM** (WiFi-enabled microcontroller)  
- **pH Sensor** (for measuring soil pH levels)  
- **Soil Moisture Sensor** (Capacitive or Resistive)  
- **DHT11/DHT22 Sensor** (Temperature & Humidity monitoring)  
- **Solenoid Valve** (For automated pH adjustment)  
- **Relay Module** (For water pump control)  
- **Water Pump** (For irrigation system)  

### **Software & Cloud:**  
- **Machine Learning Model:** TensorFlow/PyTorch for disease classification  
- **Backend:** Node.js with Firebase/MQTT for real-time data handling  
- **Frontend:** React.js with Firebase for the dashboard  

## 🚀 How to Get Started?  

1️⃣ **Set up ESP32** with sensors and connect to Firebase/MQTT.  
2️⃣ **Train & deploy the ML model** for crop disease detection.  
3️⃣ **Deploy the web dashboard** to visualize sensor data.  
4️⃣ **Automate irrigation & pH control** based on sensor readings.  

## 📌 Future Enhancements  

🌍 **Mobile App Integration** (for remote monitoring via mobile)  
🤖 **AI-based Recommendations** (for better greenhouse optimization)  
🔋 **Solar Power Integration** (to make the system energy-efficient)  

---

### 🔗 **Stay Connected!**  
Feel free to contribute, suggest improvements, or report issues! 🚀🌿  

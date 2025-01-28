# Green_House-_Automated_System
🌱 Greenhouse Controller with AI-Powered Crop Disease Detection, pH, and Moisture Monitoring


This project is a smart IoT-based greenhouse management system that integrates:

AI-driven crop disease detection using a trained machine learning model.
pH monitoring and automatic control to maintain optimal soil conditions.
Soil moisture sensing and automated irrigation to optimize water usage.
Real-time sensor data monitoring via Firebase/MQTT.
Web dashboard (React + Firebase) for remote control and visualization.
🚀 Features
✅ Crop Disease Detection: Uses an ESP32-CAM or Raspberry Pi camera to capture plant images, analyze them with an ML model, and provide disease classification & recommendations.
✅ Automated pH Control: Monitors soil pH and adjusts acidity/alkalinity using a solenoid valve-based liquid dispenser.
✅ Soil Moisture Monitoring & Irrigation: Detects moisture levels and activates a water pump when needed.
✅ Temperature & Humidity Sensing: Ensures optimal greenhouse climate control.
✅ Cloud Connectivity: Sends real-time sensor data to Firebase and allows remote access.

🔧 Tech Stack & Hardware
Hardware: ESP32, ESP32-CAM, pH sensor, Soil Moisture Sensor, DHT11/DHT22, Solenoid Valve, Relay Module, Water Pump
Software: Python (ML Model), TensorFlow, Node.js, React, Firebase, MQTT
Connectivity: WiFi-enabled ESP32 for cloud communication

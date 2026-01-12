# Moody Plant Watering System 🌱

## Abstract
The Moody Plant Watering System is an interactive plant care device that monitors multiple indicators of plant health, including soil moisture, temperature, and humidity. Using multiple Arduino microcontrollers, the system collects environmental data, automatically waters the plant when needed, and displays the plant’s “mood” using LEDs and LCD screens. By giving plants personality through visual and audio feedback, this project aims to make plant care more engaging while educating users about optimal watering and environmental conditions.

---

## Project Overview
This system automates plant watering based on real-time environmental conditions. Sensors continuously monitor soil moisture, temperature, humidity, and water level. When the soil becomes dry, the system activates a water pump to hydrate the plant to a healthy level.

Beyond automation, the system introduces a creative “mood” concept:
- **Healthy plant:** Green LED and a smiling face on the LCD  
- **Unhealthy or dry plant:** Red LED and a frowning face  
- **Low water warning:** Blue LED indicator  

This combination of functionality and creativity encourages user interaction and awareness of plant health.

---

## System Architecture (Multiple Arduinos)

### 1. Sensor Hub Arduino
- Collects environmental data
- Reads soil moisture sensor
- Reads temperature and humidity from the DHT11 sensor
- Sends all sensor data to the Main Controller via serial communication

### 2. Main Controller Arduino
- Acts as the brain of the system
- Receives and processes sensor data
- Determines plant health and watering needs
- Sends processed data to the Display Unit and Output System

### 3. Display Unit Arduino
- Provides visual feedback to the user
- Displays plant status and sensor data on an LCD
- Controls LEDs to indicate plant “mood” and water level

### 4. Output System Arduino
- Controls the water pump through a relay
- Activates a buzzer while watering
- Uses an ultrasonic sensor to measure water level
- Includes a pushbutton to change buzzer tones

---

## Communication Between Arduinos
All four Arduinos communicate using **serial communication** via RX (pin 0) and TX (pin 1).  
**Important:** All Arduinos must share a common ground.

### Data Flow
1. Sensor Hub collects environmental data and sends it to the Main Controller  
2. Main Controller processes data and determines plant status  
3. Display Unit updates LEDs and LCD based on the plant’s “mood”  
4. Output System controls watering, buzzer, and water-level monitoring  
5. Water level data is sent back into the system loop  

---

## Inputs and Outputs

### Inputs
- **Soil Moisture Sensor:** Measures soil water content
- **DHT11 Sensor:** Measures temperature and humidity
- **Ultrasonic Sensor:** Detects remaining water level
- **Push Button:** Changes buzzer tone during watering

### Outputs
- **16x2 LCD Displays:**  
  - Sensor data (temperature, humidity, moisture, water level)  
  - Plant mood (happy or sad)
- **LED Indicators:**  
  - Green: Healthy  
  - Red: Dry / Unhealthy  
  - Blue: Low water level
- **Buzzer:** Audible feedback during watering
- **Water Pump & Relay Module:** Dispenses water automatically

---

## Original Work
While many automated watering systems already exist, this project introduces an expressive “mood” concept to create a stronger emotional connection between users and their plants. By combining automation with visual and audio feedback, the system makes plant care more interactive, educational, and enjoyable.

---

## Build Notes (Hardware Setup)
⚠️ **IMPORTANT:** Ensure all Arduinos share a common ground.

### Sensor Hub Arduino
- TX (Pin 1) → Main Controller RX (Pin 0)
- Soil moisture sensor → A0 (Analog), D8 (Digital), GND
- DHT11 signal → D5, VCC → 5V, GND → GND

### Main Controller Arduino
- TX (Pin 1) → Display Unit RX (Pin 0)
- LCD connections based on `.ino` configuration

### Display Unit Arduino
- TX (Pin 1) → Output System RX (Pin 0)
- LEDs:  
  - Blue → D2  
  - Red → D3  
  - Green → D4
- LCD connections based on `.ino` configuration

### Output System Arduino
- TX (Pin 1) → Sensor Hub RX (Pin 0)
- Ultrasonic sensor:  
  - Trig → D9  
  - Echo → D10
- Relay module → D7
- Water pump powered through relay (NO)
- Buzzer → D4

---

## How to Use the System
1. Ensure all Arduinos are wired correctly and share a common ground
2. Establish serial connections between all boards (pins 0 and 1)
3. Power the system (the Output System Arduino should be connected via USB due to higher power needs)
4. Place the soil moisture sensor in the plant’s soil and position the DHT11 nearby
5. The system will begin monitoring conditions, displaying data, and watering automatically as needed

---

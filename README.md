# 🚀 ESP32 GPS Live Tracker with Web Map (Leaflet.js)

A compact live GPS tracker using **ESP32-WROOM-32** and **u-blox NEO-6M** GPS module. It displays GPS status on a **16x2 LCD** and serves a **live web map** using **Leaflet.js**, hosted locally on the ESP32 via Wi-Fi. The tracker provides **~6-meter accuracy** and is ideal for lightweight GPS tracking projects.

---

## 🛠️ Features

- ✅ Real-time GPS tracking via u-blox NEO-6M
- ✅ Local webserver hosted by ESP32
- ✅ Interactive map with [Leaflet.js](https://leafletjs.com)
- ✅ 16x2 LCD shows GPS status (`Waiting for GPS` or `GPS is ready`)
- ✅ Map auto-refreshes every 3 seconds with current GPS location
- ✅ Typical GPS accuracy: ~6 meters
- ✅ No cloud or third-party dependencies

---

## 🔌 Hardware Required

| Component         | Description                     |
|------------------|---------------------------------|
| ESP32-WROOM-32    | Main microcontroller             |
| NEO-6M GPS       | GPS receiver module (UART)       |
| 16x2 LCD         | Display (I2C preferred)           |
| Breadboard + Wires | Standard jumper wires           |
| Power supply     | 5V via USB or battery             |

---

## ⚙️ Pin Connections

| ESP32 Pin | GPS NEO-6M | LCD (via I2C) |
|-----------|------------|---------------|
| RX (GPIO16) | TX         | —             |
| TX (GPIO17) | Not used   | —             |
| 3.3V/5V     | VCC        | VCC           |
| GND         | GND        | GND           |
| SDA (GPIO21) | —         | SDA           |
| SCL (GPIO22) | —         | SCL           |

> 💡 Use `TinyGPS++` for GPS parsing and `LiquidCrystal_I2C` for the LCD.

---

## 🌐 How It Works

1. ESP32 reads live coordinates from the NEO-6M GPS module.
2. LCD shows:
   - `Waiting for GPS` when fix not acquired
   - `GPS is ready` when location is locked
3. ESP32 connects to your Wi-Fi and prints its IP via Serial.
4. Visit `http://<ESP_IP>/` in your browser to view the live map.
5. The map auto-refreshes the marker every 3 seconds with updated GPS coordinates.
   

---


## 📺 Demo Video

[https://github.com/AnasWagih25/ESP32_GPS_Live_Tracker_w_Web-Map/blob/main/assets/Demo.mp4](https://github.com/AnasWagih25/ESP32_GPS_Live_Tracker_w_Web-Map/blob/main/assets/Demo.mp4)

> 🎥 Watch a full walkthrough of the live GPS feed, LCD status display, and Leaflet map updates.

<video src="assets/demo.mp4" controls style="width:100%; max-width:600px; border-radius:8px;"></video>


## 📸 Demo Screenshot

![Leaflet Map Screenshot](https://github.com/AnasWagih25/Live_Location_Tracking_GPS/blob/main/Location%20.jpg)

## 📸 Enclosure Screenshot

![Enclosure Body Design](https://github.com/AnasWagih25/ESP32_GPS_Live_Tracker_w_Web-Map/blob/main/Enclosure.png)

---
## MADE BY

Anas Wagih X Marawan Ghazy

## 🔧 Libraries Used

- [`TinyGPS++`](https://github.com/mikalhart/TinyGPSPlus)
- [`LiquidCrystal_I2C`](https://github.com/johnrickman/LiquidCrystal_I2C)
- [`WiFi.h`](https://www.arduino.cc/en/Reference/WiFi)
- [`WebServer.h`](https://github.com/espressif/arduino-esp32)

Install all via the Arduino Library Manager.

---

## 🚀 Getting Started

1. Clone this repo:
   ```bash
   git clone https://github.com/AnasWagih25/Live_Location_Tracking_GPS.git

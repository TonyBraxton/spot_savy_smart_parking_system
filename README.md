# spot_savy_smart_parking_system
 Spot Savy – Smart Parking System
Spot Savy is a smart parking system designed using ESP32 that monitors the availability of parking slots and displays the status via a local web server. It integrates sensors, a servo motor for gate control, and safety features like flame detection and buzzer alerts.

Features:
Real-time Parking Slot Monitoring (5 slots)

Wi-Fi Web Interface (ESP32 hosted)

Automatic Gate Control via Servo Motor

Flame Detection with Alert Buzzer

Visual Indicators with LEDs

OLED Display for network credentials and IP

Manual Alert Button for emergencies

Hardware Components:
ESP32 Development Board

IR Sensors (6x) – For slot detection and entry gate

OLED Display (SSD1306)

Servo Motor (for gate control)

Flame Sensor

Buzzer

LEDs (5x)

Push Button

Network Configuration:
SSID: Rohilla

Password: 87654321

System displays local IP on OLED after connection.

Web Interface:
Access the smart parking dashboard via the IP shown on the OLED. The web UI displays:

Slot status (P = Parked, E = Empty):

ON/OFF control for each slot simulation

Buzzer and Servo controls

Setup:
Flash the code to your ESP32 using the Arduino IDE.

Power up the system and wait for it to connect to Wi-Fi.

Note the IP address on the OLED screen.

Open the IP in a browser to access the interface.

File Structure:
SpotSavy/
├── SpotSavy.ino       # Main Arduino sketch
├── README.md          # This file

Screenshots:
(You can add screenshots of your web interface and hardware setup here)

Future Improvements:
Integrate RFID-based user authentication.

Add real-time parking analytics and history.

Connect to a cloud platform for remote monitoring.

Contributors[Final Graduation Project Seneca College]
-Tony Braxton Tchio Ngoumeza
-Krusha Mistry

Systems/software Engineer Enthusiast | IoT Developer

📄 License
Custom Non-Commercial License (CNCL) - Version 1.0

Copyright (c) [2025] [Spot Savy Smart Parking System]

Permission is hereby granted, free of charge, to use, copy, modify, and distribute copies of the Software, subject to the following conditions:

1. **Non-Commercial Use**: The Software may only be used for non-commercial purposes. Commercial use of the Software is strictly prohibited unless you have obtained explicit written permission from the copyright holder.

2. **Attribution**: Redistributions of the Software must retain the original copyright notice, this list of conditions, and the following disclaimer.

3. **No Warranty**: The Software is provided "as is", without warranty of any kind, express or implied, including but not limited to the warranties of merchantability, fitness for a particular purpose, and noninfringement. In no event shall the authors or copyright holders be liable for any claim, damages, or other liability, whether in an action of contract, tort, or otherwise, arising from, out of, or in connection with the software or the use or other dealings in the software.

4. **Commercial Use Prohibition**: Any use of the Software for commercial purposes, including but not limited to resale, offering as a service, or integration into a proprietary product, is prohibited without a commercial license obtained directly from the author(s).


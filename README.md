# Smart-Plant-Monitoring-and-Protection-System
This code connects an ESP32 to Blynk for a "Smart Plant" system. It monitors temperature, humidity (DHT11), soil moisture, and motion (PIR). Data is displayed on an LCD and sent to Blynk. A relay is controlled via a button or Blynk app. Features include sensor alerts, virtual writes, and a user-friendly interface.
This system is designed to monitor the health of your plants by tracking environmental conditions such as temperature, humidity, soil moisture, and motion detection. The system provides real-time data on an LCD display and through the Blynk mobile app. Additionally, it allows you to control the watering system using a relay, triggered by a physical button or remotely through the Blynk app.

Features
Temperature & Humidity Monitoring: Uses a DHT11 sensor to track the temperature and humidity.
Soil Moisture Detection: Monitors soil moisture levels to ensure plants receive proper hydration.
Motion Detection: Uses a PIR sensor to detect movement in the vicinity of the plant, providing security.
Relay Control: Allows control of a watering system via a relay, which can be activated using a physical button or the Blynk app.
Blynk Integration: View real-time data on the Blynk mobile app and control the system remotely.
LCD Display: Displays temperature, humidity, and soil moisture readings on an LCD screen for easy access.
Requirements
ESP32 Development Board
DHT11 Sensor (for temperature and humidity)
Soil Moisture Sensor
PIR Motion Sensor
Relay Module (for controlling watering system)
Blynk App (for remote monitoring and control)
LCD with I2C Interface (for local display)
Installation
1. Hardware Setup
Connect the DHT11 sensor to GPIO 32 on the ESP32.
Connect the soil moisture sensor to GPIO 0.
Connect the PIR sensor to GPIO 14.
Connect the relay to GPIO 5.
Connect the push button to GPIO 25.
Connect the LCD to the ESP32 using I2C (address 0x3F).
2. Software Setup
Download and install the Blynk app.
Create a new project in the Blynk app and get your Auth Token.
Replace the BLYNK_AUTH_TOKEN, ssid, and pass in the code with your Blynk Auth Token and Wi-Fi credentials.
Upload the code to the ESP32 using the Arduino IDE.
Usage
Open the Blynk app and connect the ESP32.
Monitor the temperature, humidity, and soil moisture values on both the LCD display and the app.
The relay can be toggled manually using the physical button or remotely through the Blynk app.
Code Explanation
DHT11sensor(): Reads temperature and humidity data from the DHT11 sensor and sends it to the Blynk app.
soilMoistureSensor(): Reads soil moisture data and updates it in the Blynk app and LCD.
PIRsensor(): Detects motion using the PIR sensor and triggers a Blynk log event and LED indicator.
checkPhysicalButton(): Monitors the physical button state and toggles the relay accordingly.
BLYNK_WRITE(VPIN_BUTTON_1): Controls the relay state based on input from the Blynk app.
Contributing
Feel free to fork this repository, make improvements, and create pull requests. Contributions are welcome!


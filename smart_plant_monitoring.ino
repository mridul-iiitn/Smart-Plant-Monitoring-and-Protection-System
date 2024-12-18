// Include the required libraries
#define BLYNK_TEMPLATE_ID "TMPL3gZ2UU0Py"
#define BLYNK_TEMPLATE_NAME "Smart Plant"
#define BLYNK_AUTH_TOKEN "EGCChlwY4r2vZ3YQZZOaE14fr7ACHS2c"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Initialize the LCD display with the correct I2C address, columns, and rows
LiquidCrystal_I2C lcd(0x3F, 16, 2);

char ssid[] = "realme7";    // Enter your WiFi SSID
char pass[] = "123456789"; // Enter your WiFi Password

DHT dht(32, DHT11); // DHT sensor connected to GPIO 32 on ESP32
BlynkTimer timer;

// Define component pins based on your updated configuration
#define SOIL_SENSOR_PIN 0   // Soil Sensor connected to GPIO 0
#define PIR_PIN 14          // PIR Sensor connected to GPIO 14
#define RELAY_PIN 5         // Relay connected to GPIO 5
#define PUSH_BUTTON_PIN 25  // Push Button connected to GPIO 25
#define VPIN_BUTTON_1 V12

int relayState = LOW;
int pushButtonState = HIGH;

void setup() {
  Serial.begin(115200);

  // Initialize the LCD with the correct dimensions
  lcd.begin(16, 2);
  lcd.backlight();

  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  pinMode(PUSH_BUTTON_PIN, INPUT_PULLUP);

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Initialize DHT sensor
  dht.begin();

  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  // Set up Blynk timers
  timer.setInterval(1000L, DHT11sensor);
  timer.setInterval(1000L, soilMoistureSensor);
  timer.setInterval(1000L, PIRsensor);
  timer.setInterval(500L, checkPhysicalButton);
}

void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error");
    return;
  }

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);

  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(t);
  lcd.print("C ");
  lcd.print("H: ");
  lcd.print(h);
  lcd.print("% ");
}

void PIRsensor() {
  bool value = digitalRead(PIR_PIN);
  WidgetLED LED(V5);
  if (value) {
    Blynk.logEvent("pirmotion", "WARNING! Motion Detected!");
    LED.on();
  } else {
    LED.off();
  }
}

void soilMoistureSensor() {
  int soilValue = analogRead(SOIL_SENSOR_PIN);
  soilValue = map(soilValue, 0, 4095, 0, 100);
  soilValue = (soilValue - 100) * -1;

  Blynk.virtualWrite(V3, soilValue);
  lcd.setCursor(0, 1);
  lcd.print("Soil: ");
  lcd.print(soilValue);
  lcd.print("%   ");
}



void checkPhysicalButton() {
  if (digitalRead(PUSH_BUTTON_PIN) == LOW) {
    if (pushButtonState != LOW) {
      relayState = !relayState;
      digitalWrite(RELAY_PIN, relayState);
      Blynk.virtualWrite(VPIN_BUTTON_1, relayState);
    }
    pushButtonState = LOW;
  } else {
    pushButtonState = HIGH;
  }
}

BLYNK_WRITE(VPIN_BUTTON_1) {
  relayState = param.asInt();
  digitalWrite(RELAY_PIN, relayState);
}

void loop() {
  Blynk.run();
  timer.run();
}

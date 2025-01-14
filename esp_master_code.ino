#define BLYNK_TEMPLATE_ID "TMPL3rsfDEkhQ"
#define BLYNK_TEMPLATE_NAME "NODEMCU"
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include<Servo.h>

const int SLAVE_ADDR = 8;

float phValue = 0.0;
float temperature = 0.0;
float waterLevel = 0.0;
float conductivity = 0.0;

// Blynk virtual pin definitions
#define VIRTUAL_PIN_PH V0
#define VIRTUAL_PIN_TEMPERATURE V3
#define VIRTUAL_PIN_WATER_LEVEL V1
#define VIRTUAL_PIN_CONDUCTIVITY V2
#define VDINNER V5
#define VLUNCH V6
#define VFEED V7

Servo myServo;
bool automaticFeeding = false;
String dinnerTime, lunchTime;
//myServo.attach(2);
char auth[] = "Z9eVwuJHA5zqr-bhdoGTY7XNbf9AnxF9";
char ssid[] = "F19 Pro";
char pass[] = "123456789011";

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  // Initialize I2C as master
  Wire.begin();
}

void loop() {
  Blynk.run();

  // Request 16 bytes of data from the Arduino slave
  Wire.requestFrom(SLAVE_ADDR, 16);  // 4 floats, each 4 bytes

  if (Wire.available() == 16) {
    // Read pH value
    Wire.readBytes((char*)&phValue, sizeof(phValue));
    // Read temperature value
    Wire.readBytes((char*)&temperature, sizeof(temperature));
    // Read water level value
    Wire.readBytes((char*)&waterLevel, sizeof(waterLevel));
    // Read conductivity value
    Wire.readBytes((char*)&conductivity, sizeof(conductivity));
  }

  // Send the data to Blynk
  Blynk.virtualWrite(VIRTUAL_PIN_PH, phValue);
  Blynk.virtualWrite(VIRTUAL_PIN_TEMPERATURE, temperature);
  Blynk.virtualWrite(VIRTUAL_PIN_WATER_LEVEL, waterLevel);
  Blynk.virtualWrite(VIRTUAL_PIN_CONDUCTIVITY, conductivity);

  // Print the received values for debugging
  Serial.print("pH: ");
  Serial.println(phValue, 2);
  Serial.print("Temperature: ");
  Serial.println(temperature, 2);
  Serial.print("Water Level: ");
  Serial.println(waterLevel, 2);
  Serial.print("Conductivity: ");
  Serial.println(conductivity, 2);

  delay(1000);
}

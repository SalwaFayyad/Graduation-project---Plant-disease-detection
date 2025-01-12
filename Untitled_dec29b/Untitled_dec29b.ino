#include "arduino_secrets.h"
#include "DHT.h"
#include <WiFi.h>
#include "thingProperties.h"

#define LDR_DIGITAL_PIN 32
#define DPIN 4
#define DTYPE DHT11
#define soil_moisture_pin 35
#define LDRPIN 34

DHT dht(DPIN, DTYPE);

// Variables to store sensor readings (do not declare cloud variables here)
float Temperature;
float Humidity;

void setup() {
  Serial.begin(115200);
  pinMode(LDRPIN, INPUT);
  pinMode(LDR_DIGITAL_PIN, INPUT);
  dht.begin();

  // Initialize IoT Cloud properties
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  // Update the IoT Cloud
  ArduinoCloud.update();

  // Read sensors and update the cloud
  readDHTSensor();      
  readSoilMoistureSensor(); // Read raw soil moisture value
  readLDRSensor();             

  delay(1000); // Small delay for stability
}

// Implement the required callback
void onTempretureChange() {
  Serial.println("Temperature cloud variable changed.");
}

void readDHTSensor() {
  // Read temperature and humidity from DHT sensor
  float temp = dht.readTemperature(false);  // Celsius
  float hum = dht.readHumidity();           // Humidity

  // Validate readings
  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Update IoT Cloud variables
  tempreture = temp;
  humidity = hum;

  // Debug output
  Serial.print("Temperature: ");
  Serial.print(tempreture);
}

void readLDRSensor() {
  // Read LDR analog value
  int ldrValue = analogRead(LDRPIN);
  
  // Read LDR digital value if needed
  int ldrDigitalValue = digitalRead(LDR_DIGITAL_PIN);

  // Store the raw analog value directly to the cloud variable (LDR)
  lDR = ldrValue;  // Update the LDR cloud variable with the raw LDR value

  // Debug output to ensure the correct values are being read and sent
  Serial.print("LDR Analog Value: ");
  Serial.println(lDR);  // Prints the raw value (0-4095)
  Serial.print("LDR Digital Value: ");
  Serial.println(ldrDigitalValue == HIGH ? "LED OFF" : "LED ON");
}

void readSoilMoistureSensor() {
  // Read soil moisture sensor raw value
  int soil_moisture_value = analogRead(soil_moisture_pin);  // Read raw value

  // Map the raw sensor value to a percentage (optional)
  int mappedSoilMoisture = map(soil_moisture_value, 0, 4095, 0, 100);

  // Update the cloud variable with the raw or mapped soil moisture value
  soil_mositure = soil_moisture_value;  // Update the cloud variable with the mapped value

  // Debug output
  Serial.print("Soil Moisture Raw Value: ");
  Serial.println(soil_moisture_value);  // Prints the raw value (0–4095)
}

/*
  Since SoilMositure is READ_WRITE variable, onSoilMositureChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onSoilMositureChange()  {
  // Add your code here to act upon SoilMositure change
}

/*
  Since LDR is READ_WRITE variable, onLDRChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLDRChange()  {
  // Add your code here to act upon LDR change
}
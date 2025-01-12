#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "03b3e4fd-2f48-420a-9c5d-f862b8436870";
const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]         = SECRET_DEVICE_KEY;    // Secret device password

void onSoilMositureChange();
void onLDRChange();
void onTempretureChange();

CloudFlowRate soil_mositure;   // Cloud variable
CloudLuminousIntensity lDR;    // Cloud variable
CloudRelativeHumidity humidity; // Cloud variable
CloudTemperature tempreture;   // Cloud variable

void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(soil_mositure, READWRITE, 1 * SECONDS, onSoilMositureChange);
  ArduinoCloud.addProperty(lDR, READWRITE, 1 * SECONDS, onLDRChange);
  ArduinoCloud.addProperty(humidity, READ, 1 * SECONDS, NULL);
  ArduinoCloud.addProperty(tempreture, READWRITE, 1 * SECONDS, onTempretureChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
#include <Arduino.h>
static const uint32_t GPSBaud = 9600;

#include <TinyGPS++.h>
TinyGPSPlus gps;
// HardwareSerial mySerial1(2);
void processGps();

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 1 /*rx*/, 3/* tx */);
}

void loop() { //Choose Serial1 or Serial2 as required
  processGps();
}

void processGps() {
  while (Serial1.available() > 0) {
    char c = Serial1.read();
    if (gps.encode(c)) {
      if (gps.location.isValid()) {
        Serial.print(gps.location.lat(), 6);
        Serial.print(F(","));
        Serial.print(gps.location.lng(), 6);
        RawDegrees lat = gps.location.rawLat();
        RawDegrees lng = gps.location.rawLng();
        char latC[20];
        char lngC[20];
        sprintf(latC, "%c%u.%lu", lat.negative?'-':' ', lat.deg, lat.billionths);
        sprintf(lngC, "%c%u.%lu", lng.negative?'-':' ', lng.deg, lng.billionths);
        Serial.printf("%s,%s\r\n", latC, lngC);
      }
      else
      {
        // Serial.println(F("INVALID"));
      }
    }
  }
}

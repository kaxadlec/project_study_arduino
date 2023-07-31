// mac address 확인하는 코드 
// 받침대만 있는 ET-BOARD ESP32 MAC Address: C8:F0:9E:B4:EC:C0
// 아무것도 없는 ET-BOARD ESP32 MAC Address: C8:F0:9E:AE:0E:48
// 키트모두 조립 ET-BOARD ESP32 MAC Address: C8:F0:9E:AD:07:64

#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000); // Add a short delay

  uint8_t mac[6];
  WiFi.macAddress(mac);

  Serial.print("ESP32 MAC Address: ");
  for (int i = 0; i < 6; ++i) {
    Serial.printf("%02X", mac[i]);
    if (i < 5) {
      Serial.print(':');
    }
  }
  Serial.println();
}

void loop() {

}

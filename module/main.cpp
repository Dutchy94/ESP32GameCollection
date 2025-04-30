#include <esp_now.h>
#include <WiFi.h>
#include "../common/protocol.h"

void onReceive(const uint8_t *mac, const uint8_t *incomingData, int len) {
  if (len == sizeof(GameMessage)) {
    GameMessage msg;
    memcpy(&msg, incomingData, len);
    Serial.print("Nachricht empfangen, Command: ");
    Serial.println(msg.command, HEX);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init fehlgeschlagen");
    return;
  }

  esp_now_register_recv_cb(onReceive);
}

void loop() {}

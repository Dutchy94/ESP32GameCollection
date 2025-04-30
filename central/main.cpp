#include <esp_now.h>
#include <WiFi.h>
#include "../common/protocol.h"

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Broadcast

void onSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Nachricht gesendet: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Erfolg" : "Fehler");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init fehlgeschlagen");
    return;
  }

  esp_now_register_send_cb(onSent);

  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, broadcastAddress, 6);
  peer.channel = 0;  
  peer.encrypt = false;

  esp_now_add_peer(&peer);

  GameMessage msg = {MESSAGE_TYPE_COMMAND, 0x42};
  esp_now_send(broadcastAddress, (uint8_t*)&msg, sizeof(msg));
}

void loop() {}

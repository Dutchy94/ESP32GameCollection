#include <WiFi.h>
#include <esp_now.h>
#include "esp_wifi.h"
#include "../common/protocol.h"

// ✅ Zentrale-MAC (von serieller Ausgabe)
uint8_t centralMac[] = {0xEC, 0xE3, 0x34, 0x7B, 0xB7, 0x50};

unsigned long lastSend = 0;

void onReceive(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  Serial.println("Modul: Daten empfangen");

  if (len == sizeof(GameMessage)) {
    GameMessage msg;
    memcpy(&msg, data, len);
    Serial.print("Antwort: Command: 0x");
    Serial.print(msg.command, HEX);
    Serial.print(" | Value: ");
    Serial.println(msg.value);
  } else {
    Serial.println("Modul: Ungültige Nachricht ignoriert");
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("=== Modul gestartet ===");

  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  wifi_country_t country = {
    .cc = "EU",
    .schan = 1,
    .nchan = 13,
    .policy = WIFI_COUNTRY_POLICY_MANUAL
  };
  esp_wifi_set_country(&country);

  setCpuFrequencyMhz(240);  // für ESP32-S3/C3 empfohlen

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init fehlgeschlagen");
    return;
  }

  // Zentrale als Peer eintragen
  esp_now_peer_info_t peer = {};
  memcpy(peer.peer_addr, centralMac, 6);
  peer.channel = 1;
  peer.encrypt = false;
  peer.ifidx = WIFI_IF_STA;
  esp_now_add_peer(&peer);

  esp_now_register_recv_cb(onReceive);
  esp_wifi_set_promiscuous(false);  // Empfangsprobleme vermeiden

  Serial.println("Modul bereit");
}

void loop() {
  if (millis() - lastSend > 5000) {
    GameMessage msg = {MESSAGE_TYPE_COMMAND, 0xA0, 7};
    esp_now_send(centralMac, (uint8_t*)&msg, sizeof(msg));
    Serial.println("Modul: Nachricht gesendet");
    lastSend = millis();
  }
}

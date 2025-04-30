#include <WiFi.h>
#include <esp_now.h>
#include "esp_wifi.h"
#include "../common/protocol.h"

void onReceive(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  if (len != sizeof(GameMessage)) {
    Serial.println("Zentrale: Ungültige Nachricht – ignoriert");
    return;
  }

  GameMessage msg;
  memcpy(&msg, data, len);

  Serial.print("Zentrale: Empfangen von ");
  for (int i = 0; i < 6; i++) {
    if (i) Serial.print(":");
    Serial.printf("%02X", info->src_addr[i]);
  }
  Serial.print(" | Command: ");
  Serial.print(msg.command, HEX);
  Serial.print(" | Value: ");
  Serial.println(msg.value);

  // Peer sicherheitshalber eintragen
  if (!esp_now_is_peer_exist(info->src_addr)) {
    esp_now_peer_info_t peer = {};
    memcpy(peer.peer_addr, info->src_addr, 6);
    peer.channel = 1;
    peer.encrypt = false;
    peer.ifidx = WIFI_IF_STA;
    esp_now_add_peer(&peer);
    Serial.println("Zentrale: Peer hinzugefügt");
  }

  GameMessage reply = {MESSAGE_TYPE_COMMAND, 0xB0, msg.value + 1};
  esp_err_t result = esp_now_send(info->src_addr, (uint8_t*)&reply, sizeof(reply));

  if (result == ESP_OK) {
    Serial.println("Zentrale: Antwort gezielt gesendet");
  } else {
    Serial.print("Zentrale: Fehler beim Senden: ");
    Serial.println(result);
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("=== Zentrale gestartet ===");

  WiFi.mode(WIFI_STA);
  delay(100);  // MAC-Erkennung zuverlässig
  WiFi.disconnect();  // kein Access-Point suchen

  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);

  String macStr = WiFi.macAddress();
  Serial.print("Zentrale MAC: ");
  Serial.println(macStr);  // z. B. CC:BA:97:08:EE:3C

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init fehlgeschlagen!");
    return;
  }

  esp_now_register_recv_cb(onReceive);
  Serial.println("Zentrale bereit");
}

void loop() {
  delay(1000);
}

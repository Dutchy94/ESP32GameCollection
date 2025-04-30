# ESP-NOW Spielsystem

Ein modulares, drahtloses Spielsystem auf Basis von ESP32 und ESP32-C3 Mikrocontrollern.  
Ein zentraler ESP32 mit Display steuert verschiedene Spielmodi.  
Mehrere dezentrale ESP32-Module mit LEDs und Tastern dienen als Spielerstationen.  
Kommunikation erfolgt über ESP-NOW (schnell, stromsparend, kein WLAN nötig).

---

## Features

- ESP-NOW-basierte Kommunikation (1:n)
- Zentrale Spielsteuerung mit Display
- Spielerstationen mit LEDs & Taster
- Mehrere Spielmodi:
  - Reaktionsspiel
  - Kettenreaktion
  - Simon Says
  - Speedrunde
  - Farbcode-Spiel
  - Hot Potato
- Erweiterbar und modular aufgebaut

---

## Hardware

### Zentrale (ESP32)
- OLED oder TFT Display (I²C/SPI)
- Taster oder Drehencoder zur Spielauswahl
- Optional: Summer für Feedback

### Module (ESP32-C3)
- 1x Taster (GPIO)
- 1–4 RGB-LEDs (z. B. WS2812 oder einfache LEDs)
- Optional: Buzzer

---

## Aufbau

```text
[Zentraleinheit ESP32]
   │
   ├──ESP-NOW Broadcasts
   ▼
[Modul 1 - LED + Taster]
[Modul 2 - LED + Taster]
[... beliebig erweiterbar]

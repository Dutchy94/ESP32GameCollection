#pragma once

#include <Arduino.h>

#define MESSAGE_TYPE_COMMAND     0x01
#define CLAIM_REQUEST            0x10
#define CLAIM_RESPONSE           0x11

struct GameMessage {
  uint8_t type;
  uint8_t command;
  uint8_t value;  // z. B. Modul-ID
};

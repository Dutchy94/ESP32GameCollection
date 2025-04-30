#pragma once

#include <Arduino.h>

#define MESSAGE_TYPE_COMMAND 0x01

struct GameMessage {
    uint8_t type;
    uint8_t command;
};

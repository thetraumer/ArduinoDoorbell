#include "Arduino.h"
#include <stdint.h>
#include "DacLadder.h"

DacLadder::DacLadder() {
    for (uint8_t i = 0; i < DacLadder::DAC_RESOLUTION; i++) {
        pinMode(DAC_PINS[i], OUTPUT);
        digitalWrite(DAC_PINS[i], LOW);
    }
}

uint8_t DacLadder::ConvertEightToSixBits(uint8_t value) {
    uint8_t result = value >> 2;
    if ((value & 0x03) >= 0x02 && result < 0x3F) {
        result++;
    }
    return result;
}

void DacLadder::SetValue(uint8_t value) {
    uint8_t oneBit = 1;
    uint8_t sixBitVal = ConvertEightToSixBits(value);
    for (uint8_t i = 0; i < DacLadder::DAC_RESOLUTION; i++) {
        if ((sixBitVal & (oneBit << i)) != 0) {
            digitalWrite(DAC_PINS[i], HIGH);
        }
        else {
            digitalWrite(DAC_PINS[i], LOW);
        }
    }
}


#include "BellButton.h"
#include "Arduino.h"
#include <stdint.h>

BellButton::BellButton() {
    pinMode(BELL_BUTTON_PIN, INPUT);
}

bool BellButton::IsButtonPressed() {
    uint16_t observationsWithtinInterval = 0;
    for (uint16_t i = 0; i < OBSERVATIONS_FOR_VERDICT; i++) {
        uint16_t measuredValue = analogRead(BELL_BUTTON_PIN);
        if (measuredValue > INTERVAL_LOWER_ENDPOINT && measuredValue < INTERVAL_UPPER_ENDPOINT) {
            observationsWithtinInterval++;
        }
        delay(OBSERVATION_DELAY_MS);
    }
    if (observationsWithtinInterval <= MAX_INTERVAL_HITS_WHEN_PRESSED) {
        return true;
    }
    return false;
}

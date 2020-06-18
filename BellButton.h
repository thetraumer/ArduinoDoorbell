#include "stdint.h"
#include "Arduino.h"

class BellButton {
private:
    const uint8_t BELL_BUTTON_PIN = 16;

    const uint16_t INTERVAL_LOWER_ENDPOINT = 40;
    const uint16_t INTERVAL_UPPER_ENDPOINT = 1000;
    
    const uint16_t MAX_INTERVAL_HITS_WHEN_PRESSED = 5;

    
    
    uint16_t observationsTotal = 0;
public:
    const uint16_t OBSERVATION_DELAY_MS = 1;
    const uint16_t OBSERVATIONS_FOR_VERDICT = 500;

    BellButton();
    bool IsButtonPressed();
};

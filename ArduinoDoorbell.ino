#include <stdint.h>
#include "BellFilePlayer.h"
#include "BellButton.h"

BellFilePlayer *player;
BellButton *bellButton;

const uint32_t SHORT_PLAY_DURATION_MS = 5000;
const uint16_t BUTTON_PRESSES_FOR_LONG_PLAY = 3;
const uint32_t BUTTON_PRESS_CHECKS_BEFORE_TIMEOUT = 20;
const char *audioFileName = "bell.wav";

void setup() {
    bellButton = new BellButton();
    player = new BellFilePlayer();
}

uint16_t recentButtonPresses = 0;
uint32_t lastPlayedPosition = 0;

uint16_t buttonNotPressedCount;

void ResetRepeatedPressData() {
    recentButtonPresses = 0;
    lastPlayedPosition = 0;
    buttonNotPressedCount = 0;
}

void ResetRepeatedPressDataOnTimeout() {
    if (buttonNotPressedCount >= BUTTON_PRESS_CHECKS_BEFORE_TIMEOUT) {
        ResetRepeatedPressData();
    }
}

uint32_t DeterminePlayDuration() {
    if (recentButtonPresses >= (BUTTON_PRESSES_FOR_LONG_PLAY - 1)) {
        return (UINT32_MAX / player->FILE_SAMPLES_PER_MSEC);
    }
    else {
        return SHORT_PLAY_DURATION_MS;
    }
}

void loop() {
    if (bellButton->IsButtonPressed()) {
        uint32_t playDuration = DeterminePlayDuration();
        player->PlayFile(audioFileName, lastPlayedPosition, playDuration);
        if (player->IsFileFinished()) {
            ResetRepeatedPressData();
        }
        else {
            lastPlayedPosition += playDuration;
            recentButtonPresses++;
        }
    }
    else if (recentButtonPresses > 0) {
        buttonNotPressedCount++;
        ResetRepeatedPressDataOnTimeout();
    }
}

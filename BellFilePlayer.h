#pragma once
#include <stdint.h>
#include <SD.h>
#include "DacLadder.h"

class BellFilePlayer {
private:
    const uint16_t CHIP_SELECT = 10;
    const uint32_t FILE_BYTES_TO_SKIP_HEADER = 1000;

    DacLadder dac;
    bool fileFinished;

    void InitSdCard();
    void ResetOutput();
    void PlaySample(uint16_t value);
    uint32_t ConvertMsToSamples(uint32_t ms);
    void SkipFileBytes(File *file, uint32_t bytesToSkip);
public:
    const uint32_t FILE_SAMPLES_PER_MSEC = 14;

    BellFilePlayer();
    void PlayFile(char fileName[], uint32_t msToSkip, uint32_t playDuration);
    bool IsFileFinished();
};


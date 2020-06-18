#include <SD.h>
#include "BellFilePlayer.h"
#include "DacLadder.h"

//static uint16_t divider = 1;
//static uint16_t multiplier = 1;
//static uint16_t center = 0x7F;

BellFilePlayer::BellFilePlayer(): dac{} {
    InitSdCard();
    fileFinished = false;
}

void BellFilePlayer::InitSdCard() {
    if (!SD.begin(CHIP_SELECT)) {
        //be stuck in endless loop
        while (true) ;
    }
}

void BellFilePlayer::ResetOutput() {
    dac.SetValue(0x00);
}

void BellFilePlayer::PlaySample(uint16_t sample) {
    dac.SetValue((uint8_t) sample);
}

void BellFilePlayer::SkipFileBytes(File *file, uint32_t bytesToSkip) {
    uint32_t i = 0;
    file->seek(bytesToSkip);
}

uint32_t BellFilePlayer::ConvertMsToSamples(uint32_t ms) {
    return (FILE_SAMPLES_PER_MSEC * ms);
}

bool BellFilePlayer::IsFileFinished() {
    return fileFinished;
}

void BellFilePlayer::PlayFile(char fileName[], uint32_t msToSkip, uint32_t playDuration) {
    ResetOutput();
    File audioFile = SD.open(fileName);
    if (audioFile) {
        uint32_t bytesToSkip = FILE_BYTES_TO_SKIP_HEADER + ConvertMsToSamples(msToSkip);
        if (bytesToSkip >= audioFile.size()) {
            bytesToSkip = FILE_BYTES_TO_SKIP_HEADER;
        }
        SkipFileBytes(&audioFile, bytesToSkip);
        uint32_t samplesToPlay = ConvertMsToSamples(playDuration);
        uint32_t playedSamples = 0;
        while (audioFile.available() && (playedSamples < samplesToPlay)) {
            uint8_t sample = audioFile.read();
            PlaySample(sample);
            playedSamples++;
        }
        if (audioFile.available()) {
            fileFinished = false;
        }
        else {
            fileFinished = true;
        }
        audioFile.close();
    }
    else {
        delay(1000);
    }
    ResetOutput();
}


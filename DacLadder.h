#pragma once
#include <stdint.h>

class DacLadder {
private:
    uint8_t ConvertEightToSixBits(uint8_t);
public:
    //ESP 8266
//    static const uint8_t DAC_BIT0 = 5;
//    static const uint8_t DAC_BIT1 = 4;
//    static const uint8_t DAC_BIT2 = 0;
//    static const uint8_t DAC_BIT3 = 2;
//    static const uint8_t DAC_BIT4 = 14;
//    static const uint8_t DAC_BIT5 = 12;

    //Arduino MEGA
//    static const uint8_t DAC_BIT0 = 22;
//    static const uint8_t DAC_BIT1 = 26;
//    static const uint8_t DAC_BIT2 = 30;
//    static const uint8_t DAC_BIT3 = 34;
//    static const uint8_t DAC_BIT4 = 38;
//    static const uint8_t DAC_BIT5 = 42;

    //Arduino Nano
    static const uint8_t DAC_BIT0 = 2;
    static const uint8_t DAC_BIT1 = 3;
    static const uint8_t DAC_BIT2 = 4;
    static const uint8_t DAC_BIT3 = 5;
    static const uint8_t DAC_BIT4 = 6;
    static const uint8_t DAC_BIT5 = 7;
  
    static const uint8_t DAC_RESOLUTION = 6;

    const uint8_t DAC_PINS[6] = {DAC_BIT0, DAC_BIT1, DAC_BIT2, DAC_BIT3, DAC_BIT4, DAC_BIT5};
  
    DacLadder();
    void SetValue(uint8_t value);
};

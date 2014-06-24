/*
Candle simulation library.

Generates 8-bit candle-like brightness values.
*/

#ifndef Candle_h
#define Candle_h

#include "Arduino.h"
#include <FastLED.h>

class Candle
{
  public:
    Candle(uint8_t brightness_min, uint8_t steps_min, uint8_t steps_max);
    uint8_t get_next_brightness();

  private:
    uint8_t
        _brightness_min,
        _steps_min,
        _steps_max,
        _brightness,
        _steps,
        _step;
    int16_t
        _brightness_delta;
};

#endif

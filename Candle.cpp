#include <Candle.h>
#include <FastLED.h>


void Candle::init(uint8_t brightness_min, uint8_t brightness_max, uint8_t steps_min, uint8_t steps_max) {
    _brightness_min = brightness_min;
    _brightness_max = brightness_max;
    _steps_min = steps_min;
    _steps_max = steps_max;
    _step = 0;
    _steps = 0;
    _brightness = 0;
}


uint8_t Candle::get_next_brightness() {
    uint8_t new_brightness;

    // Return next brightness value for candle

    if (_step > _steps) {
        // Update target brightness and delay

        // Get new brightness
        new_brightness = random8(_brightness_min, _brightness_max);

        // Update candle steps
        _steps = random8(
            _steps_min, max(new_brightness - _brightness, _steps_max)
        );

        // Amount of change for every step
        _brightness_delta = (new_brightness - _brightness) / _steps;
        if (_brightness_delta == 0) _brightness_delta = 1;

        // Serial.println(12345);
        // Serial.println(brightness);
        // Serial.println(new_brightness);
        // Serial.println(candle_steps);
        // Serial.println(_brightness_delta);
        // Serial.println(12345);

        // Reset step counter
        _step = 0;
    }

    // Set (and limit) brightness
    if (_brightness_delta > 0) {
        _brightness = qadd8(_brightness, _brightness_delta);
    } else {
        _brightness += _brightness_delta;
    }

    _step++;

    return ease8InOutCubic(_brightness);
}

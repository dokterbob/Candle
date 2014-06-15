/* Test the theory that candlelight can be simulate by lowpass filtering of
white noise. */

#include <Metro.h>
#include <FastLED.h>

#define CANDLE_BRIGHTNESS_MIN 96
#define CANDLE_STEPS_MIN 2
#define CANDLE_STEPS_MAX 20
#define CANDLE_TICK_TIME 20 // 50 FPS

byte
    candle_old_brightness = 0,
    candle_new_brightness = 0,
    candle_step = 0,
    candle_steps = 0,
    brightness = 0;

int16_t brightness_delta;

Metro candle_timer = Metro(CANDLE_TICK_TIME);

void setup() {
    Serial.begin(38400);
}

void loop() {
    candleLoop();

    delay(1);
}

void candleSetup() {
    pinMode(22, OUTPUT);
}

void candleLoop() {
    if (candle_timer.check() == 1) {
        // Candle tick

        if (candle_step > candle_steps) {
            // Update target brightness and delay

            // Get new brightness
            candle_new_brightness = random8(CANDLE_BRIGHTNESS_MIN, 255);

            // Update candle steps
            candle_steps = random8(
                CANDLE_STEPS_MIN, max(
                    candle_new_brightness - brightness, CANDLE_STEPS_MAX
                )
            );

            // Amount of change for every step
            brightness_delta = (candle_new_brightness - brightness) / candle_steps;
            if (brightness_delta == 0) brightness_delta = 1;

            Serial.println(12345);
            Serial.println(brightness);
            Serial.println(candle_new_brightness);
            Serial.println(candle_steps);
            Serial.println(brightness_delta);
            Serial.println(12345);

            // Reset step counter
            candle_step = 0;
        }

        // Set (and limit) brightness
        if (brightness_delta > 0) {
            brightness = qadd8(brightness, brightness_delta);
        } else {
            brightness += brightness_delta;
        }

        // Update LED state
        Serial.println(ease8InOutCubic(brightness));
        analogWrite(22, ease8InOutCubic(brightness));

        candle_step++;
    }
}

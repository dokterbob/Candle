/* Test the theory that candlelight can be simulate by lowpass filtering of
white noise. */

#include <Metro.h>
#include <FastLED.h>
#include <Candle.h>

#define NUM_STRIPS 8
#define NUM_LEDS_PER_STRIP 64
#define NUM_LEDS NUM_LEDS_PER_STRIP * NUM_STRIPS

CRGB leds[NUM_STRIPS * NUM_LEDS_PER_STRIP];

candle::Candle candles[NUM_LEDS];
candle::Candle saturation[NUM_LEDS];

byte hues[NUM_LEDS];

#define CANDLE_TICK_TIME 20

Metro candle_timer = Metro(CANDLE_TICK_TIME);

void setup() {
    FastLED.addLeds<NEOPIXEL, 2>(leds, 0, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<NEOPIXEL, 14>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<NEOPIXEL, 7>(leds, 2*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<NEOPIXEL, 8>(leds, 3*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<NEOPIXEL, 6>(leds, 4*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<NEOPIXEL, 20>(leds, 5*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<NEOPIXEL, 21>(leds, 6*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
    FastLED.addLeds<NEOPIXEL, 5>(leds, 7*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);

    for (size_t i=0; i<NUM_LEDS; i++) {
        // Reset LED values
        leds[i] = CRGB::Black;

        // Initialize candles
        candles[i].init(random8(16, 96), 255, random8(3, 8), random8(6, 22));

        // Initialize random hues and saturation
        hues[i] = random8(24, 32);
        saturation[i].init(random8(112, 240), random8(241, 255), random8(10, 20), random8(22, 62));
    }

    FastLED.show();

    // Power LED
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void loop() {
    candleLoop();
}

void candleLoop() {
    if (candle_timer.check() == 1) {
        for (size_t i=0; i<NUM_LEDS; i++) {
            leds[i] = CHSV(hues[i], saturation[i].get_next_brightness(), candles[i].get_next_brightness());
        }

        FastLED.show();
    }
}

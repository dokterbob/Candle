/* Test the theory that candlelight can be simulate by lowpass filtering of
white noise. */

#include <Metro.h>
#include <FastLED.h>
#include <Candle.h>

// How many leds in your strip?
#define NUM_LEDS 40

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 3
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];
Candle *candles[NUM_LEDS];
char hues[NUM_LEDS];

#define CANDLE_TICK_TIME 20

Metro candle_timer = Metro(CANDLE_TICK_TIME);

void setup() {
    // Uncomment/edit one of the following lines for your leds arrangement.
    // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<NEOPIXEL, DATA_PIN, GRB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);

    // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);

    // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);

    for (size_t i; i<NUM_LEDS; i++) {
        // Reset LED values
        leds[i] = CRGB::Black;

        // Initialize candles
        candles[i] = new Candle(random8(34, 96), random8(2, 6), random8(8, 20));

        // Initialize random hues
        hues[i] = random8(32, 48);
    }

    FastLED.show();

    // Power LED
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void loop() {
    candleLoop();

    delay(1);
}

void candleLoop() {
    if (candle_timer.check() == 1) {
        for (size_t i; i<NUM_LEDS; i++) {
            leds[i] = CHSV(hues[i], 255, candles[i]->get_next_brightness());
        }

        FastLED.show();
    }
}
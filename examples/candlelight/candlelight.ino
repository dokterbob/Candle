/* Test the theory that candlelight can be simulate by lowpass filtering of
white noise. */

#include <Metro.h>
#include <FastLED.h>
#include <Candle.h>

#define CANDLE_TICK_TIME 20

Candle candle1(96, 255, 2, 20);
Candle candle2(34, 255, 4, 10);
Candle candle3(64, 255, 6, 8);

Metro candle_timer = Metro(CANDLE_TICK_TIME);

void setup() {
    Serial.begin(38400);
    candleSetup();
}

void loop() {
    candleLoop();

    delay(1);
}

void candleSetup() {
    pinMode(21, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
}

void candleLoop() {
    byte brightness;

    if (candle_timer.check() == 1) {
        analogWrite(21, candle1.get_next_brightness());
        analogWrite(22, candle2.get_next_brightness());
        analogWrite(23, candle3.get_next_brightness());
    }
}

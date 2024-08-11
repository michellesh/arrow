#include <FastLED.h>

#define DATA_PIN 13
#define LED_TYPE NEOPIXEL
#define COLOR_ORDER GRB
#define NUM_LEDS 144
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];

float chase = NUM_LEDS; // current chase position
int length = 50;        // total length of the chase
int speed = 2; // number of pixels to advance on each iteration of the loop
float delayFactor = 1.5; // how long to delay between bloops. 1 will delay for
                         // the same amount of time as a single bloop.

void setup() {
  Serial.begin(9600);
  delay(500);

  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  FastLED.clear();

  for (int i = chase; i < chase + length; i++) {
    if (i >= 0 && i < NUM_LEDS) {
      leds[i] = CRGB::Green;
      int brightness =
          i < (chase + length) / 2
              ? map(i, chase, (chase + length) / 2, 0, 255)
              : map(i, (chase + length) / 2, chase + length, 255, 0);
      leds[i].nscale8(brightness);
    }
  }

  chase -= speed;
  if (chase < -1 * delayFactor * NUM_LEDS) {
    chase = NUM_LEDS;
  }

  FastLED.show();
}

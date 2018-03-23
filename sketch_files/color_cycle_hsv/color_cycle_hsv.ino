#include "FastLED.h"

const int redPin = 10;
const int greenPin = 11;
const int bluePin = 9;
const int delayMS = 15;


void setColorRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setup() {
  // Start off with the LED off.
  setColorRgb(0,0,0);
}

void loop() {
  // representation of one RGB pixel, set to red initially
  CRGB rgbColor;
  //rgbColor = CRGB::Red;

  // representation of one HSV pixel
  CHSV hsvColor = CHSV(0, 0, 255);

  // run the hsv pixel through hue 0-255, with constant "value" (pretty much brightness)
  for (int i = 0; i < 255; i++) {
    hsvColor.s = sin8_C(i);
    for (int i = 0; i < 255; i++) {
      hsvColor.h = i;
      hsv2rgb_rainbow(hsvColor, rgbColor);
      setColorRgb(rgbColor.r, rgbColor.b, rgbColor.g);
      delay(delayMS);
    } 
  }
}

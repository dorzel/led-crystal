#include "FastLED.h"

const int redPin = 10;
const int greenPin = 11;
const int bluePin = 9;
const int delayMS = 130;

// representation of one RGB pixel
CRGB rgbColor;
// representation of one HSV pixel
CHSV hsvColor = CHSV(0, 255, 255);

void setColorRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void fullHueCycle() {
  // run the hsv pixel through hue 0-255, with constant value and saturation
  // no need to have an invert option as hue is defined as the angular component
  // in cylindrical coordinates, and so will return to it's originial value
  for (int i = 0; i <= 255; i++) {
    hsvColor.h = i;
    hsv2rgb_rainbow(hsvColor, rgbColor);
    setColorRgb(rgbColor.r, rgbColor.g, rgbColor.b);
    delay(delayMS); 
  } 
}

void setup() {
  setColorRgb(0,0,0);
}

void loop() {
  fullHueCycle();
}

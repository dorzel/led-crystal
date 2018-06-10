#include "FastLED.h"

const int redPin = 10;
const int greenPin = 11;
const int bluePin = 9;

// representation of one RGB pixel
CRGB rgbColor;
// representation of one HSV pixel
CHSV hsvColor = CHSV(0, 255, 255);

void setColorRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void fullValueCycle(bool invert, int delayMS) {
  // run the hsv pixel through value 0-255, with constant hue and saturation
  // can choose to invert the direction to 255-0
  for (int i = 0; i <= 255; i += 1) {
      if (invert) {
        hsvColor.v = 255 - i; 
      }
      else {
        hsvColor.v = i;
      }
      hsv2rgb_rainbow(hsvColor, rgbColor);
      setColorRgb(rgbColor.r, rgbColor.b, rgbColor.g);
      delay(delayMS);
    }
}

void fullHueCycle(int delayMS) {
  // run the hsv pixel through hue 0-255, with constant value and saturation
  // no need to have an invert option as hue is defined as the angular component
  // in cylindrical coordinates, and so will return to it's originial value
  for (int i = 0; i <= 255; i++) {
    hsvColor.h = i;
    hsv2rgb_rainbow(hsvColor, rgbColor);
    setColorRgb(rgbColor.r, rgbColor.b, rgbColor.g);
    delay(delayMS);
  }
}

void startupSequence(int startHue, int numTimes, int valueDelayMS) {
  // pulsing effect with a single hue, make sure that this runs
  // an odd number of times to end on the value being max
  hsvColor.h = startHue;
  for (int i = 0; i < numTimes; i++) {
    bool invert = (i + 2) % 2;
    fullValueCycle(invert, valueDelayMS); 
  }
}

void setup() {
  // Start off with the LED off.
  setColorRgb(0,0,0);
  startupSequence(0, 5, 4);
}

void loop() {
  fullHueCycle(125);
}

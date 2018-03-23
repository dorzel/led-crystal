#include "FastLED.h"

const int redPin = 10;
const int greenPin = 11;
const int bluePin = 9;
const int delayMS = 125;

// representation of one RGB pixel
CRGB rgbColor;
// representation of one HSV pixel
CHSV hsvColor = CHSV(0, 255, 255);

void setColorRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void fullValueCycle(bool invert) {
  for (int i = 0; i < 255; i += 1) {
      if (invert) {
        hsvColor.v = 255 - i; 
      }
      else {
        hsvColor.v = i;
      }
      hsv2rgb_rainbow(hsvColor, rgbColor);
      setColorRgb(rgbColor.r, rgbColor.b, rgbColor.g);
      delay(10);
    }
}

void fullHueCycle() {
  for (int i = 0; i < 255; i++) {
    hsvColor.h = i;
    hsv2rgb_rainbow(hsvColor, rgbColor);
    setColorRgb(rgbColor.r, rgbColor.b, rgbColor.g);
    delay(delayMS);
  }
}

void startupSequence() {
  for (int i = 2; i < 5; i++) {
    bool invert = i % 2;
    fullValueCycle(invert); 
  }
}

void setup() {
  // Start off with the LED off.
  setColorRgb(0,0,0);
  startupSequence();
}

void loop() {
  // TODO: vary hsvcColor.v with the analog microphone
  // run the hsv pixel through hue 0-255, with constant "value" (pretty much brightness)  
  fullHueCycle();
}

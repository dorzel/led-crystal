#include "FastLED.h"

const int redPin = 10;
const int greenPin = 11;
const int bluePin = 9;
const int micPin = A0;
const int delayMS = 125;


void setColorRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void setup() {
  // Start off with the LED off.
  setColorRgb(0,0,0);
  Serial.begin(9600);
}

void loop() {
  // representation of one RGB pixel
  CRGB rgbColor;

  // representation of one HSV pixel
  CHSV hsvColor = CHSV(0, 255, 255);

  // TODO: vary hsvcColor.v with the analog microphone
  // run the hsv pixel through hue 0-255, with constant "value" (pretty much brightness)  
  for (int i = 0; i < 255; i++) {
    hsvColor.h = i;
    hsv2rgb_rainbow(hsvColor, rgbColor);
    setColorRgb(rgbColor.r, rgbColor.b, rgbColor.g);
    int sound_value = analogRead(micPin);
    Serial.println(sound_value);
    delay(delayMS);
  }
}

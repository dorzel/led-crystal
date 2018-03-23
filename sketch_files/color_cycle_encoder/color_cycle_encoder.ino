#include "FastLED.h"

const int redPin = 10;
const int greenPin = 11;
const int bluePin = 9;
const int encoderPinA = 6;
const int encoderPinB = 7;
const int delayMS = 125;

// representation of one RGB pixel
CRGB rgbColor;
// representation of one HSV pixel
CHSV hsvColor = CHSV(0, 255, 255);

int encoderState;
int encoderLastState;
int encoderCounter = 0;


int getEncoderPosition() {
  encoderState = digitalRead(encoderPinA);
  // If the previous and the current state of the exncoderPinA are different, that means a Pulse has occured
  if (encoderState != encoderLastState){     
    // If the encoderPinB state is different to the encoderPinA state, that means the encoder is rotating clockwise
    if (digitalRead(encoderPinB) != encoderState) { 
      encoderCounter ++;
    } else {
      encoderCounter --;
    }
    Serial.print("Position: ");
    Serial.println(encoderCounter);
  } 
  encoderLastState = encoderState; // Updates the previous state of the encoderPinA with the current state
}


void setColorRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void fullValueCycle(bool invert) {
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
      delay(5);
    }
}

void fullHueCycle() {
  // run the hsv pixel through hue 0-255, with constant value and saturation
  // no need to have an invert option as hue is defined as the angular component
  // in cylindrical coordinates, and so will return to it's originial value
  for (int i = 0; i <= 255; i++) {
    hsvColor.h = i;
    hsv2rgb_rainbow(hsvColor, rgbColor);
    setColorRgb(rgbColor.r, rgbColor.b, rgbColor.g);
    getEncoderPosition();
    delay(delayMS);
  }
}

void startupSequence(int startHue, int numTimes) {
  // pulsing effect with a single hue, make sure that this runs
  // an odd number of times to end on the value being max
  hsvColor.h = startHue;
  for (int i = 0; i < numTimes; i++) {
    bool invert = (i + 2) % 2;
    fullValueCycle(invert); 
  }
}

void setup() {
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  Serial.begin(9600);
  encoderLastState = digitalRead(encoderPinA);
  // Start off with the LED off.
  setColorRgb(0,0,0);
  startupSequence(0, 5);
}

void loop() {
  //fullHueCycle();
  getEncoderPosition();
  delay(125);
}

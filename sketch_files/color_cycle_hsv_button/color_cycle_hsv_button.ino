#include "FastLED.h"
#include "Thread.h"

const int redPin = 10;
const int greenPin = 11;
const int bluePin = 9;
const int buttonPin = 2;
const int delayMS = 130;

// representation of one RGB pixel
CRGB rgbColor;
// representation of one HSV pixel
CHSV hsvColor = CHSV(0, 255, 255);

Thread buttonThread = Thread();

int buttonState = 1;
int prevButtonState = 1;
int numPressesHeld = 0;
bool lightOn = false;
bool cycleColor = true;


void setColorRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void readButton() {
  // 0 when pressed, 1 when depressed
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == 0) {
    if (prevButtonState == 1) {
       // button pressed
       numPressesHeld = numPressesHeld + 1;
    }
    if (prevButtonState == 0) {
      // button left pressed
      if (numPressesHeld == 10) {
        lightOn = !lightOn;
        if (!lightOn) {
          setColorRgb(0, 0, 0);
        }
      }
      numPressesHeld = numPressesHeld + 1;
    }
  }
  if (buttonState == 1) {
    if (prevButtonState == 0) {
      // button depressed
      if (numPressesHeld < 10) {
        // color chosen/unchosen, toggle cycling color
        cycleColor = !cycleColor;
      }
      numPressesHeld = 0;
    }
    if (prevButtonState == 1) {
      // button left depressed
    }
  }
  
  prevButtonState = buttonState;
}

void fullHueCycle() {
  // run the hsv pixel through hue 0-255, with constant value and saturation
  // no need to have an invert option as hue is defined as the angular component
  // in cylindrical coordinates, and so will return to it's originial value
  for (int i = 0; i <= 255; i++) {
    if (lightOn && cycleColor) {
      hsvColor.h = i;
      hsv2rgb_rainbow(hsvColor, rgbColor);
      setColorRgb(rgbColor.r, rgbColor.g, rgbColor.b);
    } else {
      i--;
    }
    if(buttonThread.shouldRun()){
      buttonThread.run();
    }
    delay(delayMS); 
  } 
}

void setup() {
  pinMode(buttonPin, INPUT);
  buttonThread.setInterval(10);
  buttonThread.onRun(readButton);
  setColorRgb(0,0,0);
}

void loop() {
  fullHueCycle();
}

#include "FastLED.h"
#include "Thread.h"

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int buttonPin = 2;
const int delayMS = 125;

// representation of one RGB pixel
CRGB rgbColor;
// representation of one HSV pixel
CHSV hsvColor = CHSV(0, 255, 255);

Thread buttonThread = Thread();

int buttonState = 0;
int prevButtonState = 0;
bool lightOn = true;


void setColorRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void readButton() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != prevButtonState) {
    // button was pressed or released
    if (buttonState == 1 && prevButtonState == 0) {
      // invert the lightOn bool every time the button is pressed, not depressed
      lightOn = !lightOn;
      if (!lightOn) {
        setColorRgb(0, 0, 0);
      }
    }
  }
  prevButtonState = buttonState;
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
    if (lightOn) {
      hsvColor.h = i;
      hsv2rgb_rainbow(hsvColor, rgbColor);
      setColorRgb(rgbColor.r, rgbColor.b, rgbColor.g);
    }
    if(buttonThread.shouldRun()){
      buttonThread.run();
    }
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
  pinMode(buttonPin, INPUT);
  buttonThread.setInterval(100);
  buttonThread.onRun(readButton);
  setColorRgb(0,0,0);
  startupSequence(0, 5);
}

void loop() {
  fullHueCycle();
}

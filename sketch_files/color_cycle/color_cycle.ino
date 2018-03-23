const int redPin = 10;
const int greenPin = 11;
const int bluePin = 9;
const int delayMS = 10;

void setup() {
  // Start off with the LED off.
  setColorRgb(0,0,0);
}

void loop() {
  unsigned int rgbColor[3] = {255, 0, 0};

  // Choose the colours to increment and decrement.
  for (int decColor = 0; decColor < 3; decColor += 1) {
    int incColor = decColor == 2 ? 0 : decColor + 1;

    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColor[decColor] -= 1;
      rgbColor[incColor] += 1;
      
      setColorRgb(rgbColor[0], rgbColor[1], rgbColor[2]);
      delay(delayMS);
    }
  }
}

void setColorRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

# led-crystal
A simple RGB LED (Keyes KY-009 5050 SMD LED) driven by an Arduino Uno and shining through a large selenite crystal.

FastLED Library:
- http://fastled.io/
- https://github.com/FastLED/FastLED

LED:
- https://arduinomodules.info/ky-009-rgb-full-color-led-smd-module/

Understanding HSV as a spherical coordinate system is very beneficial:
- https://en.wikipedia.org/wiki/HSL_and_HSV#Basic_principle

### The Code

The sketch files located in the `sketch_files/` directory are all different versions of the same
basic sketch: `color_cycle_hsv.ino`. The others are WIP sketches attempting to add different 
sensors to further control the LED. 

`color_cycle_hsv.ino` uses the hsv color space to cycle the single LED through it's full hue.

`color_cycle_hsv_button.ino` adds functionality with a connected button. Hold the button down for ~1 second to turn on/off. Click it fast to hold/unhold on a certain color. 

# led-crystal
A simple rgb led (Keyes KY-009 SMD LED) driven by an arduino and shining through a large selenite crystal.

FastLED Library:
- https://github.com/FastLED/FastLED
- http://fastled.io/docs/3.1/index.html

understanding HSV as a spherical coordinate system is very beneficial:
- https://en.wikipedia.org/wiki/HSL_and_HSV#Basic_principle

### The Code

The sketch files located in the `sketch_files/` directory are all different versions of the same
basic sketch: `color_cycle_hsv.ino`. The others are WIP sketches attempting to add different 
sensors to further control the LED. 

`color_cycle_hsv.ino` uses the hsv color space to cycle the single LED through it's full hue.
It displays a quick startup sequence which flashes red and then changes to a slow hue cycle (or color cycle). 

`hsv2rgb_rainbow()` is the magic function from the FastLED library that converts the hsv space into rgb space. 
using the "rainbow" variant of this function means that the output color will more closely match colors that we
perceive as part of the rainbow, even though they are less technically correct. More info [here.](https://github.com/FastLED/FastLED/blob/master/hsv2rgb.cpp#L8)
This was chosen because the original rgb-only implementation showed way too much blue and purple, and not enough reds. With the hsv space this problem is solved. 


TODO: upload video of the crystal

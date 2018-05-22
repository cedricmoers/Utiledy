![Logo](extras/Graphics/UtiledyLogo.png)
## Introduction

A general purpose class library for use with LEDs.
For now only normal, single color, LEDs are supported.
A future release will bring classes for RGB and RGBW LEDs.

I would like to call this library lightweight, but I have no clue if that's the case. 
I think it's not.

Still... it offers a lot of functionality with only a small amount of code needed in a sketch, so why not give it a try?

## Background

In a lot of my projects LEDs are used. Not just for indicative purposes, but almost always decorative.
The main functionalities I needed are:

* Gamma Correction
* Fading (in and out, but also waving)
* Blinking
* Sparkling
* All of them combined
* Colors (Soon...)

Every project I had to copy/paste the same functionality and most of the times I saw some things that could be done better.
Then, when I changed something in the sketch, those changes should also make their way to newer and older projects.
This made the choice for a LED library all the more appealing. It was also a good C++ exercise to do so. 

So I started writing a simple Arduino library, containing one class that had all the functionality I wanted.
In the end it was a cluttered LED class that could sparkle, blink, fade and act as a constant lightsource.
This was not a good way to do that, since there was no way to just create a blinker, without having the sparkle functionality.

That's why I started over. This time with a more hierarchical/layered approach.
Starting with a GammaLED class, that just has the gamma correction and the basic functionalities such as:

* Setting brightness, increasing, decreasing, correcting and mapping.
* Writing the corrected values to the outputs
* Smoothing the actual output (low pass filter)
* ...

Then I made a fader class that inherits from the LED class, but adds fading functionality.
After that, it was time to make a blinker and a sparkler class, which both act as the name suggest.
And finally a class that inherits from both the blinker and the sparkler and can act as both.

## Applications

Currently, the library is only tested for the ESP8266 using the Arduino IDE, but Arduino board support shall be added soon. 

## Usage

The usage of the classes in the library is fairly simple. Each class has a header file. 
So if you want to...

### Create a Blinker: 
```C
#include <Blinker.h>

Blinker led1 = Blinker("LED1", HWPIN_LED1, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
```
### Use the Blinker:
```C
led1.setHighBrightness(4095); // led1.setBrightness(4095) does the same.
led1.setLowBrightness(0);
led1.setHighTime(1000);
led1.setLowTime(1000);
led1.setOffset(5000);
led2.filter.enable(); // Enable the output filter to create a smoothing effect.
led2.filter.setSmoothing(0.999); // Set the strength of the smoothing effect.
...
led1.start();
...
led1.updateAndWrite(); // Call this in the loop();
```

### Create a Sparkler:
```C
#include <Sparkler.h>

Sparkler led1 = Sparkler("LED1", 5, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
```
### Use a Sparkler:
```C
led1.setBrightness(3000); // Sets the average spark brightness.
led2.setIntensity(1000); // Sets the intensity of the sparks.
led2.setSparkInterval(250); // Sets the interval on which sparks are generated.

led2.filter.enable(); // Enable the output filter to create a smoothing effect.
led2.filter.setSmoothing(0.999); // Set the strength of the smoothing effect.
...
led1.updateAndWrite(); // Call this in the loop();
```

### Create a Fader:
```C
#include <Fader.h>

Fader led1 = Fader("LED1", 5, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
```

### Use a Fader:
```C
// The time given as an argument is the MIN to MAX time. So in case of an 8-bit pwm driver, the time to go from 0 to 255.
// If you are already at a value of 128, the time it will take to go to 255 (difference of 127) is half the time given in the argument.

led1.fadeToValue(1023, 5000); // If the current brightness is 0, fade to a brightness of 1023 within 5000 milliseconds.

led1.fadeToMax(5000); // If the current brightness is 0, fade to maximum brightness within 5000 milliseconds.
led1.fadeToMin(5000); // If the current brightness is 0, fade to minimum brightness within 5000 milliseconds.
led1.fadeToggle(5000); // If the led is lighted, fade to minimum. If it's not, fade to maximum.

led1.fadeWave(5000, 0); // Fade up and down a number of timer. If the second value is 0, it will continue to wave until stopped.

// These callbacks can be used to do some sequencing or other tasks. The function signature needs to be 'void function()'.
setFadeValueReachedCallback(onLED1ValueReached);
setFadeWavingCompleteCallback(onLED1FadeWavingComplete);

...
led1.updateAndWrite(); // Call this in the loop();
...

void onLED1ValueReached() {
	Serial.println("I've reached my final fading value!");
}

void onLED1FadeWavingComplete() {
	Serial.println("I'm done with my waves for today!");
}
```

### Create an UltiLED:

```C
#include <UltiLED.h>

UltiLED led1 = UltiLED("LED1", 5, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
```
### Using an UltiLED:
The UltiLED is a class that can act as any of the above, using the same functions.
Additional functions set the operating mode.

```C
led2.setToBlink(BRIGHTNESS_TYPE_MAX, BRIGHTNESS_TYPE_MAX / 2, 1000, 2000);
led2.filter.enable();
led2.filter.setSmoothing(0.999);

led3.setToSpark(1000, 2000, 20);
led3.filter.enable();
led3.filter.setSmoothing(0.999);

led4.setBrightness(BRIGHTNESS_TYPE_MAX);
```

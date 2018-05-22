/*
 Name:		RunningFaders.ino
 Created:	5/21/2018 12:25:05 PM
 Author:	Cedric
*/



// the setup function runs once when you press reset or power the board
#include <Fader.h>

// Create the instances of LEDs that will be used.
Fader led1 = Fader("LED1", 5, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Fader led2 = Fader("LED2", 4, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Fader led3 = Fader("LED3", 0, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Fader led4 = Fader("LED4", 2, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);

void setup() {

	// Startup the communication.
	Serial.begin(921600);

	// Set the analog range of the board.
	analogWriteRange(BRIGHTNESS_TYPE_MAX);

	// Set a callback function for each led, for when the fadewaving is complete.
	led1.setFadeWavingCompleteCallback(onLED1FadeWavingComplete);
	led2.setFadeWavingCompleteCallback(onLED2FadeWavingComplete);
	led3.setFadeWavingCompleteCallback(onLED3FadeWavingComplete);
	led4.setFadeWavingCompleteCallback(onLED4FadeWavingComplete);

	// Set the first LED to start waving.
	led1.fadeWave(2000, 1);
}

void onLED1FadeWavingComplete() {

	// When the first led has completed its waving. Set the second LED to start waving.
	led2.fadeWave(2000, 1);

}

void onLED2FadeWavingComplete() {

	// When the second led has completed its waving. Set the third LED to start waving.
	led3.fadeWave(2000, 1);

}

void onLED3FadeWavingComplete() {

	// When the third led has completed its waving. Set the fourth LED to start waving.
	led4.fadeWave(2000, 1);

}

void onLED4FadeWavingComplete() {

	// When the fourth led has completed its waving. Set the first LED to start waving.
	led1.fadeWave(2000, 1);

}

// the loop function runs over and over again until power down or reset
void loop() {

	// Update the LEDs and write the values to their outputs.
	led1.updateAndWrite();
	led2.updateAndWrite();
	led3.updateAndWrite();
	led4.updateAndWrite();

}

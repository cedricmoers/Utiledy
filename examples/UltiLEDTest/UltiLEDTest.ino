/*
 Name:		UltiLEDTest.ino
 Created:	5/15/2018 8:26:29 PM
 Author:	Cedric
*/

// the setup function runs once when you press reset or power the board
#include <UltiLED.h>


UltiLED led1 = UltiLED("LED1", 5, true, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(921600);

	analogWriteRange(BRIGHTNESS_TYPE_MAX);

	led1.enable();

	led1.setUnscaledBrightness(500);

	led1.setIntensity(500);
	
	led1.setSparkInterval(20);

	led1.setLowPassFilterEnabled(true);

	led1.setLowPassFilterSmoothing(0.9);

	led1.setMode(ULTILEDMODE_NORMAL);
	led1.setHighBrightness(BRIGHTNESS_TYPE_MAX );
	led1.setLowBrightness(500);
	led1.setHighTime(1000);
	led1.setLowTime(1000);

	led1.fadeWave(5000, 0);

	led1.start();
}

// the loop function runs over and over again until power down or reset
void loop() {

	analogWrite(led1.getPin(), led1.update());

	delay(5);

}

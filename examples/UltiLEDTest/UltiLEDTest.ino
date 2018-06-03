/*
 Name:		UltiLEDTest.ino
 Created:	5/15/2018 8:26:29 PM
 Author:	Cedric
*/

// the setup function runs once when you press reset or power the board
#include <UltiLED.h>

UltiLED led1 = UltiLED("LED1", 5, true, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
UltiLED led2 = UltiLED("LED2", 4, true, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
UltiLED led3 = UltiLED("LED3", 0, true, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
UltiLED led4 = UltiLED("LED4", 2, true, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(921600);

	pinMode(led1.getPin(),OUTPUT);
	pinMode(led2.getPin(),OUTPUT);
	pinMode(led3.getPin(),OUTPUT);
	pinMode(led4.getPin(),OUTPUT);

	analogWriteRange(BRIGHTNESS_TYPE_MAX);

	led1.fadeWave(5000, 0);

	led2.setToBlink(BRIGHTNESS_TYPE_MAX, BRIGHTNESS_TYPE_MAX / 2, 1000, 2000);
	led2.filter.enable();
	led2.filter.setSmoothing(0.999);

	led3.setToSpark(1000, 2000, 20);
	led3.filter.enable();
	led3.filter.setSmoothing(0.999);

	led4.setBrightness(BRIGHTNESS_TYPE_MAX);
	
}

// the loop function runs over and over again until power down or reset
void loop() {

	led1.updateAndWrite();
	led2.updateAndWrite();
	led3.updateAndWrite();
	led4.updateAndWrite();

	yield();

}

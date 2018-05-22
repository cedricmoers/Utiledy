
#include <Sparkler.h>


/*
 Name:		GammaCorrectedSparklerTest.ino
 Created:	5/13/2018 3:20:47 PM
 Author:	Cedric
*/

Sparkler led1 = Sparkler("LED1", 5, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Sparkler led2 = Sparkler("LED2", 4, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Sparkler led3 = Sparkler("LED3", 0, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Sparkler led4 = Sparkler("LED4", 2, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(921600);

	analogWriteRange(BRIGHTNESS_TYPE_MAX);

	led1.setBrightness(3000);
	led1.setIntensity(1000);
	led1.setSparkInterval(20);

	led1.filter.enable();
	led1.filter.setSmoothing(0.999);

	led2.setBrightness(3000);
	led2.setIntensity(1000);
	led2.setSparkInterval(250);

	led2.filter.enable();
	led2.filter.setSmoothing(0.999);

	led3.setBrightness(2000);
	led3.setIntensity(2000);
	led3.setSparkInterval(20);

	led4.setBrightness(2000);
	led4.setIntensity(2000);
	led4.setSparkInterval(250);

}

// the loop function runs over and over again until power down or reset
void loop() {
  
	led1.updateAndWrite();
	led2.updateAndWrite();
	led3.updateAndWrite();
	led4.updateAndWrite();

}

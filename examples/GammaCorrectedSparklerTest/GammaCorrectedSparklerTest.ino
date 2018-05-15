
#include <GammaCorrectedSparkler.h>


/*
 Name:		GammaCorrectedSparklerTest.ino
 Created:	5/13/2018 3:20:47 PM
 Author:	Cedric
*/

GammaCorrectedSparkler led1 = GammaCorrectedSparkler("LED1", 5, true, 0, 1023);

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(921600);

	analogWriteRange(BRIGHTNESS_TYPE_MAX);

	led1.enable();

	led1.setIntensity(500);

	led1.setSparkInterval(20);

	led1.setLowPassFilterEnabled(true);

	led1.setLowPassFilterSmoothing(0.9);

	led1.fadeWave(5000, 0);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
	analogWrite(led1.getPin(), led1.update());

	delay(5);

}

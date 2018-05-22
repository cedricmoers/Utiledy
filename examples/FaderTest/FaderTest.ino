
#include <Fader.h>

// Create 4 faders, where the second one has the gammacorrection disabled.
Fader led1 = Fader("LED1", 5, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Fader led2 = Fader("LED2", 4, GAMMACORRECTION_OFF, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Fader led3 = Fader("LED3", 0, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Fader led4 = Fader("LED4", 2, GAMMACORRECTION_OFF, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);

void setup()
{

	Serial.begin(921600);

	analogWriteRange(BRIGHTNESS_TYPE_MAX);

	led1.fadeWave(1000, 0);
	led2.fadeWave(1000, 0);
	led3.fadeWave(1000, 8);
	led4.fadeWave(1000, 8);

}

void loop()
{
	led1.updateAndWrite();
	led2.updateAndWrite();
	led3.updateAndWrite();
	led4.updateAndWrite();
}


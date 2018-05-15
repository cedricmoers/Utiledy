
#include <GammaCorrectedLED.h>

GammaCorrectedLED led1 = GammaCorrectedLED("LED1", 5, true, 0, 1023);
GammaCorrectedLED led2 = GammaCorrectedLED("LED2", 4, true, 0, 1023);
GammaCorrectedLED led3 = GammaCorrectedLED("LED3", 0, true, 0, 1023);
GammaCorrectedLED led4 = GammaCorrectedLED("LED4", 2, true, 0, 1023);

bool led1UpDown = true;
bool led2UpDown = true;
bool led3UpDown = true;
bool led4UpDown = true;

unsigned long led1PreviousUpdateTimestamp = 0;
unsigned long led2PreviousUpdateTimestamp = 0;
unsigned long led3PreviousUpdateTimestamp = 0;
unsigned long led4PreviousUpdateTimestamp = 0;

unsigned long led1UpdateInterval = 5;
unsigned long led2UpdateInterval = 10;
unsigned long led3UpdateInterval = 15;
unsigned long led4UpdateInterval = 20;


void setup()
{
	Serial.begin(921600);

	delay(2000);
	 
	led1.enable();
	led2.enable();
	led3.enable();
	led4.enable();

	led1.setUnscaledBrightness(0);
	led2.setUnscaledBrightness(0);
	led3.setUnscaledBrightness(0);
	led4.setUnscaledBrightness(0);
}

void loop()
{
	unsigned long now = millis();
	processLEDFade(led1, led1UpdateInterval, now, led1PreviousUpdateTimestamp, led1UpDown);
	processLEDFade(led2, led2UpdateInterval, now, led2PreviousUpdateTimestamp, led2UpDown);
	processLEDFade(led3, led3UpdateInterval, now, led3PreviousUpdateTimestamp, led3UpDown);
	processLEDFade(led4, led4UpdateInterval, now, led4PreviousUpdateTimestamp, led4UpDown);

}

void processLEDFade(GammaCorrectedLED &led, unsigned long updateInterval, unsigned long now, unsigned long &previousUpdate, bool &upDownMemory) {
	if (updateInterval <= now - previousUpdate) {
		if (upDownMemory == true) {
			led.increaseBrightness(1);

			if (led.isMax()) {
				upDownMemory = false;
			}
		}
		else {
			led.decreaseBrightness(1);

			if (led.isMin()) {
				upDownMemory = true;
			}
		}

		analogWrite(led.getPin(), led.update());
		previousUpdate = now;
	}
}

// #define BRIGHTNESS_RES_12BIT

#include <Blinker.h>

// Create 4 blinkers.
Blinker led1 = Blinker("LED1", 5, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Blinker led2 = Blinker("LED2", 4, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Blinker led3 = Blinker("LED3", 0, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Blinker led4 = Blinker("LED4", 2, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);

void setup()
{
	// Start serial communication.
	Serial.begin(921600);

	// Set the pwm range of the board.
	analogWriteRange(BRIGHTNESS_TYPE_MAX);

	// Set the high brightness of all the leds.
	led1.setHighBrightness(2000);
	led2.setHighBrightness(2049);
	led3.setHighBrightness(2048);
	led4.setHighBrightness(2048);

	// Set the low brightness of all the leds.
	led1.setLowBrightness(0);
	led2.setLowBrightness(2048);
	led3.setLowBrightness(0);
	led4.setLowBrightness(1024);

	// Set the high time of all the leds.
	led1.setHighTime(1000);
	led2.setHighTime(1000);
	led3.setHighTime(100);
	led4.setHighTime(50);
	
	// Set the low brightness of all the leds.
	led1.setLowTime(1000);
	led2.setLowTime(0);
	led3.setLowTime(100);
	led4.setLowTime(150);

	// Set the offset of all the leds.
	led1.setOffset(0);
	led2.setOffset(0);
	led3.setOffset(5000);
	led4.setOffset(10000);

	// Enable filters and set smoothing where needed.
	led1.filter.enable();
	led1.filter.setSmoothing(0.9);

	led3.filter.enable();
	led3.filter.setSmoothing(0.9);

	// Start the blinking functionality for all leds.
	led1.start();
	led2.start();
	led3.start();
	led4.start();

	// Enable fadewave functionality where needed.
	led1.fadeWave(5000, 0);
	led2.fadeWave(2000, 0);
}

void loop()
{
	// Read serial input.
	char * received = readStringWithLineEnding();

	// Process serial input.
	if (strcmp(received, "pause") == 0) {
		// When "pause" is received, pause the blinker
		led1.pause();
		led2.pause();
		led3.pause();
		led4.pause();
	}
	else if (strcmp(received, "run") == 0) {
		// When "run" is received, start the blinker
		led1.start();
		led2.start();
		led3.start();
		led4.start();
	}
	else if (strcmp(received, "stop") == 0) {
		// When "stop" is received, stop the blinker
		led1.stop();
		led2.stop();
		led3.stop();
		led4.stop();
	}

	// Update the leds and write the corrected brightness to their corresponding output.
	led1.updateAndWrite();
	led2.updateAndWrite();
	led3.updateAndWrite();
	led4.updateAndWrite();
}

// Read serial input until a line ending is received, returns a string.
char * readStringWithLineEnding() {

	char str[32] = "";
	char lineEnding = '\n';

	int i = 0;

	while (Serial.available()) {
		char receivedCharacter = Serial.read();

		if (receivedCharacter != lineEnding && i <= sizeof(str)/sizeof(char)) {
			str[i] = receivedCharacter;
		}
		else {
			str[i] = '\0'; // terminate the string
			break;
		}

		i++;

		if (Serial.available() == 0) {
			delay(5);
		}
	}

	if (strcmp(str, "") != 0) {
		Serial.print("Received:");
		Serial.println(str);
	}

	return str;
}


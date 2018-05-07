
#include <GammaCorrectedFader.h>

GammaCorrectedFader led1 = GammaCorrectedFader("LED1", 5, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
//GammaCorrectedFader led2 = GammaCorrectedFader("LED2", 4, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
//GammaCorrectedFader led3 = GammaCorrectedFader("LED3", 0, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
//GammaCorrectedFader led4 = GammaCorrectedFader("LED4", 2, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);

unsigned long led1PreviousUpdateTimestamp = 0;
unsigned long led2PreviousUpdateTimestamp = 0;
unsigned long led3PreviousUpdateTimestamp = 0;
unsigned long led4PreviousUpdateTimestamp = 0;

unsigned long led1UpdateInterval = 10;
unsigned long led2UpdateInterval = 10;
unsigned long led3UpdateInterval = 10;
unsigned long led4UpdateInterval = 10;

void setup()
{

	Serial.begin(921600);

	analogWriteRange(BRIGHTNESS_TYPE_MAX);

	//Countdown
	for (int i = 5; i > 0; i--)
	{
		delay(1000);
		Serial.println(i);
	}

	led1.enable();
	//led2.enable();
	//led3.enable();
	//led4.enable();

	led1.fadeWave(1000, 5);


}

void loop()
{
	char * received = readStringWithLineEnding();

	//if (strcmp(received, "pause") == 0) {
	//	//pause the blinker
	//	led1.pause();
	//	led2.pause();
	//	led3.pause();
	//	led4.pause();
	//}
	//else if (strcmp(received, "run") == 0) {
	//	//start (run)
	//	led1.start();
	//	led2.start();
	//	led3.start();
	//	led4.start();
	//}
	//else if (strcmp(received, "stop") == 0) {
	//	//stop
	//	led1.stop();
	//	led2.stop();
	//	led3.stop();
	//	led4.stop();
	//}

	led1.update();
	//led2.update();
	//led3.update();
	//led4.update();

	unsigned long now = millis();
}

char * readStringWithLineEnding() {

	char str[32] = "";
	char lineEnding = '\n';

	int i = 0;

	while (Serial.available()) {
		char receivedCharacter = Serial.read();

		if (receivedCharacter != lineEnding && i <= sizeof(str) / sizeof(char)) {
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


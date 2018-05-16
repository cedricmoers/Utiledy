#include <Blinker.h>

Blinker led1 = Blinker("LED1", 5, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Blinker led2 = Blinker("LED2", 4, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Blinker led3 = Blinker("LED3", 0, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);
Blinker led4 = Blinker("LED4", 2, GAMMACORRECTION_ON, BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX);

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
	for (int i = 0; i > 0 ; i--)
	{
		delay(1000);
		Serial.println(i);
	}

	led1.enable();
	//led2.enable();
	//led3.enable();
	//led4.enable();

	led1.setHighBrightness(2000);
	//led2.setHighBrightness(4095);
	//led3.setHighBrightness(2048);
	//led4.setHighBrightness(2048);

	led1.setLowBrightness(0);
	//led2.setLowBrightness(1024);
	//led3.setLowBrightness(0);
	//led4.setLowBrightness(1024);

	led1.setHighTime(1000);
	//led2.setHighTime(200);
	//led3.setHighTime(100);
	//led4.setHighTime(50);

	led1.setLowTime(1000);
	//led2.setLowTime(800);
	//led3.setLowTime(100);
	//led4.setLowTime(150);

	led1.setOffset(0);
	//led2.setOffset(5000);
	//led3.setOffset(10000);
	//led4.setOffset(15000);

	led1.setLowPassFilterEnabled(true);
	led1.setLowPassFilterSmoothing(0.1);

	led1.start();

	led1.fadeWave(5000, 0);

	//led2.start();
	//led3.start();
	//led4.start();
}

void loop()
{
	char * received = readStringWithLineEnding();

	if (strcmp(received, "pause") == 0) {
		//pause the blinker
		led1.pause();
		led2.pause();
		led3.pause();
		led4.pause();
	}
	else if (strcmp(received, "run") == 0) {
		//start (run)
		led1.start();
		led2.start();
		led3.start();
		led4.start();
	}
	else if (strcmp(received, "stop") == 0) {
		//stop
		led1.stop();
		led2.stop();
		led3.stop();
		led4.stop();
	}

	analogWrite(led1.getPin(), led1.update());
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


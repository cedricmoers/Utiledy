// GammaCorrectedBlinker.h

#include "c:\Users\Cedric\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\cores\esp8266\Arduino.h"

#ifndef _GAMMACORRECTEDBLINKER_h
#define _GAMMACORRECTEDBLINKER_h
#include "GammaCorrectedLED.h"

//#if defined(ARDUINO) && ARDUINO >= 100
//	#include "arduino.h"
//#else
//	#include "WProgram.h
//#endif
//
#endif

class GammaCorrectedBlinker : public GammaCorrectedLED
{

public :


	//Constants
	static const uint8_t BLINKMODE_STOPPED = 0;
	static const uint8_t BLINKMODE_RUNNING = 1;
	static const uint8_t BLINKMODE_PAUSED = 2;

	//Main constructor
	GammaCorrectedBlinker(char* identificator,
		uint8_t ledPin,
		bool gammaCorrection = false,
		BRIGHTNESS_TYPE lowerLimit = BRIGHTNESS_TYPE_MIN,
		BRIGHTNESS_TYPE upperLimit = BRIGHTNESS_TYPE_MAX);


	//Setters
	void setHighTime(uint16_t onTime);
	void setLowTime(uint16_t offTime);
	void setOffset(uint16_t offset);
	void setHighBrightness(BRIGHTNESS_TYPE brightness);
	void setLowBrightness(BRIGHTNESS_TYPE brightness);

	void setMode(uint8_t newMode);



	//Getters
	uint16_t getHighTime();										//Returns the on time of the led in blink mode.
	uint16_t getLowTime();										//Returns the off time of the led in blink mode.
	uint16_t getOffset();										//Returns the offset time of the led in blink mode.
	BRIGHTNESS_TYPE getHighBrightness();
	BRIGHTNESS_TYPE getLowBrightness();

	uint8_t getMode();
	bool getOutputState();

	bool isOn();
	bool isOff();

	bool isStopped();
	bool isRunning();
	bool isPaused();

	//Methods
	BRIGHTNESS_TYPE update();
	void start();
	void pause();
	void stop();
	void reset();

	//using GammaCorrectedLED::update;
	//	void blink(uint16_t highTime, uint16_t lowTime, BRIGHTNESS_TYPE highBrightness, BRIGHTNESS_TYPE lowBrightness, int number);
	//	void blink(uint16_t highTime, uint16_t lowTime, BRIGHTNESS_TYPE highBrightness, BRIGHTNESS_TYPE lowBrightness);


private :

	uint8_t			mode = BLINKMODE_STOPPED;

	void setOutputState(bool state);

	uint16_t		highTime;
	uint16_t		lowTime;
	uint16_t		offset;
	bool			offsetInProgress;

	bool			state;

	BRIGHTNESS_TYPE highBrightness;
	BRIGHTNESS_TYPE lowBrightness;

	unsigned long previousToggleTimestamp;
};
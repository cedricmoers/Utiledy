// UltiLED.h

#include "c:\Users\Cedric\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\cores\esp8266\Arduino.h"

#ifndef _ULTILED_h
#define _ULTILED_h

//#if defined(ARDUINO) && ARDUINO >= 100
//	#include "arduino.h"
//#else
//	#include "WProgram.h
//#endif

#define ULTILEDMODE_NORMAL 0
#define ULTILEDMODE_BLINKER 1
#define ULTILEDMODE_SPARKLER 2

#ifndef _GAMMACORRECTEDSPARKLER_h
#include "GammaCorrectedSparkler.h"
#endif

#ifndef _GAMMACORRECTEDBLINKER_h
#include "GammaCorrectedBlinker.h"
#endif
//
#endif



class UltiLED : public GammaCorrectedBlinker, public GammaCorrectedSparkler
{
public:

	//Constructor(s)
	UltiLED(
		char* identificator,
		uint8_t ledPin,
		bool gammaCorrection /*= true*/,
		BRIGHTNESS_TYPE lowerLimit /*= BRIGHTNESS_TYPE_MIN*/,
		BRIGHTNESS_TYPE upperLimit /*= BRIGHTNESS_TYPE_MAX*/);

	void setUnscaledBrightness(BRIGHTNESS_TYPE value) override;
	BRIGHTNESS_TYPE getUnscaledBrightness() override;
	BRIGHTNESS_TYPE getMinUnscaledBrightness() override;
	BRIGHTNESS_TYPE getMaxUnscaledBrightness() override;

	void setToSpark(BRIGHTNESS_TYPE intensity, BRIGHTNESS_TYPE average, unsigned long sparkUpdateInterval);
	void setToSpark(BRIGHTNESS_TYPE intensity, unsigned long sparkUpdateInterval);
	void setToSpark(BRIGHTNESS_TYPE intensity);
	void setToSpark();

	void setToBlink(BRIGHTNESS_TYPE highBrightness, BRIGHTNESS_TYPE lowBrightness, unsigned long highTime, unsigned long lowTime);
	void setToBlink(unsigned long highTime, unsigned long lowTime);
	void setToBlink(BRIGHTNESS_TYPE highBrightness, BRIGHTNESS_TYPE lowBrightness);
	void setToBlink();

	void setMode(uint8_t value);
	uint8_t getMode();

	BRIGHTNESS_TYPE update();

private:

	uint8_t mode;

};
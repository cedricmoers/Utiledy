// UltiLED.h


#ifndef _ULTILED_h
#define _ULTILED_h

#define ULTILEDMODE_NORMAL 0
#define ULTILEDMODE_BLINKER 1
#define ULTILEDMODE_SPARKLER 2

#ifndef _SPARKLER_h
#include "Sparkler.h"
#endif

#ifndef _BLINKER_h
#include "Blinker.h"
#endif
//
#endif



class UltiLED : public Blinker, public Sparkler
{
public:

	//Constructor(s)
	UltiLED(
		char* identificator,
		uint8_t ledPin,
		bool gammaCorrection /*= true*/,
		BRIGHTNESS_TYPE lowerLimit /*= BRIGHTNESS_TYPE_MIN*/,
		BRIGHTNESS_TYPE upperLimit /*= BRIGHTNESS_TYPE_MAX*/);

	void setBrightness(BRIGHTNESS_TYPE value) override;
	BRIGHTNESS_TYPE getBrightness() override;
	BRIGHTNESS_TYPE getMinBrightness() override;
	BRIGHTNESS_TYPE getMaxBrightness() override;

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

	BRIGHTNESS_TYPE update() override;

private:

	uint8_t mode;

};
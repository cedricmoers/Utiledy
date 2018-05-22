// Sparkler.h


#ifndef _SPARKLER_h
#define _SPARKLER_h

#ifndef _FADER_h
#include "Fader.h"
#endif

#endif




class Sparkler : public virtual Fader
{
public:

	//Main constructor
	Sparkler(char* identificator,
		uint8_t ledPin,
		bool gammaCorrection = false,
		BRIGHTNESS_TYPE lowerLimit = BRIGHTNESS_TYPE_MIN,
		BRIGHTNESS_TYPE upperLimit = BRIGHTNESS_TYPE_MAX);

	BRIGHTNESS_TYPE getIntensity();									//Returns the intensity of the sparkler.
	unsigned long getSparkInterval();								//Returns the interval on which new random sparks are generated.

	void setIntensity(BRIGHTNESS_TYPE value);
	void setSparkInterval(unsigned long updateInterval);			//Sets the update interval on which new sparks will be generated.
	void setBrightness(BRIGHTNESS_TYPE value) override;

	BRIGHTNESS_TYPE getSparkedBrightness();
	BRIGHTNESS_TYPE getBrightness() override;				// Returns the value of the current brightness.
	BRIGHTNESS_TYPE getMinBrightness() override;
	BRIGHTNESS_TYPE getMaxBrightness() override;
	BRIGHTNESS_TYPE update() override;

private:

	void setSparkedBrightness(BRIGHTNESS_TYPE value);

	BRIGHTNESS_TYPE intensity;
	BRIGHTNESS_TYPE sparkedBrightness;

	unsigned long sparkInterval;
	unsigned long previousSparkTimestamp;

};
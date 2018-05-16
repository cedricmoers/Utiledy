// Sparkler.h

#include "c:\Users\Cedric\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\cores\esp8266\Arduino.h"

#ifndef _SPARKLER_h
#define _SPARKLER_h

//#if defined(ARDUINO) && ARDUINO >= 100
//	#include "arduino.h"
//#else
//	#include "WProgram.h
//#endif
//

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
	void setSparkedBrightness(BRIGHTNESS_TYPE value);
	void setUnscaledBrightness(BRIGHTNESS_TYPE value) override;

	BRIGHTNESS_TYPE getSparkedBrightness();
	BRIGHTNESS_TYPE getUnscaledBrightness() override;				// Returns the value of the current brightness.
	BRIGHTNESS_TYPE getMinUnscaledBrightness() override;
	BRIGHTNESS_TYPE getMaxUnscaledBrightness() override;
	BRIGHTNESS_TYPE update();

private:

	BRIGHTNESS_TYPE intensity;
	BRIGHTNESS_TYPE sparkedBrightness;

	unsigned long sparkInterval;
	unsigned long previousSparkTimestamp;


};
// Fader.h



#ifndef _FADER_h
#define _FADER_h
#define FADEMODE_UP 1
#define FADEMODE_DOWN 2
#define FADEMODE_IDLE 0

#ifndef _GAMMALED_h
#include "GammaLED.h"
#endif

#endif




class Fader : public GammaLED
{
public:

	// Main constructor
	Fader(char* identificator,
		uint8_t ledPin,
		bool gammaCorrection = false,
		BRIGHTNESS_TYPE lowerLimit = BRIGHTNESS_TYPE_MIN,
		BRIGHTNESS_TYPE upperLimit = BRIGHTNESS_TYPE_MAX);



	// Functions
	BRIGHTNESS_TYPE update() override;

	void fadeToValue(uint16_t time, BRIGHTNESS_TYPE brightness);		//Fade the led to a given value, within the given time.
	void fadeToMax(uint16_t time);										//Fade the led to fully on within the given time.
	void fadeToMin(uint16_t time);										//Fade the led to fully off within the given time.
	void fadeToggle(uint16_t time);										//Fade the led to fully off within the given time. Depending on its current state.
	void fadeWave(uint16_t minToMaxTime, uint16_t numberOfTimes = 0);	//Fade the LED sequentially on and off for a given amount of times.
	// void stopFade();													//Stops the LED from fading. Sets the remaining waves to 0.
	// void pauseFade();												//Pauses the fading of the LED.
	// void resumeFade();
	
	uint8_t getFadeMode();
	bool isFadingUp();
	bool isFadingDown();
	bool isFadeInProgress();											// Returns true if the current unscaled brightness is not equal to the ending brightness. 
	bool isFadeWaving();												// Indicates if the fader is fade waving.
	bool isContinuouslyFadeWaving();

	void setContinuouslyFadeWaving(bool state);

	void setCurrentFadeEndBrightness(BRIGHTNESS_TYPE brightness);
	void setCurrentFadeStartBrightness(BRIGHTNESS_TYPE brightness);
	void setCurrentFadeStartTime(unsigned long time);

	BRIGHTNESS_TYPE getCurrentFadeEndBrightness();
	BRIGHTNESS_TYPE getCurrentFadeStartBrightness();
	unsigned long getCurrentFadeStartTime();

	void setFadeWavesLeft(uint16_t numberOfWaves);
	uint16_t getFadeWavesLeft();

	void setMinToMaxTime(unsigned long value);
	unsigned long getMinToMaxTime();

private:

	// Fields

	uint8_t fadeMode;
	void setFadeMode(uint8_t value);

	bool continuouslyFadeWaving;

	uint16_t fadeWavesLeft = 0;

	BRIGHTNESS_TYPE currentFadeEndBrightness;
	BRIGHTNESS_TYPE currentFadeStartBrightness;

	unsigned long currentFadeStartTime;
	unsigned long minToMaxTime;
};
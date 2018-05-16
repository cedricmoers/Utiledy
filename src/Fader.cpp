// 
// 
// 

#include "Fader.h"

Fader::Fader(
	char* identificator,
	uint8_t ledPin,
	bool gammaCorrection /*= true*/,
	BRIGHTNESS_TYPE lowerLimit /*= BRIGHTNESS_TYPE_MIN*/,
	BRIGHTNESS_TYPE upperLimit /*= BRIGHTNESS_TYPE_MAX*/)
	:
	GammaLED(identificator, ledPin, gammaCorrection, lowerLimit, lowerLimit)
{
	setCurrentFadeEndBrightness(0);
	setCurrentFadeStartTime(0);
	setContinuouslyFadeWaving(false);
	setMinToMaxTime(0);
	setFadeWavesLeft(0);
	setFadeMode(FADEMODE_IDLE);
}


void Fader::fadeToValue(uint16_t time, BRIGHTNESS_TYPE brightness) {

	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Fading to value: ");
	DEBUG_PRINT(brightness);
	DEBUG_PRINT_F(" within: ");
	DEBUG_PRINT(time);
	DEBUG_PRINTLN_F("ms.");

	if (brightness == getUnscaledBrightness()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Brightness is already at that value.");

		setFadeMode(FADEMODE_IDLE);
		return;
	}
	else if (brightness > getUnscaledBrightness()) {
		setFadeMode(FADEMODE_UP);
	}
	else if (brightness < getUnscaledBrightness()) {
		setFadeMode(FADEMODE_DOWN);
	}

	setCurrentFadeStartBrightness(getUnscaledBrightness());
	setCurrentFadeEndBrightness(brightness);
	setCurrentFadeStartTime(millis());
	setMinToMaxTime(time);
}

void Fader::fadeToMax(uint16_t time)
{
	fadeToValue(time, getMaxUnscaledBrightness());
}

void Fader::fadeToMin(uint16_t time)
{
	fadeToValue(time, getMinUnscaledBrightness());
}

void Fader::fadeToggle(uint16_t time)
{
	if (getUnscaledBrightness() > getMinUnscaledBrightness()) {
		fadeToMin(time);
	}
	else {
		fadeToMax(time);
	}
}

bool Fader::isFadingUp()
{
	return getFadeMode() == FADEMODE_UP;
}

bool Fader::isFadingDown()
{
	return getFadeMode() == FADEMODE_DOWN;
}

bool Fader::isFadeInProgress() {

	return !(getFadeMode() == FADEMODE_IDLE);
}

void Fader::fadeWave(uint16_t minToMaxTime, uint16_t numberOfTimes /*= 0*/) {

	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Starting to wave "); 
	if (numberOfTimes == 0) {
		DEBUG_PRINT_F("continuously,");
	}
	else {
		DEBUG_PRINT_F("for ");
		DEBUG_PRINT_F(numberOfTimes);
		DEBUG_PRINT_F(" times,")
	}
	DEBUG_PRINT_F(" with min to max time: ");
	DEBUG_PRINT(minToMaxTime);
	DEBUG_PRINTLN_F("ms.");

	if (numberOfTimes == 0) {
		setContinuouslyFadeWaving(true);		// Implicitly sets the remaining waves to zero.
	}
	else {
		setContinuouslyFadeWaving(false);
		setFadeWavesLeft(numberOfTimes);
	}

	fadeToMax(minToMaxTime);
}

bool Fader::isFadeWaving() {

	if (getFadeWavesLeft() > 0 || isContinuouslyFadeWaving()) {
		return true;
	}
	else {
		return false;
	}
}

bool Fader::isContinuouslyFadeWaving() {

	return this->fadeWaveContinuous;
}


void Fader::setContinuouslyFadeWaving(bool state)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting continuously fade waving to: ");
	DEBUG_PRINT(state ? "true" : "false");
	DEBUG_PRINTLN_F(".");

	if (state == true) {
		setFadeWavesLeft(0);
	}

	this->fadeWaveContinuous = state;
}


BRIGHTNESS_TYPE Fader::update() {

	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Updating Fader");

	if (isFadeInProgress()) {

		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Fade in progress");

		unsigned long now = millis();
		unsigned long elapsed = now - getCurrentFadeStartTime();
		unsigned int units;

		if (getMinToMaxTime() != 0.0) {
			float avgMinToMaxSpeed = ((float)BRIGHTNESS_TYPE_MAX - (float)BRIGHTNESS_TYPE_MIN) / (float)getMinToMaxTime(); //   units/ms
			units = (unsigned int)(avgMinToMaxSpeed * (float)elapsed);
		}
		else {
			units = BRIGHTNESS_TYPE_MAX;
		}

		// Increasing brightness
		if (isFadingUp()) {

			long newBrightness = (long)getCurrentFadeStartBrightness() + (long)units;

			if (newBrightness >= (long)getCurrentFadeEndBrightness() || elapsed >= getMinToMaxTime() || newBrightness >= (long)getMaxUnscaledBrightness()) {
				DEBUG_PRINT_HEADER();
				DEBUG_PRINT_F("Desired brightness reached by increasing, ");
				DEBUG_PRINTLN_F(".");

				setUnscaledBrightness(getCurrentFadeEndBrightness());

				setFadeMode(FADEMODE_IDLE);

				if (isFadeWaving()) {
					fadeToMin(getMinToMaxTime());
					setFadeWavesLeft(getFadeWavesLeft() - 1);
				}
			}
			else {
				setUnscaledBrightness(newBrightness);
			}
		}

		// Decreasing brightness
		else if (isFadingDown()) {

			long newBrightness = (long)getCurrentFadeStartBrightness() - (long)units;

			if (newBrightness <= (long)getCurrentFadeEndBrightness() || elapsed >= getMinToMaxTime() || newBrightness <= (long)getMinUnscaledBrightness()) {
				DEBUG_PRINT_HEADER();
				DEBUG_PRINT_F("Desired brightness reached by decreasing, ");
				DEBUG_PRINTLN_F(".");

				setUnscaledBrightness(getCurrentFadeEndBrightness());

				setFadeMode(FADEMODE_IDLE);

				if (isFadeWaving()) {
					if (getFadeWavesLeft() > 0) {
						fadeToMax(getMinToMaxTime());

					}
				}
			}
			else {
				setUnscaledBrightness(newBrightness);
			}
		}
	}
	else {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Fade not in progress");
	}

	return this->GammaLED::update();
}


BRIGHTNESS_TYPE Fader::update(BRIGHTNESS_TYPE value) {

	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Updating Fader");

	if (isFadeInProgress()) {

		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Fade in progress");

		unsigned long now = millis();
		unsigned long elapsed = now - getCurrentFadeStartTime();
		unsigned int units;

		if (getMinToMaxTime() != 0.0) {
			float avgMinToMaxSpeed = ((float)BRIGHTNESS_TYPE_MAX - (float)BRIGHTNESS_TYPE_MIN) / (float)getMinToMaxTime(); //   units/ms
			units = (unsigned int)(avgMinToMaxSpeed * (float)elapsed);
		}
		else {
			units = BRIGHTNESS_TYPE_MAX;
		}

		// Increasing brightness
		if (isFadingUp()) {

			long newBrightness = (long)getCurrentFadeStartBrightness() + (long)units;

			if (newBrightness >= (long)getCurrentFadeEndBrightness() || elapsed >= getMinToMaxTime() || newBrightness >= (long)getMaxUnscaledBrightness()) {
				DEBUG_PRINT_HEADER();
				DEBUG_PRINT_F("Desired brightness reached by increasing, ");
				DEBUG_PRINTLN_F(".");

				setUnscaledBrightness(getCurrentFadeEndBrightness());

				setFadeMode(FADEMODE_IDLE);

				if (isFadeWaving()) {
					fadeToMin(getMinToMaxTime());
					setFadeWavesLeft(getFadeWavesLeft() - 1);
				}
			}
			else {
				setUnscaledBrightness(newBrightness);
			}
		}

		// Decreasing brightness
		else if (isFadingDown()) {

			long newBrightness = (long)getCurrentFadeStartBrightness() - (long)units;

			if (newBrightness <= (long)getCurrentFadeEndBrightness() || elapsed >= getMinToMaxTime() || newBrightness <= (long)getMinUnscaledBrightness()) {
				DEBUG_PRINT_HEADER();
				DEBUG_PRINT_F("Desired brightness reached by decreasing, ");
				DEBUG_PRINTLN_F(".");

				setUnscaledBrightness(getCurrentFadeEndBrightness());

				setFadeMode(FADEMODE_IDLE);

				if (isFadeWaving()) {
					if (getFadeWavesLeft() > 0) {
						fadeToMax(getMinToMaxTime());

					}
				}
			}
			else {
				setUnscaledBrightness(newBrightness);
			}
		}
	}
	else {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Fade not in progress");
	}

	return this->GammaLED::update(value);
}


void Fader::setCurrentFadeEndBrightness(BRIGHTNESS_TYPE brightness)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting fade end brightness to: ");
	DEBUG_PRINT(brightness);
	DEBUG_PRINTLN_F(".");

	this->currentFadeEndBrightness = brightness;
}

void Fader::setCurrentFadeStartBrightness(BRIGHTNESS_TYPE brightness)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting fade start brightness to: ");
	DEBUG_PRINT(brightness);
	DEBUG_PRINTLN_F(".");

	this->currentFadeStartBrightness = brightness;
}

void Fader::setCurrentFadeStartTime(unsigned long time)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting fade start time to: ");
	DEBUG_PRINT(time);
	DEBUG_PRINTLN_F(".");

	this->currentFadeStartTime = time;
}

BRIGHTNESS_TYPE Fader::getCurrentFadeEndBrightness()
{
	return this->currentFadeEndBrightness;
}

BRIGHTNESS_TYPE Fader::getCurrentFadeStartBrightness()
{
	return this->currentFadeStartBrightness;
}

unsigned long Fader::getCurrentFadeStartTime()
{
	return this->currentFadeStartTime;
}

void Fader::setFadeWavesLeft(uint16_t numberOfWaves)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting remaining fade waves to: ");
	DEBUG_PRINT(numberOfWaves);
	DEBUG_PRINTLN_F(".");

	this->fadeWavesLeft = numberOfWaves;
}

uint16_t Fader::getFadeWavesLeft()
{
	return this->fadeWavesLeft;
}

uint8_t Fader::getFadeMode()
{
	return this->fadeMode;
}

void Fader::setMinToMaxTime(unsigned long value)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting min to max time to: ");
	DEBUG_PRINT(value);
	DEBUG_PRINTLN_F(".");

	this->minToMaxTime = value;
}

unsigned long Fader::getMinToMaxTime()
{
	return this->minToMaxTime;
}

void Fader::setFadeMode(uint8_t value)
{
	DEBUG_PARAMETER("Setting fade mode to:", value);
	this->fadeMode = value;
}

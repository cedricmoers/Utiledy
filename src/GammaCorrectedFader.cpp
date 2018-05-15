// 
// 
// 

#include "GammaCorrectedFader.h"

GammaCorrectedFader::GammaCorrectedFader(
	char* identificator,
	uint8_t ledPin,
	bool gammaCorrection /*= true*/,
	BRIGHTNESS_TYPE lowerLimit /*= BRIGHTNESS_TYPE_MIN*/,
	BRIGHTNESS_TYPE upperLimit /*= BRIGHTNESS_TYPE_MAX*/)
	:
	GammaCorrectedLED(identificator, ledPin, gammaCorrection, lowerLimit, lowerLimit)
{
	setCurrentFadeEndBrightness(0);
	setCurrentFadeStartTime(0);
	setContinuouslyFadeWaving(false);
	setMinToMaxTime(0);
	setFadeWavesLeft(0);
	setFadeMode(FADEMODE_IDLE);
}


void GammaCorrectedFader::fadeToValue(uint16_t time, BRIGHTNESS_TYPE brightness) {

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

void GammaCorrectedFader::fadeToMax(uint16_t time)
{
	fadeToValue(time, getMaxUnscaledBrightness());
}

void GammaCorrectedFader::fadeToMin(uint16_t time)
{
	fadeToValue(time, getMinUnscaledBrightness());
}

void GammaCorrectedFader::fadeToggle(uint16_t time)
{
	if (getUnscaledBrightness() > getMinUnscaledBrightness()) {
		fadeToMin(time);
	}
	else {
		fadeToMax(time);
	}
}

bool GammaCorrectedFader::isFadingUp()
{
	return getFadeMode() == FADEMODE_UP;
}

bool GammaCorrectedFader::isFadingDown()
{
	return getFadeMode() == FADEMODE_DOWN;
}

bool GammaCorrectedFader::isFadeInProgress() {

	return !(getFadeMode() == FADEMODE_IDLE);
}

void GammaCorrectedFader::fadeWave(uint16_t minToMaxTime, uint16_t numberOfTimes /*= 0*/) {

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

bool GammaCorrectedFader::isFadeWaving() {

	if (getFadeWavesLeft() > 0 || isContinuouslyFadeWaving()) {
		return true;
	}
	else {
		return false;
	}
}

bool GammaCorrectedFader::isContinuouslyFadeWaving() {

	return this->fadeWaveContinuous;
}


void GammaCorrectedFader::setContinuouslyFadeWaving(bool state)
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


BRIGHTNESS_TYPE GammaCorrectedFader::update() {

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

	return this->GammaCorrectedLED::update();
}


BRIGHTNESS_TYPE GammaCorrectedFader::update(BRIGHTNESS_TYPE value) {

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

	return this->GammaCorrectedLED::update(value);
}


void GammaCorrectedFader::setCurrentFadeEndBrightness(BRIGHTNESS_TYPE brightness)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting fade end brightness to: ");
	DEBUG_PRINT(brightness);
	DEBUG_PRINTLN_F(".");

	this->currentFadeEndBrightness = brightness;
}

void GammaCorrectedFader::setCurrentFadeStartBrightness(BRIGHTNESS_TYPE brightness)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting fade start brightness to: ");
	DEBUG_PRINT(brightness);
	DEBUG_PRINTLN_F(".");

	this->currentFadeStartBrightness = brightness;
}

void GammaCorrectedFader::setCurrentFadeStartTime(unsigned long time)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting fade start time to: ");
	DEBUG_PRINT(time);
	DEBUG_PRINTLN_F(".");

	this->currentFadeStartTime = time;
}

BRIGHTNESS_TYPE GammaCorrectedFader::getCurrentFadeEndBrightness()
{
	return this->currentFadeEndBrightness;
}

BRIGHTNESS_TYPE GammaCorrectedFader::getCurrentFadeStartBrightness()
{
	return this->currentFadeStartBrightness;
}

unsigned long GammaCorrectedFader::getCurrentFadeStartTime()
{
	return this->currentFadeStartTime;
}

void GammaCorrectedFader::setFadeWavesLeft(uint16_t numberOfWaves)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting remaining fade waves to: ");
	DEBUG_PRINT(numberOfWaves);
	DEBUG_PRINTLN_F(".");

	this->fadeWavesLeft = numberOfWaves;
}

uint16_t GammaCorrectedFader::getFadeWavesLeft()
{
	return this->fadeWavesLeft;
}

uint8_t GammaCorrectedFader::getFadeMode()
{
	return this->fadeMode;
}

void GammaCorrectedFader::setMinToMaxTime(unsigned long value)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting min to max time to: ");
	DEBUG_PRINT(value);
	DEBUG_PRINTLN_F(".");

	this->minToMaxTime = value;
}

unsigned long GammaCorrectedFader::getMinToMaxTime()
{
	return this->minToMaxTime;
}

void GammaCorrectedFader::setFadeMode(uint8_t value)
{
	DEBUG_PARAMETER("Setting fade mode to:", value);
	this->fadeMode = value;
}

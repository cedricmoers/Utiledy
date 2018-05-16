#include "GammaCorrectedSparkler.h"

//Constructor(s)
GammaCorrectedSparkler::GammaCorrectedSparkler(
	char* identificator,
	uint8_t ledPin,
	bool gammaCorrection /*= true*/,
	BRIGHTNESS_TYPE lowerLimit /*= BRIGHTNESS_TYPE_MIN*/,
	BRIGHTNESS_TYPE upperLimit /*= BRIGHTNESS_TYPE_MAX*/)
	:
	GammaCorrectedFader(identificator, ledPin, gammaCorrection, lowerLimit, lowerLimit)
{
	setIntensity(0);
	setSparkInterval(0);
}



BRIGHTNESS_TYPE GammaCorrectedSparkler::getIntensity()
{
	return this->intensity;
}

unsigned long GammaCorrectedSparkler::getSparkInterval()
{
	return this->sparkInterval;
}

void GammaCorrectedSparkler::setIntensity(BRIGHTNESS_TYPE value)
{
	BRIGHTNESS_TYPE intensityMin = 0;
	BRIGHTNESS_TYPE intensityMax = BRIGHTNESS_TYPE_MAX / 2;

	if (value <= intensityMin) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Spark intensity of zero will have no effect, writing the value anyway, but constant mode would be better in this case.");
		
		this->intensity = intensityMin;
	}
	else if (value > intensityMax / 2) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Spark intensity should not exceed a value of: ");
		DEBUG_PRINT(intensityMax);
		DEBUG_PRINTLN_F(". Changing to that.");

		this->intensity = intensityMax;
	}
	else {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting spark intensity to: ");
		DEBUG_PRINT(value);
		DEBUG_PRINTLN_F(".");

		this->intensity = value;
	}

	// Update the brightness.
	setUnscaledBrightness(getUnscaledBrightness());

	DEBUG_PARAMETER("Unscaled Min: ", getMinUnscaledBrightness());
	DEBUG_PARAMETER("Unscaled Max: ", getMaxUnscaledBrightness());
}

void GammaCorrectedSparkler::setSparkInterval(unsigned long updateInterval)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting spark update interval to: ");
	DEBUG_PRINT(updateInterval);
	DEBUG_PRINTLN_F(" ms.");

	this->sparkInterval = updateInterval;
}

void GammaCorrectedSparkler::setSparkedBrightness(BRIGHTNESS_TYPE value)
{
	this->sparkedBrightness = value;
}

void GammaCorrectedSparkler::setUnscaledBrightness(BRIGHTNESS_TYPE value)
{
	if (value < getMinUnscaledBrightness()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("The given brightness with the current intensity will result in a brightness below zero. Changing the brightness to ");
		DEBUG_PRINT(getIntensity());
		DEBUG_PRINTLN_F(" to prevent this.");
		GammaCorrectedLED::setUnscaledBrightness(getMinUnscaledBrightness());
	}
	else if (value > getMaxUnscaledBrightness()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("The given brightness with the intensity will result in a brightness above BRIGHTNESS_TYPE_MAX. Changing the brightness to ");
		DEBUG_PRINT(BRIGHTNESS_TYPE_MAX - getIntensity());
		DEBUG_PRINTLN_F(" to prevent this.");
		GammaCorrectedLED::setUnscaledBrightness(getMaxUnscaledBrightness());
	}
	else {
		GammaCorrectedLED::setUnscaledBrightness(value);
	}
}

BRIGHTNESS_TYPE GammaCorrectedSparkler::getSparkedBrightness()
{
	return this->sparkedBrightness;
}

BRIGHTNESS_TYPE GammaCorrectedSparkler::getUnscaledBrightness()
{
	return getSparkedBrightness();
}

BRIGHTNESS_TYPE GammaCorrectedSparkler::getMinUnscaledBrightness()
{
	return getIntensity();
}

BRIGHTNESS_TYPE GammaCorrectedSparkler::getMaxUnscaledBrightness()
{
	return BRIGHTNESS_TYPE_MAX - getIntensity();
}

BRIGHTNESS_TYPE GammaCorrectedSparkler::update()
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Updating sparkler");

	unsigned long now = millis();
	unsigned long elapsed = now - this->previousSparkTimestamp;

	if (elapsed >= getSparkInterval()) {

		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Generating new spark::B:");
		DEBUG_PRINT(getUnscaledBrightness());

		BRIGHTNESS_TYPE finalBrightness = (BRIGHTNESS_TYPE) ((long)GammaCorrectedLED::getUnscaledBrightness() + random(-(long)getIntensity(), (long)getIntensity()));

		DEBUG_PRINT_F(", A:");
		DEBUG_PRINTLN(finalBrightness);

		setSparkedBrightness(finalBrightness);

		this->previousSparkTimestamp = now;
	}

	return GammaCorrectedFader::update();
}
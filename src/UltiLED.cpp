#include "UltiLED.h"

//Constructor(s)
UltiLED::UltiLED(
	char* identificator,
	uint8_t ledPin,
	bool gammaCorrection /*= true*/,
	BRIGHTNESS_TYPE lowerLimit /*= BRIGHTNESS_TYPE_MIN*/,
	BRIGHTNESS_TYPE upperLimit /*= BRIGHTNESS_TYPE_MAX*/)
	:
	Fader(identificator, ledPin, gammaCorrection, lowerLimit, lowerLimit),
	Sparkler(identificator, ledPin, gammaCorrection, lowerLimit, lowerLimit),
	Blinker(identificator, ledPin, gammaCorrection, lowerLimit, lowerLimit)
{
	setMode(ULTILEDMODE_NORMAL);
}


void UltiLED::setBrightness(BRIGHTNESS_TYPE value)
{
	switch (getMode())
	{
	case ULTILEDMODE_BLINKER :
		Blinker::setBrightness(value);
		break;

	case ULTILEDMODE_NORMAL :
		Fader::setBrightness(value);
		break;

	case ULTILEDMODE_SPARKLER : 
		Sparkler::setBrightness(value);
		break;

	default:
		break;
	}
}

BRIGHTNESS_TYPE UltiLED::getBrightness()
{
	switch (getMode())
	{
	case ULTILEDMODE_BLINKER:
		return Blinker::getBrightness();

	case ULTILEDMODE_NORMAL:
		return Fader::getBrightness();

	case ULTILEDMODE_SPARKLER:
		return Sparkler::getBrightness();

	default:
		return 0;
	}
}

BRIGHTNESS_TYPE UltiLED::getMinBrightness()
{
	switch (getMode())
	{
	case ULTILEDMODE_BLINKER:
		return Blinker::getMinBrightness();

	case ULTILEDMODE_NORMAL:
		return Fader::getMinBrightness();

	case ULTILEDMODE_SPARKLER:
		return Sparkler::getMinBrightness();

	default:
		return 0;
	}
}

BRIGHTNESS_TYPE UltiLED::getMaxBrightness()
{
	switch (getMode())
	{
	case ULTILEDMODE_BLINKER:
		return Blinker::getMaxBrightness();

	case ULTILEDMODE_NORMAL:
		return Fader::getMaxBrightness();

	case ULTILEDMODE_SPARKLER:
		return Sparkler::getMaxBrightness();

	default:
		return 0;
	}
}

void UltiLED::setToSpark(BRIGHTNESS_TYPE intensity, BRIGHTNESS_TYPE average, unsigned long sparkUpdateInterval)
{
	setBrightness(average);
	setToSpark(intensity, sparkUpdateInterval);
}

void UltiLED::setToSpark(BRIGHTNESS_TYPE intensity, unsigned long sparkUpdateInterval)
{
	setSparkInterval(sparkUpdateInterval);
	setToSpark(intensity);
}

void UltiLED::setToSpark(BRIGHTNESS_TYPE intensity)
{
	setIntensity(intensity);
	setToSpark();
}

void UltiLED::setToSpark()
{
	setMode(ULTILEDMODE_SPARKLER);
}

void UltiLED::setToBlink(BRIGHTNESS_TYPE highBrightness, BRIGHTNESS_TYPE lowBrightness, unsigned long highTime, unsigned long lowTime)
{
	setHighTime(highTime);
	setLowTime(lowTime);
	setHighBrightness(highBrightness);
	setLowBrightness(lowBrightness);
	setToBlink();
}

void UltiLED::setToBlink(unsigned long highTime, unsigned long lowTime)
{
	setHighTime(highTime);
	setLowTime(lowTime);
	setToBlink();
}

void UltiLED::setToBlink(BRIGHTNESS_TYPE highBrightness, BRIGHTNESS_TYPE lowBrightness)
{
	setHighBrightness(highBrightness);
	setLowBrightness(lowBrightness);
	setToBlink();
}

void UltiLED::setToBlink()
{
	setMode(ULTILEDMODE_BLINKER);
	start();
}

void UltiLED::setMode(uint8_t value)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting Ultiled mode to: ");
	DEBUG_PRINTLN(value);

	// Get the value of the brightness before the mode change.
	BRIGHTNESS_TYPE currentBrightness = getBrightness();

	this->mode = value;

	// Set the value to the previous brightness.
	setBrightness(currentBrightness);
}

uint8_t UltiLED::getMode()
{
	return this->mode;
}

BRIGHTNESS_TYPE UltiLED::update()
{
	switch (getMode())
	{
	case ULTILEDMODE_BLINKER:
		return Blinker::update();

	case ULTILEDMODE_NORMAL:
		return Fader::update();

	case ULTILEDMODE_SPARKLER:
		return Sparkler::update();

	default:
		return 0;
	}
}

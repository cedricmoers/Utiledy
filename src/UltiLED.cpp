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


void UltiLED::setUnscaledBrightness(BRIGHTNESS_TYPE value)
{
	switch (getMode())
	{
	case ULTILEDMODE_BLINKER :
		Blinker::setUnscaledBrightness(value);
		break;

	case ULTILEDMODE_NORMAL :
		Fader::setUnscaledBrightness(value);
		break;

	case ULTILEDMODE_SPARKLER : 
		Sparkler::setUnscaledBrightness(value);
		break;

	default:
		break;
	}
}

BRIGHTNESS_TYPE UltiLED::getUnscaledBrightness()
{
	switch (getMode())
	{
	case ULTILEDMODE_BLINKER:
		return Blinker::getUnscaledBrightness();

	case ULTILEDMODE_NORMAL:
		return Fader::getUnscaledBrightness();

	case ULTILEDMODE_SPARKLER:
		return Sparkler::getUnscaledBrightness();

	default:
		return 0;
	}
}

BRIGHTNESS_TYPE UltiLED::getMinUnscaledBrightness()
{
	switch (getMode())
	{
	case ULTILEDMODE_BLINKER:
		return Blinker::getMinUnscaledBrightness();

	case ULTILEDMODE_NORMAL:
		return Fader::getMinUnscaledBrightness();

	case ULTILEDMODE_SPARKLER:
		return Sparkler::getMinUnscaledBrightness();

	default:
		return 0;
	}
}

BRIGHTNESS_TYPE UltiLED::getMaxUnscaledBrightness()
{
	switch (getMode())
	{
	case ULTILEDMODE_BLINKER:
		return Blinker::getMaxUnscaledBrightness();

	case ULTILEDMODE_NORMAL:
		return Fader::getMaxUnscaledBrightness();

	case ULTILEDMODE_SPARKLER:
		return Sparkler::getMaxUnscaledBrightness();

	default:
		return 0;
	}
}

void UltiLED::setToSpark(BRIGHTNESS_TYPE intensity, BRIGHTNESS_TYPE average, unsigned long sparkUpdateInterval)
{
	setUnscaledBrightness(average);
	setToSpark(intensity, average, sparkUpdateInterval);
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
}

void UltiLED::setMode(uint8_t value)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting Ultiled mode to: ");
	DEBUG_PRINTLN(value);

	// Get the value of the brightness before the mode change.
	BRIGHTNESS_TYPE currentBrightness = getUnscaledBrightness();

	this->mode = value;

	// Set the value to the previous brightness.
	setUnscaledBrightness(currentBrightness);
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

#include "Blinker.h"

//Constructor(s)
Blinker::Blinker(
	char* identificator,
	uint8_t ledPin,
	bool gammaCorrection /*= true*/,
	BRIGHTNESS_TYPE lowerLimit /*= BRIGHTNESS_TYPE_MIN*/,
	BRIGHTNESS_TYPE upperLimit /*= BRIGHTNESS_TYPE_MAX*/)
	:
	Fader(identificator, ledPin, gammaCorrection, lowerLimit, lowerLimit)
{
	setHighBrightness(BRIGHTNESS_TYPE_MAX);
	setLowBrightness(BRIGHTNESS_TYPE_MIN);

	setHighTime(500);
	setLowTime(500);
	setOffset(0);

	reset();
}

//Getters
uint16_t Blinker::getLowTime() {
	return this->lowTime;
}

uint16_t Blinker::getHighTime() {
	return this->highTime;
}

uint16_t Blinker::getOffset() {
	return this->offset;
}

BRIGHTNESS_TYPE Blinker::getHighBrightness() {
	//return this->highBrightness;
	return GammaLED::getUnscaledBrightness();
}

BRIGHTNESS_TYPE Blinker::getLowBrightness() {
	return this->lowBrightness;
}

BRIGHTNESS_TYPE Blinker::getUnscaledBrightness()
{
	BRIGHTNESS_TYPE blinkBrightness;

	if (getMode() == BLINKMODE_STOPPED) {
		blinkBrightness = 0;
	}
	else if (offsetInProgress) {
		blinkBrightness = 0;
	}
	else if (isOn()) {
		blinkBrightness = getHighBrightness();
	}
	else if (isOff()) {
		blinkBrightness = getLowBrightness();
	}

	return blinkBrightness;
}

BRIGHTNESS_TYPE Blinker::getMinUnscaledBrightness()
{
	return getLowBrightness();
}

BRIGHTNESS_TYPE Blinker::getMaxUnscaledBrightness()
{
	return BRIGHTNESS_TYPE_MAX;
}

uint8_t Blinker::getMode() {
	return this->mode;
}

bool Blinker::getOutputState() {
	return this->state;
}

bool Blinker::isOn() {
	if (getOutputState() == true) {
		return true;
	}
	else {
		return false;
	}
}

bool Blinker::isOff() {
	if (getOutputState() == false) {
		return true;
	}
	else {
		return false;
	}
}


bool Blinker::isStopped()
{
	if (getMode() == BLINKMODE_STOPPED) {
		return true;
	}
	else {
		return false;
	}
}

bool Blinker::isRunning()
{
	if (getMode() == BLINKMODE_RUNNING) {
		return true;
	}
	else {
		return false;
	}
}

bool Blinker::isPaused()
{
	if (getMode() == BLINKMODE_PAUSED) {
		return true;
	}
	else {
		return false;
	}
}

void Blinker::start()
{
	setMode(BLINKMODE_RUNNING);
}

void Blinker::pause()
{
	setMode(BLINKMODE_PAUSED);
}

void Blinker::stop()
{
	if (isRunning() || isPaused()) {
		setMode(BLINKMODE_STOPPED);
	}
}

void Blinker::reset()
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Resetting blink timer.");
	this->previousToggleTimestamp = millis();
	this->offsetInProgress = true;
	setOutputState(true);

	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Done.");
}


//Setters

void Blinker::setOutputState(bool state) {
	if (getOutputState() != state) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting state to: ");
		DEBUG_PRINT(state ? "true" : "false");
		DEBUG_PRINTLN_F(".");
		this->state = state;
	}
}

void Blinker::setHighTime(uint16_t onTime) {
	if (getHighTime() != onTime) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting blink on-time to: ");
		DEBUG_PRINT(onTime);
		DEBUG_PRINTLN_F(".");
		this->highTime = onTime;
	}
}

void Blinker::setLowTime(uint16_t offTime) {
	if (getLowTime() != offTime) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting blink off-time to: ");
		DEBUG_PRINT(offTime);
		DEBUG_PRINTLN_F(".");
		this->lowTime = offTime;
	}
}

void Blinker::setOffset(uint16_t offset) {
	if (getOffset() != offset) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting blink offset to: ");
		DEBUG_PRINT(offset);
		DEBUG_PRINTLN_F(".");
		this->offset = offset;
	}
}

void Blinker::setUnscaledBrightness(BRIGHTNESS_TYPE brightness)
{
	setHighBrightness(brightness);
}


void Blinker::setHighBrightness(BRIGHTNESS_TYPE brightness) {
	if (brightness > BRIGHTNESS_TYPE_MAX || brightness < BRIGHTNESS_TYPE_MIN) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Cannot set the on-brightness to a brightness higher than BRIGHTNESS_TYPE_MAX or lower than BRIGHTNESS_TYPE_MIN. The value will be changed to BRIGHTNESS_TYPE_MAX.");
		brightness = BRIGHTNESS_TYPE_MAX;
	}
	if (brightness <= getLowBrightness()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("The blink on-brightness should not be lower than or equal to the off-brightness. The value will be changed to BRIGHTNESS_TYPE_MAX.");
		brightness = BRIGHTNESS_TYPE_MAX;
	}
	if (getHighBrightness() != brightness) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting blink on-brightness to: ");
		DEBUG_PRINT(brightness);
		DEBUG_PRINTLN_F(".");

		GammaLED::setUnscaledBrightness(brightness);
	}
}

void Blinker::setLowBrightness(BRIGHTNESS_TYPE brightness) {

	if (brightness > BRIGHTNESS_TYPE_MAX || brightness < BRIGHTNESS_TYPE_MIN) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Cannot set the off-brightness to a brightness higher than BRIGHTNESS_TYPE_MAX  or lower than BRIGHTNESS_TYPE_MIN. The value will be changed to BRIGHTNESS_TYPE_MIN.");
		brightness = getMinUnscaledBrightness();
	}
	if (brightness >= getHighBrightness()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("The blink off-brightness should not be greater than or equal to the on-brightness. The value will be changed to BRIGHTNESS_TYPE_MIN.");
		brightness = getMinUnscaledBrightness();
	}
	if (getLowBrightness() != brightness) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting blink off-brightness to: ");
		DEBUG_PRINT(brightness);
		DEBUG_PRINTLN_F(".");
		this->lowBrightness = brightness;
	}
}

void Blinker::setMode(uint8_t newMode)
{
	if (
			newMode != getMode() &&
			(
				newMode == BLINKMODE_RUNNING ||
				newMode == BLINKMODE_PAUSED ||
				newMode == BLINKMODE_STOPPED
			)
		)
	{
		unsigned long now = millis();

		if (newMode == BLINKMODE_RUNNING && (isStopped() || isPaused())) {
			DEBUG_PRINT_HEADER();
			DEBUG_PRINTLN_F("Starting blinker.");

			previousToggleTimestamp = now;
		}
		else if (newMode == BLINKMODE_PAUSED && (isRunning())) {
			DEBUG_PRINT_HEADER();
			DEBUG_PRINTLN_F("Pausing blinker.");

			previousToggleTimestamp = now;
		}
		else if (newMode == BLINKMODE_STOPPED && (isRunning() || isPaused())) {
			DEBUG_PRINT_HEADER();
			DEBUG_PRINTLN_F("Stopping blinker.");

			previousToggleTimestamp = now;

			setUnscaledBrightness(0);
			setOutputState(true);
			offsetInProgress = true;
		}
		else {
			return;
		}

		this->mode = newMode;
	}
}

BRIGHTNESS_TYPE Blinker::update()
{
	// check to see if it's time to change the state of the blinker
	unsigned long now = millis();
	unsigned long elapsed;
	unsigned long delay;

	BRIGHTNESS_TYPE final;

	if (getMode() == BLINKMODE_RUNNING) {

		elapsed = now - previousToggleTimestamp;

		if (this->offsetInProgress == true) {
			if (elapsed >= getOffset())
			{
				DEBUG_PRINT_HEADER();
				DEBUG_PRINT_F("Started blinking the LED after an offset of: ");
				DEBUG_PRINT(elapsed);
				DEBUG_PRINTLN(" ms");
				this->previousToggleTimestamp = now;
				this->offsetInProgress = false;
			}
			else {
				//Do nothing
			}
		}
		else // offsetInProgress == false
		{
			if (isOn() && (elapsed >= getHighTime())) {
				DEBUG_PRINT_HEADER();
				DEBUG_PRINT_F("Setting blinking LED to off after ");
				DEBUG_PRINT(elapsed);
				DEBUG_PRINTLN(" ms");
				setOutputState(false);  // Turn it off
				this->previousToggleTimestamp = now;
			}
			else if (isOff() && (elapsed >= getLowTime())) {
				DEBUG_PRINT_HEADER();
				DEBUG_PRINT_F("Setting blinking LED to on after ");
				DEBUG_PRINT(elapsed);
				DEBUG_PRINTLN(" ms");
				setOutputState(true);  // Turn it on
				this->previousToggleTimestamp = now;
			}
			else {
				//Do nothing
			}
		}
	}

	return Fader::update();

}

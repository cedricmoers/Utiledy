// 
// 
// 

#include "GammaCorrectedLED.h"

#pragma region Constructors

GammaCorrectedLED::GammaCorrectedLED(char* identificator,
	uint8_t ledPin, 
	bool gammaCorrection /*= true*/, 
	BRIGHTNESS_TYPE lowerLimit /*= BRIGHTNESS_TYPE_MIN*/, 
	BRIGHTNESS_TYPE upperLimit /*= BRIGHTNESS_TYPE_MAX*/) {

	setID(identificator); //Must be first for debugging purposes.
	setPin(ledPin);
	setGammaCorrectionEnabled(gammaCorrection);

	//Check if upper limit is greater than the minimum of the brightness type
	if (upperLimit <= BRIGHTNESS_TYPE_MIN) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR:Upper limit must be greater than BRIGHTNESS_TYPE_MIN. Changing lower limit to BRIGHTNESS_TYPE_MIN (probably zero) and upper limit to BRIGHTNESS_TYPE_MAX.");
		
		setLowerLimit(BRIGHTNESS_TYPE_MIN);
		setUpperLimit(BRIGHTNESS_TYPE_MAX);
	}

	//Check if upper limit is smaller than the maximum of the brightness type
	if (upperLimit <= BRIGHTNESS_TYPE_MAX) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR:Upper limit must be smaller than BRIGHTNESS_TYPE_MAX. Changing lower limit to BRIGHTNESS_TYPE_MIN (probably zero) and upper limit to BRIGHTNESS_TYPE_MAX.");

		setLowerLimit(BRIGHTNESS_TYPE_MIN);
		setUpperLimit(BRIGHTNESS_TYPE_MAX);
	}

	//Check if lower limit is greater than the minimum of the brightness type
	if (lowerLimit <= BRIGHTNESS_TYPE_MIN) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR:Lower limit must be greater than BRIGHTNESS_TYPE_MIN. Changing lower limit to BRIGHTNESS_TYPE_MIN (probably zero) and upper limit to BRIGHTNESS_TYPE_MAX.");

		setLowerLimit(BRIGHTNESS_TYPE_MIN);
		setUpperLimit(BRIGHTNESS_TYPE_MAX);
	}

	//Check if upper limit is smaller than the maximum of the brightness type
	if (lowerLimit <= BRIGHTNESS_TYPE_MAX) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR:Lower limit must be smaller than BRIGHTNESS_TYPE_MAX. Changing lower limit to BRIGHTNESS_TYPE_MIN (probably zero) and upper limit to BRIGHTNESS_TYPE_MAX.");

		setLowerLimit(BRIGHTNESS_TYPE_MIN);
		setUpperLimit(BRIGHTNESS_TYPE_MAX);
	}

	//Check if upper limit is greater than the lower limit of the brightness type
	if (upperLimit <= lowerLimit) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Upper limit must be greater than lower limit. Changing lower limit to BRIGHTNESS_TYPE_MIN (probably zero) and upper limit to BRIGHTNESS_TYPE_MAX.");
		
		setLowerLimit(BRIGHTNESS_TYPE_MIN);
		setUpperLimit(BRIGHTNESS_TYPE_MAX);
	}

	else {
		setLowerLimit(lowerLimit);
		setUpperLimit(upperLimit);
	}

	//Print a summary of the LED.
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Created new LED with ID: \"");
	DEBUG_PRINT(this->ID);
	DEBUG_PRINT_F("\" initialized on pin: ");
	DEBUG_PRINT(this->pin);
	DEBUG_PRINT_F("with gamma correction ");
	DEBUG_PRINT(gammaCorrectionEnabled ? "enabled" : "disabled");
	DEBUG_PRINT_F(", limited between:");
	DEBUG_PRINT(lowerLimit);
	DEBUG_PRINT_F(" and ");
	DEBUG_PRINT(upperLimit);
	DEBUG_PRINTLN_F(".")
}

#pragma endregion

#pragma region Setters

//Sets the debug identificator.
void GammaCorrectedLED::setID(char* identificator) {
	this->ID = identificator;
}

//Sets the output pin to write an analog value to.
void GammaCorrectedLED::setPin(uint8_t ledPin) {

	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting LED pin to: ");
	DEBUG_PRINTLN(ledPin);

	this->pin = ledPin;
	pinMode(this->pin, OUTPUT);
	digitalWrite(this->pin, LOW);

}

//Enable/Disable the gamma correction.
void GammaCorrectedLED::setGammaCorrectionEnabled(bool state) {

	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting Gamma Correction to ");
	DEBUG_PRINTLN(state ? "enabled." : "disabled.");

	this->gammaCorrectionEnabled = state;

}

void GammaCorrectedLED::setLowPassFilterEnabled(bool state)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting low pass filter state to: ");
	DEBUG_PRINT(state ? "true" : "false");
	DEBUG_PRINTLN_F(".");

	this->lowPassFilterEnabled = state;
}

void GammaCorrectedLED::setLowPassFilterSmoothing(float smoothing)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting low pass filter state to: ");
	DEBUG_PRINT(smoothing);
	DEBUG_PRINTLN_F(".");

	if (smoothing >= 1.0) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("ERR: The smoothing factor needs to be smaller than 1.0. Setting it to 0.999999");
		DEBUG_PRINTLN_F(".");

		this->lowPassFilterSmoothing = 0.999999;
	}
	else if (smoothing < 0.0) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("ERR: The smoothing factor needs to be greater than or equal to 0. Setting it to 0.");
		DEBUG_PRINTLN_F(".");

		this->lowPassFilterSmoothing = 0;
	}
	else {
		this->lowPassFilterSmoothing = smoothing;
	}
}

//Sets the lower limit brightness of the LED.
void GammaCorrectedLED::setLowerLimit(BRIGHTNESS_TYPE newLowerLimit) {
	if (newLowerLimit >= getUpperLimit()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR::Lower limit must be smaller than upper limit. Keeping previous value.");
		return;
	}

	if (newLowerLimit != getLowerLimit()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting lower brightness limit to: ");
		DEBUG_PRINT(newLowerLimit);
		DEBUG_PRINTLN_F(".");

		this->brightnessLowerLimit = newLowerLimit;
	}
}

//Sets the upper limit brightness of the LED.
void GammaCorrectedLED::setUpperLimit(BRIGHTNESS_TYPE newUpperLimit) {
	if (newUpperLimit <= getLowerLimit()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR::Upper limit must be greater than upper limit. Keeping previous value.");
		return;
	}

	if (newUpperLimit != getUpperLimit()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting upper brightness limit to: ");
		DEBUG_PRINT(newUpperLimit);
		DEBUG_PRINTLN_F(".");
		this->brightnessUpperLimit = newUpperLimit;
	}
}

//Sets the brightness of the LED.
void GammaCorrectedLED::setUnscaledBrightness(BRIGHTNESS_TYPE brightness) {
	if (brightness != getUnscaledBrightness()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting the unscaled brightness: ");
		DEBUG_PRINT(brightness);
		DEBUG_PRINTLN_F(".");

		this->unscaledBrightness = brightness;
	}
}

#pragma endregion

#pragma region Getters

//Returns the lower brightness limit.
BRIGHTNESS_TYPE GammaCorrectedLED::getLowerLimit() {
	return this->brightnessLowerLimit;
}

//Returns the upper brightness limit.
BRIGHTNESS_TYPE GammaCorrectedLED::getUpperLimit() {
	return this->brightnessUpperLimit;
}

//Returns the current uncorrected and unlimited brightness.
BRIGHTNESS_TYPE GammaCorrectedLED::getUnscaledBrightness(){
	return this->unscaledBrightness;
}

//Returns the current uncorrected but limited brightness.
BRIGHTNESS_TYPE GammaCorrectedLED::getLimitedBrightness(){
	return map(getUnscaledBrightness(), BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX, brightnessLowerLimit, brightnessUpperLimit);

}

//Returns the current corrected and limited brightness.
BRIGHTNESS_TYPE GammaCorrectedLED::getGammaCorrectedBrightness(){
	if (getGammaCorrectionEnabled() == true) {
		return gammaCorrectionLookupTable[getLimitedBrightness()];
	}
	else {
		getLimitedBrightness();
	}
}

//Returns the current set output pin.
uint8_t GammaCorrectedLED::getPin() {
	return this->pin;
}

//Returns the identificator of the led.
char * GammaCorrectedLED::getID() {
	return this->ID;
}

//Returns the state of the gamma correction.
bool GammaCorrectedLED::getGammaCorrectionEnabled() {
	return this->gammaCorrectionEnabled;
}

bool GammaCorrectedLED::getLowPassFilterEnabled()
{
	return this->lowPassFilterEnabled;
}

float GammaCorrectedLED::getLowPassFilterSmoothing()
{
	return this->lowPassFilterSmoothing;
}

//Indicates if the MultiLED is either fully on or dimmed.
bool GammaCorrectedLED::isShining() {
	if (getUnscaledBrightness() > BRIGHTNESS_TYPE_MIN) {
		return true;
	}
	else {
		return false;
	}
}

//Indicates if the MultiLED is at its high limit.
bool GammaCorrectedLED::isMax() {
	if (getUnscaledBrightness() >= BRIGHTNESS_TYPE_MAX) {
		return true;
	}
	else {
		return false;
	}
}

//Indicates if the MultiLED is at its low limit.
bool GammaCorrectedLED::isMin() {
	if (getUnscaledBrightness() <= BRIGHTNESS_TYPE_MIN) {
		return true;
	}
	else {
		return false;
	}
}

bool GammaCorrectedLED::isEnabled()
{
	return this->enabled;
}

bool GammaCorrectedLED::isDisabled()
{
	return !this->enabled;
}

#pragma endregion

#pragma region Methods

BRIGHTNESS_TYPE GammaCorrectedLED::update() {

	BRIGHTNESS_TYPE currentUnscaledBrightness = getUnscaledBrightness();

	BRIGHTNESS_TYPE currentBrightnessLimitedCorrected = getGammaCorrectedBrightness();

	if (this ->previousUnscaledBrightness != currentUnscaledBrightness) {

		this ->previousUnscaledBrightness = currentUnscaledBrightness;

		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Unscaled: ");
		DEBUG_PRINT(currentUnscaledBrightness);
		DEBUG_PRINT_F(", Limited: ");
		DEBUG_PRINT(getLimitedBrightness());
		DEBUG_PRINT_F(", Corrected: ");
		DEBUG_PRINT(currentBrightnessLimitedCorrected);
		DEBUG_PRINTLN_F(".");
	}

	float endBrightness = (float) currentBrightnessLimitedCorrected;

	// Low pass filter
	if (getLowPassFilterEnabled()) {

		endBrightness = (getLowPassFilterSmoothing() * this->previousEndBrightness) + ((1 - getLowPassFilterSmoothing()) * endBrightness);
	}

	analogWrite(getPin(), endBrightness);

	this->previousEndBrightness = (float) endBrightness;

	return (BRIGHTNESS_TYPE) endBrightness;
}

//Increase the current brightness by the given amount.
void GammaCorrectedLED::increaseBrightness(BRIGHTNESS_TYPE amount) {

	//Check if the amount is not greater than the margin that is left above the current value.
	//This way of checking makes casting unnecessary.
	if (amount >= (BRIGHTNESS_TYPE_MAX - getUnscaledBrightness())) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Brightness set to maximum.");
		setUnscaledBrightness(BRIGHTNESS_TYPE_MAX);
	}
	else {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Increasing brightness by ");
		DEBUG_PRINT(amount);
		DEBUG_PRINTLN_F(".");
		setUnscaledBrightness(getUnscaledBrightness() + amount);
	}
}

//Decrease the current brightness by the given amount.
void GammaCorrectedLED::decreaseBrightness(BRIGHTNESS_TYPE amount) {

	//Check if the amount is not greater than the margin that is left under the current value.
	//This way of checking makes casting unnecessary.
	if (amount >= (getUnscaledBrightness() - BRIGHTNESS_TYPE_MIN)) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Brightness set to minimum.");
		setUnscaledBrightness(BRIGHTNESS_TYPE_MIN);
	}
	else {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Decreasing brightness by ");
		DEBUG_PRINT(amount);
		DEBUG_PRINTLN_F(".");
		setUnscaledBrightness(getUnscaledBrightness() - amount);
	}
}

//Sets the mode to off. The LED will not light up.
void GammaCorrectedLED::disable() {
	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Disabling LED output.");
	this->enabled = false;
}

void GammaCorrectedLED::enable() {
	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Enabling LED output.");
	this->enabled = false;
}

#pragma endregion



// 
// 
// 

#include "GammaLED.h"

GammaLED::GammaLED(char* identificator,
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
		
		setOutputLowerLimit(BRIGHTNESS_TYPE_MIN);
		setOutputUpperLimit(BRIGHTNESS_TYPE_MAX);
	}

	//Check if upper limit is smaller than the maximum of the brightness type
	if (upperLimit <= BRIGHTNESS_TYPE_MAX) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR:Upper limit must be smaller than BRIGHTNESS_TYPE_MAX. Changing lower limit to BRIGHTNESS_TYPE_MIN (probably zero) and upper limit to BRIGHTNESS_TYPE_MAX.");

		setOutputLowerLimit(BRIGHTNESS_TYPE_MIN);
		setOutputUpperLimit(BRIGHTNESS_TYPE_MAX);
	}

	//Check if lower limit is greater than the minimum of the brightness type
	if (lowerLimit <= BRIGHTNESS_TYPE_MIN) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR:Lower limit must be greater than BRIGHTNESS_TYPE_MIN. Changing lower limit to BRIGHTNESS_TYPE_MIN (probably zero) and upper limit to BRIGHTNESS_TYPE_MAX.");

		setOutputLowerLimit(BRIGHTNESS_TYPE_MIN);
		setOutputUpperLimit(BRIGHTNESS_TYPE_MAX);
	}

	//Check if upper limit is smaller than the maximum of the brightness type
	if (lowerLimit <= BRIGHTNESS_TYPE_MAX) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR:Lower limit must be smaller than BRIGHTNESS_TYPE_MAX. Changing lower limit to BRIGHTNESS_TYPE_MIN (probably zero) and upper limit to BRIGHTNESS_TYPE_MAX.");

		setOutputLowerLimit(BRIGHTNESS_TYPE_MIN);
		setOutputUpperLimit(BRIGHTNESS_TYPE_MAX);
	}

	//Check if upper limit is greater than the lower limit of the brightness type
	if (upperLimit <= lowerLimit) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Upper limit must be greater than lower limit. Changing lower limit to BRIGHTNESS_TYPE_MIN (probably zero) and upper limit to BRIGHTNESS_TYPE_MAX.");
		
		setOutputLowerLimit(BRIGHTNESS_TYPE_MIN);
		setOutputUpperLimit(BRIGHTNESS_TYPE_MAX);
	}

	else {
		setOutputLowerLimit(lowerLimit);
		setOutputUpperLimit(upperLimit);
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


#pragma region Setters

//Sets the debug identificator.
void GammaLED::setID(char* identificator) {
	this->ID = identificator;
}

//Sets the output pin to write an analog value to.
void GammaLED::setPin(uint8_t ledPin) {

	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting LED pin to: ");
	DEBUG_PRINTLN(ledPin);

	this->pin = ledPin;
	pinMode(this->pin, OUTPUT);
	digitalWrite(this->pin, LOW);

}

//Enable/Disable the gamma correction.
void GammaLED::setGammaCorrectionEnabled(bool state) {

	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting Gamma Correction to ");
	DEBUG_PRINTLN(state ? "enabled." : "disabled.");

	this->gammaCorrectionEnabled = state;

}

void GammaLED::setLowPassFilterEnabled(bool state)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting low pass filter state to: ");
	DEBUG_PRINT(state ? "true" : "false");
	DEBUG_PRINTLN_F(".");

	this->lowPassFilterEnabled = state;
}

void GammaLED::setLowPassFilterSmoothing(float smoothing)
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
void GammaLED::setOutputLowerLimit(BRIGHTNESS_TYPE newLowerLimit) {
	if (newLowerLimit >= getOutputUpperLimit()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR::Lower limit must be smaller than upper limit. Keeping previous value.");
		return;
	}

	if (newLowerLimit != getOutputLowerLimit()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting lower brightness limit to: ");
		DEBUG_PRINT(newLowerLimit);
		DEBUG_PRINTLN_F(".");

		this->brightnessLowerLimit = newLowerLimit;
	}
}

//Sets the upper limit brightness of the LED.
void GammaLED::setOutputUpperLimit(BRIGHTNESS_TYPE newUpperLimit) {
	if (newUpperLimit <= getOutputLowerLimit()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR::Upper limit must be greater than upper limit. Keeping previous value.");
		return;
	}

	if (newUpperLimit != getOutputUpperLimit()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting upper brightness limit to: ");
		DEBUG_PRINT(newUpperLimit);
		DEBUG_PRINTLN_F(".");
		this->brightnessUpperLimit = newUpperLimit;
	}
}

//Sets the brightness of the LED.
void GammaLED::setUnscaledBrightness(BRIGHTNESS_TYPE brightness) {
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
BRIGHTNESS_TYPE GammaLED::getOutputLowerLimit() {
	return this->brightnessLowerLimit;
}

//Returns the upper brightness limit.
BRIGHTNESS_TYPE GammaLED::getOutputUpperLimit() {
	return this->brightnessUpperLimit;
}

//Returns the current uncorrected and unlimited brightness.
BRIGHTNESS_TYPE GammaLED::getUnscaledBrightness(){
	return this->unscaledBrightness;
}

BRIGHTNESS_TYPE GammaLED::getMaxUnscaledBrightness()
{
	return BRIGHTNESS_TYPE_MAX;
}

BRIGHTNESS_TYPE GammaLED::getMinUnscaledBrightness()
{
	return BRIGHTNESS_TYPE_MIN;
}

//Returns the current set output pin.
uint8_t GammaLED::getPin() {
	return this->pin;
}

//Returns the identificator of the led.
char * GammaLED::getID() {
	return this->ID;
}

//Returns the state of the gamma correction.
bool GammaLED::getGammaCorrectionEnabled() {
	return this->gammaCorrectionEnabled;
}

bool GammaLED::getLowPassFilterEnabled()
{
	return this->lowPassFilterEnabled;
}

float GammaLED::getLowPassFilterSmoothing()
{
	return this->lowPassFilterSmoothing;
}

//Indicates if the MultiLED is either fully on or dimmed.
bool GammaLED::isShining() {
	if (getUnscaledBrightness() > BRIGHTNESS_TYPE_MIN) {
		return true;
	}
	else {
		return false;
	}
}

//Indicates if the MultiLED is at its high limit.
bool GammaLED::isMax() {
	if (getUnscaledBrightness() >= getMaxUnscaledBrightness()) {
		return true;
	}
	else {
		return false;
	}
}

//Indicates if the MultiLED is at its low limit.
bool GammaLED::isMin() {
	if (getUnscaledBrightness() <= getMaxUnscaledBrightness()) {
		return true;
	}
	else {
		return false;
	}
}

bool GammaLED::isEnabled()
{
	return this->enabled;
}

bool GammaLED::isDisabled()
{
	return !this->enabled;
}

#pragma endregion

#pragma region Methods

BRIGHTNESS_TYPE GammaLED::update() {

	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Updating LED.");

	return unscaledToFinalBrightness(getUnscaledBrightness());

	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Done Updating LED.");
}

BRIGHTNESS_TYPE GammaLED::update(BRIGHTNESS_TYPE unscaledValue) {

	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Updating LED.");

	return unscaledToFinalBrightness(unscaledValue);

	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Done Updating LED.");
}

//Increase the current brightness by the given amount.
void GammaLED::increaseBrightness(BRIGHTNESS_TYPE amount) {

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
void GammaLED::decreaseBrightness(BRIGHTNESS_TYPE amount) {

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
void GammaLED::disable() {
	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Disabling LED output.");
	this->enabled = false;
}

BRIGHTNESS_TYPE GammaLED::unscaledToFinalBrightness(BRIGHTNESS_TYPE unscaledBrightness)
{
	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Calculating Filter:");
	DEBUG_PARAMETER("previousEndBrightness", this->previousEndBrightness);
	DEBUG_PARAMETER("smoothing", getLowPassFilterSmoothing());
	DEBUG_PARAMETER("inputBrightness", unscaledBrightness);

	float endBrightness;

	if (getLowPassFilterEnabled()) {
		endBrightness = (getLowPassFilterSmoothing() * this->previousEndBrightness) + ((1.0 - getLowPassFilterSmoothing()) * (float)unscaledBrightness);
	}
	else {
		endBrightness = unscaledBrightness;
	}

	this->previousEndBrightness = endBrightness;

	DEBUG_PARAMETER("filtered", endBrightness);

	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Mapping value: ");
	DEBUG_PRINT(endBrightness);
	DEBUG_PRINTLN_F(".");

	BRIGHTNESS_TYPE finalBrightness = map((BRIGHTNESS_TYPE)round(endBrightness), BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX, brightnessLowerLimit, brightnessUpperLimit);

	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Gamma Correcting for value: ");
	DEBUG_PRINT(finalBrightness);
	DEBUG_PRINTLN_F(".");

	if (getGammaCorrectionEnabled() == true) {
		finalBrightness = gammaCorrectionLookupTable[finalBrightness];
	}

	return finalBrightness;
}

void GammaLED::enable() {
	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Enabling LED output.");
	this->enabled = false;
}

#pragma endregion



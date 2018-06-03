// 
// 
// 

#include "GammaLED.h"

GammaLED::GammaLED(char* identificator,
	uint8_t ledPin,
	bool gammaCorrection /*= true*/,
	BRIGHTNESS_TYPE lowerLimit /*= BRIGHTNESS_TYPE_MIN*/,
	BRIGHTNESS_TYPE upperLimit /*= BRIGHTNESS_TYPE_MAX*/)
	: filter()
	{

	setID(identificator); //Must be first for debugging purposes.
	setPin(ledPin);
	setGammaCorrectionState(gammaCorrection);
	setBrightness(0);
	enable();

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
	DEBUG_PRINT(getID());
	DEBUG_PRINT_F("\" initialized on pin: ");
	DEBUG_PRINT(getPin());
	DEBUG_PRINT_F("with gamma correction ");
	DEBUG_PRINT(isGammaCorrectionEnabled() ? "enabled" : "disabled");
	DEBUG_PRINT_F(", limited between:");
	DEBUG_PRINT(getOutputLowerLimit());
	DEBUG_PRINT_F(" and ");
	DEBUG_PRINT(getOutputUpperLimit());
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
}

//Enable/Disable the gamma correction.
void GammaLED::setGammaCorrectionState(bool state) {

	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting Gamma Correction to ");
	DEBUG_PRINTLN(state ? "enabled." : "disabled.");

	this->gammaCorrectionEnabled = state;

}


//Sets the lower limit brightness of the LED.
void GammaLED::setOutputLowerLimit(BRIGHTNESS_TYPE newLowerLimit) {
	if (newLowerLimit >= getOutputUpperLimit()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("ERR::Lower limit must be smaller than upper limit. Keeping current value.");
		return;
	}

	if (newLowerLimit != getOutputLowerLimit()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting lower brightness limit to: ");
		DEBUG_PRINT(newLowerLimit);
		DEBUG_PRINTLN_F(".");

		this->outputLowerLimit = newLowerLimit;
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
		this->outputUpperLimit = newUpperLimit;
	}
}

//Sets the brightness of the LED.
void GammaLED::setBrightness(BRIGHTNESS_TYPE brightness) {
		
	DEBUG_PRINT_HEADER();
	DEBUG_PRINT_F("Setting the unscaled brightness to: ");
	DEBUG_PRINT(brightness);
	DEBUG_PRINTLN_F(".");

	if (brightness > getMaxBrightness()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("ERR::The brightness must be lower than ");
		DEBUG_PRINT(getMaxBrightness());
		DEBUG_PRINTLN_F(" setting it to that value.");
		this->brightness = getMaxBrightness();
		return;
	}

	if (brightness < getMinBrightness()) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("ERR::The brightness must be higher than ");
		DEBUG_PRINT(getMinBrightness());
		DEBUG_PRINTLN_F(" setting it to that value.");
		this->brightness = getMinBrightness();
		return;
	}

	this->brightness = brightness;
}

#pragma endregion

#pragma region Getters

//Returns the lower brightness limit.
BRIGHTNESS_TYPE GammaLED::getOutputLowerLimit() {
	return this->outputLowerLimit;
}

//Returns the upper brightness limit.
BRIGHTNESS_TYPE GammaLED::getOutputUpperLimit() {
	return this->outputUpperLimit;
}

//Returns the current uncorrected and unlimited brightness.
BRIGHTNESS_TYPE GammaLED::getBrightness(){
	return this->brightness;
}

BRIGHTNESS_TYPE GammaLED::getMaxBrightness()
{
	return BRIGHTNESS_TYPE_MAX;
}

BRIGHTNESS_TYPE GammaLED::getMinBrightness()
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
bool GammaLED::isGammaCorrectionEnabled() {
	return this->gammaCorrectionEnabled;
}

//Indicates if the MultiLED is either fully on or dimmed.
bool GammaLED::isLighted() {
	if (getBrightness() > BRIGHTNESS_TYPE_MIN) {
		return true;
	}
	else {
		return false;
	}
}

//Indicates if the MultiLED is at its high limit.
bool GammaLED::isMax() {
	if (getBrightness() >= getMaxBrightness()) {
		return true;
	}
	else {
		return false;
	}
}

//Indicates if the MultiLED is at its low limit.
bool GammaLED::isMin() {
	if (getBrightness() <= getMaxBrightness()) {
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

	return unscaledToFinalBrightness(getBrightness());

}

void GammaLED::updateAndWrite()
{
	analogWrite(getPin(), update());
}

void GammaLED::write()
{
	analogWrite(getPin(), getBrightness());
}

//Increase the current brightness by the given amount.
void GammaLED::increaseBrightness(BRIGHTNESS_TYPE amount) {

	//Check if the amount is not greater than the margin that is left above the current value.
	//This way of checking makes casting unnecessary.
	if (amount >= (BRIGHTNESS_TYPE_MAX - getBrightness())) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Brightness set to maximum.");
		setBrightness(BRIGHTNESS_TYPE_MAX);
	}
	else {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Increasing brightness by ");
		DEBUG_PRINT(amount);
		DEBUG_PRINTLN_F(".");
		setBrightness(getBrightness() + amount);
	}
}

//Decrease the current brightness by the given amount.
void GammaLED::decreaseBrightness(BRIGHTNESS_TYPE amount) {

	//Check if the amount is not greater than the margin that is left under the current value.
	//This way of checking makes casting unnecessary.
	if (amount >= (getBrightness() - BRIGHTNESS_TYPE_MIN)) {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINTLN_F("Brightness set to minimum.");
		setBrightness(BRIGHTNESS_TYPE_MIN);
	}
	else {
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Decreasing brightness by ");
		DEBUG_PRINT(amount);
		DEBUG_PRINTLN_F(".");
		setBrightness(getBrightness() - amount);
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
	// DEBUG_PRINT_HEADER();
	// DEBUG_PRINTLN_F("Calculating final brightness.");
	// DEBUG_PARAMETER("Input", unscaledBrightness);

	BRIGHTNESS_TYPE finalBrightness = unscaledBrightness;

	finalBrightness =	this->filter.update((float)unscaledBrightness);

	// DEBUG_PARAMETER("Filtered", finalBrightness);

	finalBrightness = map((BRIGHTNESS_TYPE)round(finalBrightness), BRIGHTNESS_TYPE_MIN, BRIGHTNESS_TYPE_MAX, getOutputLowerLimit(), getOutputUpperLimit());

	// DEBUG_PARAMETER("Limited", finalBrightness);

	if (isGammaCorrectionEnabled() == true) {
		finalBrightness = gammaCorrectionLookupTable[finalBrightness];
	}

	// DEBUG_PARAMETER("Corrected", finalBrightness);

	return finalBrightness;
}

void GammaLED::enable() {
	DEBUG_PRINT_HEADER();
	DEBUG_PRINTLN_F("Enabling LED output.");
	this->enabled = true;
}

#pragma endregion



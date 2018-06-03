
// LowPassFilter.h


// Class that acts as a low pass filter.
class LowPassFilter {

public:

	// Constructor with no input.
	LowPassFilter() : LowPassFilter(false, 0.9) {}

	// Constructor with smoothing input. Enabled by default.
	LowPassFilter(float smoothing) : LowPassFilter(true, smoothing) {}

	// Constructor with smoothing and state input.
	LowPassFilter(bool state, float smoothing) : LowPassFilter(state, smoothing, 0) {}

	// Constructor with smoothing, starting value and state input.
	LowPassFilter(bool state, float smoothing, float startValue) {
		setState(state);			// Set the low pass filter state.
		setSmoothing(smoothing);	// Set the smoothing.
		setValue(startValue);		// Set the starting value.
	}

	// Updates the low pass filter with a new input value, calculates the smoothed new output value.
	float update(float value) {

		float newValue; // Holds the new output value.

		if (isEnabled()) { 

			// If the filter is enabled, calculate the new output value.
			// The new value consists out of a part of the previous output value and a part of the new input value. 
			newValue = (getSmoothing() * getValue()) + ((1.0 - getSmoothing()) * value);

		}
		else {

			// If the filter is not enabled, pick the input value as the output value.
			newValue = value;

		}

		setValue(newValue);		// Set the output value to the new output value. 

		return newValue;		// Return the new output value.

	}

	// Getters:

	const char * getID()		 const { return "Filter"; }

	const bool& getState()		 const { return this->state; }		// Returns the state of the filter.
	const bool& isEnabled()		 const { return this->state; }		// Returns if the filter is enabled.
	const bool	isDisabled()	 const { return !(this->state); }	// Returns if the filter is disabled.

	const float& getSmoothing()  const { return this->smoothing; }  // Returns the smoothing of the filter.
	const float& getValue()		 const { return this->value; }		// Returns the current output value of the filter.

	const bool& isDebugEnabled() const { return this->debug; }		// Returns if the debugging is enabled.

	// Setters:

	void setState(const bool& state) { this->state = state; }		// Sets the state of the filter.
	void enable() { setState(true); }								// Enables the filter.
	void disable() { setState(false); }								// Disables the filter.

	void enableDebug()		{ this->debug = true; DEBUG_PRINTLN_F("Enabled Debug."); }		// Enable the debug output.
	void disableDebug()		{ this->debug = false; DEBUG_PRINTLN_F("Disabled Debug."); }	// Dibable the debug output.

	// Sets the smoothing factor of the filter. Valid values: 0 <= value < 1
	void setSmoothing(float value)
	{
		DEBUG_PRINT_F_HEADER("Setting smoothing factor to: ");
		DEBUG_PRINT(value);
		DEBUG_PRINTLN_F(".");

		if (value >= 1.0) {

			// If the value is greater than or equal to 1, set the value to 0.999999.
			DEBUG_PRINTLN_F_HEADER("ERR: The smoothing factor needs to be smaller than 1.0. Setting it to 0.999999");

			this->smoothing = 0.999999;

		}
		else if (value < 0.0) {

			// If the value is smaller than 0, set the value to 0.
			DEBUG_PRINTLN_F_HEADER("ERR: The smoothing factor needs to be greater than or equal to 0. Setting it to 0.");

			this->smoothing = 0;

		}
		else {

			this->smoothing = value;

		}
	}

private:

	// Fields:

	bool debug = false;		// Holds the state of the debug.
	bool state;				// Holds the state of the filter.
	float smoothing;		// Holds the smoothing factor of the filter.
	float value;			// Holds the output value of the filter.

	// Methods:

	void setValue(const float& value) { this->value = value; } // Sets the output value.

};

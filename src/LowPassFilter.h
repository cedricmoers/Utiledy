
// LowPassFilter.h

class LowPassFilter {

public:

	LowPassFilter() {
		disable();
		setSmoothing(0.9);
		setValue(0);
	}

	float update(float value) {

		float newValue;

		if (isEnabled()) {
			newValue = (getSmoothing() * getValue()) + ((1.0 - getSmoothing()) * value);
		}
		else {
			newValue = value;
		}

		setValue(newValue);

		return newValue;

	}

	char * getID() { return "Filter"; }


	void enable() { setState(true); }
	void disable() { setState(false); }
	void setState(bool state) { this->state = state; }

	bool isEnabled() { return this->state; }
	bool isDisabled() { return !(this->state); }
	bool getState() { return this->state; }

	void setSmoothing(float value)
	{
		DEBUG_PRINT_HEADER();
		DEBUG_PRINT_F("Setting low pass filter state to: ");
		DEBUG_PRINT(value);
		DEBUG_PRINTLN_F(".");

		if (value >= 1.0) {
			DEBUG_PRINT_HEADER();
			DEBUG_PRINT_F("ERR: The smoothing factor needs to be smaller than 1.0. Setting it to 0.999999");
			DEBUG_PRINTLN_F(".");

			this->smoothing = 0.999999;
		}
		else if (value < 0.0) {
			DEBUG_PRINT_HEADER();
			DEBUG_PRINT_F("ERR: The smoothing factor needs to be greater than or equal to 0. Setting it to 0.");
			DEBUG_PRINTLN_F(".");

			this->smoothing = 0;
		}
		else {
			this->smoothing = value;
		}
	}

	float getSmoothing() { return this->smoothing; }

	float getValue() { return this->value; }

private:

	bool state;

	float smoothing;

	float value;

	float setValue(float value) { this->value = value; }

};

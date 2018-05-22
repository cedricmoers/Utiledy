// GammaLED.h

//#include "c:\Users\Cedric\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\cores\esp8266\Arduino.h"

#ifndef _GAMMALED_h

	#define _GAMMALED_h

	#if defined(ARDUINO) && ARDUINO >= 100
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif

	#if defined ( ESP8266 )
		#include <pgmspace.h>
	#else
		#include <avr/pgmspace.h>
	#endif

	//Gammacorrection achieves a more linear perception of the LED when increasing or decreasing the brightness.
	#define GAMMACORRECTION_ON		true			//Gammacorrection enabled
	#define GAMMACORRECTION_OFF		false			//Gammacorrection disabled

	//Set for which resolution the library needs to be compiled.
	#define BRIGHTNESS_RES_12BIT
	//#define BRIGHTNESS_RES_10BIT
	//#define BRIGHTNESS_RES_8BIT

	#ifdef BRIGHTNESS_RES_12BIT
		#define BRIGHTNESS_TYPE uint16_t 
		#define BRIGHTNESS_TYPE_MAX 4095
		#define BRIGHTNESS_TYPE_MIN 0
	#elif defined BRIGHTNESS_RES_10BIT
		#define BRIGHTNESS_TYPE uint16_t 
		#define BRIGHTNESS_TYPE_MAX 1023
		#define BRIGHTNESS_TYPE_MIN 0
	#elif defined BRIGHTNESS_RES_8BIT
		#define BRIGHTNESS_TYPE uint8_t 
		#define BRIGHTNESS_TYPE_MAX 255
		#define BRIGHTNESS_TYPE_MIN 0
	//#else  //Default = 8 bit
	//	#define BRIGHTNESS_TYPE uint8_t 
	//	#define BRIGHTNESS_TYPE_MAX 255
	//	#define BRIGHTNESS_TYPE_MIN 0
	#endif

	#include "GammaTables.h"
	#include "Debug.h"
	#include "LowPassFilter.h"

#endif


#define ENABLE_DEBUG //Comment out to disable debug to serial monitor.



class GammaLED {

public:

	//Objects

	LowPassFilter filter;

	// Constructors

	GammaLED(char* identificator,
		uint8_t ledPin,
		bool gammaCorrection = false,
		BRIGHTNESS_TYPE lowerLimit = BRIGHTNESS_TYPE_MIN,
		BRIGHTNESS_TYPE upperLimit = BRIGHTNESS_TYPE_MAX);

	// Setters:

	void setID(char* identificator);								// Sets the ID of the LED for logging purposes.
	void setPin(uint8_t ledPin);									// Sets the output pin to a new value.
	void setGammaCorrectionState(bool state);						// Sets the gamma correction to on/off.
	void setOutputLowerLimit(BRIGHTNESS_TYPE lowerLimit);			// Sets the lower limit of the MultiLED.
	void setOutputUpperLimit(BRIGHTNESS_TYPE upperLimit);			// Sets the upper limit of the MultiLED.
	virtual void setBrightness(BRIGHTNESS_TYPE brightness);	// Sets the brightness to a certain value.

	// Getters:

	BRIGHTNESS_TYPE getOutputLowerLimit();							// Returns the lower limit.
	BRIGHTNESS_TYPE getOutputUpperLimit();							// Returns the upper limit.

	virtual BRIGHTNESS_TYPE getBrightness();				// Returns the value of the current brightness.
	virtual BRIGHTNESS_TYPE getMaxBrightness();				// Returns the maximal value to what the unscaled brightness can be set.
	virtual BRIGHTNESS_TYPE getMinBrightness();				// Returns the maximal value to what the unscaled brightness can be set.

	uint8_t			getPin();										// Returns the output pin number.
	bool			isGammaCorrectionEnabled();					// Returns the state of the gamma correction.
	char *			getID();										// Returns the identificator of the led.
																	   
	bool			isLighted();									// Indicates if the LED is either fully on or dimmed.
	bool			isMax();										// Indicates if the LED is at its high limit.
	bool			isMin();										// Indicates if the LED is at its low limit.
	bool			isEnabled();									// Indicates if the LED is enabled.
	bool			isDisabled();									// Indicates if the LED is disabled.

	// Methods:

	virtual BRIGHTNESS_TYPE update();
	void updateAndWrite();
	void write();

	void increaseBrightness(BRIGHTNESS_TYPE amount);				// Increase the current brightness by the given amount.
	void decreaseBrightness(BRIGHTNESS_TYPE amount);				// Decrease the current brightness by the given amount.
																	   
	void enable();													// Enable the LED output.
	void disable();													// Disable the LED output.


private:

	BRIGHTNESS_TYPE unscaledToFinalBrightness(BRIGHTNESS_TYPE unscaledBrightness);

	// Fields
	char *			ID;
	uint8_t			pin;

	BRIGHTNESS_TYPE outputLowerLimit;
	BRIGHTNESS_TYPE outputUpperLimit;

	BRIGHTNESS_TYPE brightness;

	bool			gammaCorrectionEnabled;

	bool			enabled;
};




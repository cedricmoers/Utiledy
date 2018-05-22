//Debug.h

#ifndef _DEBUG_h
	#define _DEBUG_h
	
	#ifdef ENABLE_DEBUG
	
		#define DEBUG_PRINT_HEADER(...)		{									\
												Serial.print(millis());			\
												Serial.print("::");				\
												Serial.print(getID());			\
												Serial.print("::");				\
											}
		#define DEBUG_PRINTLN_HEADER(...)	{									\
												DEBUG_PRINT_HEADER();			\
												Serial.println(__VA_ARGS__);	\
											}
		#define DEBUG_PARAMETER(name, value){									\
												DEBUG_PRINT_HEADER();			\
												DEBUG_PRINT(name);				\
												DEBUG_PRINT_F("::");			\
												DEBUG_PRINTLN(value);			\
											}
		
		#define DEBUG_PRINT(...)				Serial.print(__VA_ARGS__);
		#define DEBUG_PRINT_F(...)				Serial.print(__VA_ARGS__);
		#define DEBUG_PRINTLN(...)				Serial.println(__VA_ARGS__);
		#define DEBUG_PRINTLN_F(...)			Serial.println(__VA_ARGS__);
	
	#else
	
		#define DEBUG_PRINT_HEADER(...)     // Now defines a blank macro, debug is disabled.
		#define DEBUG_PARAMETER(...)		// Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINT(...)			// Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINT_F(...)			// Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINTLN(...)			// Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINTLN_F(...)		// Now defines a blank macro, debug is disabled.
	
	#endif
#endif
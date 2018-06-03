//Debug.h

#ifndef _DEBUG_h
	#define _DEBUG_h
	
	#ifdef ENABLE_DEBUG
		#define DEBUG_HEADER(...)			{										\
												if(isDebugEnabled()) {				\
												Serial.print(millis());				\
												Serial.print("::");					\
												Serial.print(getID());				\
												Serial.print("::");}				\
											}
		#define DEBUG_PRINTLN_HEADER(...)	{										\
												if(isDebugEnabled()) {				\
												DEBUG_HEADER();						\
												Serial.println(__VA_ARGS__);}		\
											}
		#define DEBUG_PRINT_HEADER(...)		{										\
												if(isDebugEnabled()) {				\
												DEBUG_HEADER();						\
												Serial.print(__VA_ARGS__);}			\
											}
		#define DEBUG_PRINTLN_F_HEADER(...)	{										\
												if(isDebugEnabled()) {				\
												DEBUG_HEADER();						\
												Serial.println(__VA_ARGS__);}		\
											}
		#define DEBUG_PRINT_F_HEADER(...)	{										\
												if(isDebugEnabled()) {				\
												DEBUG_HEADER();						\
												Serial.print(__VA_ARGS__);}			\
											}
		#define DEBUG_PARAMETER(name, value){										\
												if(isDebugEnabled()) {				\
												DEBUG_HEADER();						\
												DEBUG_PRINT(name);					\
												DEBUG_PRINT_F(":");					\
												DEBUG_PRINTLN(value);}				\
											}
		
		#define DEBUG_PRINT(...)				if(isDebugEnabled()) {Serial.print(__VA_ARGS__);	}
		#define DEBUG_PRINT_F(...)				if(isDebugEnabled()) {Serial.print(__VA_ARGS__);	}
		#define DEBUG_PRINTLN(...)				if(isDebugEnabled()) {Serial.println(__VA_ARGS__);	}
		#define DEBUG_PRINTLN_F(...)			if(isDebugEnabled()) {Serial.println(__VA_ARGS__);	}
	
	#else
		#define DEBUG_HEADER(...)			// Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINTLN_HEADER(...)     // Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINT_HEADER(...)   // Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINTLN_F_HEADER(...)   // Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINT_F_HEADER(...) // Now defines a blank macro, debug is disabled.
		#define DEBUG_PARAMETER(...)		// Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINT(...)			// Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINT_F(...)			// Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINTLN(...)			// Now defines a blank macro, debug is disabled.
		#define DEBUG_PRINTLN_F(...)		// Now defines a blank macro, debug is disabled.
	
	#endif
#endif
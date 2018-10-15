//~ #define DEBUG

#pragma once
#include <Arduino.h>
#include <StringBuffer.h>
#include <avr/pgmspace.h>

class AT {
	
	private :
		HardwareSerial *hs;
	
	public :	
		
		AT(HardwareSerial *hs);
		~AT();
		
		bool readAndCheck(char *pattern, unsigned long timeout, unsigned long chartimeout);
		bool readAndCheck(StringBuffer *sb, char *pattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout);
		bool readAndCheck(String *str, char *pattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout);
		void send(char *cmd);
		void flush();
				
		void sendAndWait(char *cmd, unsigned int time);
		bool sendAndCheck(char *cmd, char *pattern, unsigned long timeout, unsigned long chartimeout);
		bool sendAndCheck(char *cmd, StringBuffer *sb, char *firstPattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout);
		bool sendAndCheck(char *cmd, String *str, char *firstPattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout);
		
		// FOR PROGMEM
		void sendPM(const char *cmd);
		void sendAndWaitPM(const char *cmd, unsigned int time);
		bool sendAndCheckPM(const char *cmd, char *pattern, unsigned long timeout, unsigned long chartimeout);
		bool sendAndCheckPM(const char *cmd, StringBuffer *sb, char *firstPattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout);
		bool sendAndCheckPM(const char *cmd, String *str, char *firstPattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout);

};

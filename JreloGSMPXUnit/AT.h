#pragma once
#include <Arduino.h>
#include <StringBuffer.h>

#define DEBUG


const char AT_OK_RESPONSE[] 	   = "OK\r\n";		
const char AT_END[] 	   		   = "\r\n";			
const char AT_COMMAND_1[]  PROGMEM = "AT\r\n";		
const char AT_COMMAND_2[]  PROGMEM = "AT+HTTPREAD\r\n";
const char AT_COMMAND_3[]  PROGMEM = "AT+HTTPACTION=1\r\n";		
const char AT_COMMAND_4[]  PROGMEM = "AT+HTTPACTION=0\r\n";		
const char AT_COMMAND_5[]  PROGMEM = "AT+HTTPINIT\r\n";		
const char AT_COMMAND_6[]  PROGMEM = "AT+HTTPTERM\r\n";		
const char AT_COMMAND_7[]  PROGMEM = "AT+HTTPPARA=\"CID\",1\r\n";	
const char AT_COMMAND_8[]  PROGMEM = "AT+CSQ\r\n";	
const char AT_COMMAND_9[]  PROGMEM = "AT+SAPBR=2,1\r\n";	
const char AT_COMMAND_10[] PROGMEM = "AT+SAPBR=1,1\r\n";	
const char AT_COMMAND_11[] PROGMEM = "AT+SAPBR=2,1\r\n";	
const char AT_COMMAND_12[] PROGMEM = "AT+HTTPSSL=1\r\n";	
const char AT_COMMAND_13[] PROGMEM = "AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n";	
const char AT_COMMAND_14[] PROGMEM = "AT+CPIN?\r\n";	
const char AT_COMMAND_15[] PROGMEM = "AT+CREG?\r\n";	
const char AT_COMMAND_16[] PROGMEM = "AT+CPOWD=0\r\n";	
const char AT_COMMAND_17[] PROGMEM = "AT+HTTPPARA=\"CONTENT\",\"application/json\"\r\n";
const char AT_COMMAND_18[] PROGMEM = "AT+HTTPPARA=\"URL\",\"";	
const char AT_COMMAND_19[] PROGMEM = "\"\r\n";
const char AT_COMMAND_20[] PROGMEM = "AT+HTTPPARA=\"USERDATA\",\"";	
const char AT_COMMAND_21[] PROGMEM = "AT+HTTPDATA=";	
const char AT_COMMAND_22[] PROGMEM = ",100000\r\n";	
const char AT_COMMAND_23[] PROGMEM = "AT+SAPBR=3,1,\"APN\",\"";	
const char AT_COMMAND_24[] PROGMEM = "AT+CPIN=";	

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

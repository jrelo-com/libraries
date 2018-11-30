/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 2.1.0
 * */

//#define DEBUG

#pragma once
#include <Arduino.h>
#include <avr/pgmspace.h>
#include <StringBuffer.h>

#define DELAY 10

class ATCommandExecutor {

    private :
    
        HardwareSerial *hs;
        bool readAndCheck(StringBuffer *responseBuffer, char *firstPattern, char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout); 
        void send(const char *cmd); // for progmem
        void send(StringBuffer *cmd);
        void flush();
        
    public :

        ATCommandExecutor(HardwareSerial *hs);
        ~ATCommandExecutor();
        
        bool sendAndCheck(StringBuffer  *cmd,  								char *firstPattern, char *secondPattern = NULL, uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000);        
		bool sendAndCheck(const char 	*cmd,  								char *firstPattern, char *secondPattern = NULL, uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000);        
		bool sendAndCheck(StringBuffer  *cmd, StringBuffer *responseBuffer, char *firstPattern, char *secondPattern = NULL, uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000);
		bool sendAndCheck(const char 	*cmd, StringBuffer *responseBuffer, char *firstPattern, char *secondPattern = NULL, uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000);        

};

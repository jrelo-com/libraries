/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 2.1.1
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
        bool readAndCheck(StringBuffer *responseBuffer, const char *firstPattern, const char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout); 
        void send(const char *cmd); // for progmem
        void send(StringBuffer *cmd);
        void flush();
        
    public :

        ATCommandExecutor(HardwareSerial *hs);
        ~ATCommandExecutor();
        
        bool sendAndCheck(StringBuffer  *cmd,  								const char *firstPattern, const char *secondPattern = NULL, uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000);        
		bool sendAndCheck(const char 	*cmd,  								const char *firstPattern, const char *secondPattern = NULL, uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000);        
		bool sendAndCheck(StringBuffer  *cmd, StringBuffer *responseBuffer, const char *firstPattern, const char *secondPattern = NULL, uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000);
		bool sendAndCheck(const char 	*cmd, StringBuffer *responseBuffer, const char *firstPattern, const char *secondPattern = NULL, uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000);        

};

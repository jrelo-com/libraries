/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 3.0.0
 * */

//#define DEBUG

#pragma once
#include <Arduino.h>
#include <WDT.h>
#include <avr/pgmspace.h>
#include <StringBuffer.h>
#include <SIMActionHandler.h>

#define DELAY 6

const char AT_COMMAND_1 [] PROGMEM = "AT\r\n";
const char AT_COMMAND_2 [] PROGMEM = "AT+HTTPREAD\r\n";
const char AT_COMMAND_3 [] PROGMEM = "AT+HTTPACTION=1\r\n";
const char AT_COMMAND_4 [] PROGMEM = "AT+HTTPACTION=0\r\n";
const char AT_COMMAND_5 [] PROGMEM = "AT+HTTPINIT\r\n";
const char AT_COMMAND_6 [] PROGMEM = "AT+HTTPTERM\r\n";
const char AT_COMMAND_7 [] PROGMEM = "AT+HTTPPARA=\"CID\",1\r\n";
const char AT_COMMAND_8 [] PROGMEM = "AT+CSQ\r\n";
const char AT_COMMAND_9 [] PROGMEM = "AT+SAPBR=2,1\r\n";
const char AT_COMMAND_10[] PROGMEM = "AT+SAPBR=1,1\r\n";
const char AT_COMMAND_11[] 		   = "AT+CPIN=";
const char AT_COMMAND_12[] PROGMEM = "AT+HTTPSSL=1\r\n";
const char AT_COMMAND_13[] PROGMEM = "AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n";
const char AT_COMMAND_14[] PROGMEM = "AT+CPIN?\r\n";
const char AT_COMMAND_15[] PROGMEM = "AT+CREG?\r\n";
const char AT_COMMAND_16[] PROGMEM = "AT+CPOWD=0\r\n";
const char AT_COMMAND_17[] PROGMEM = "AT+HTTPPARA=\"CONTENT\",\"application/json\"\r\n";
const char AT_COMMAND_18[]         = "AT+HTTPPARA=\"URL\",\"";
const char AT_COMMAND_19[]         = "\"\r\n";
const char AT_COMMAND_20[] 		   = "AT+HTTPPARA=\"USERDATA\",\"";
const char AT_COMMAND_21[]         = "AT+HTTPDATA=";
const char AT_COMMAND_22[]         = ",100000\r\n";
const char AT_COMMAND_23[]         = "AT+SAPBR=3,1,\"APN\",\"";
const char AT_COMMAND_24[] PROGMEM = "AT+HTTPSSL=0\r\n";
const char AT_COMMAND_25[] PROGMEM = "AT+CBC\r\n";
const char AT_COMMAND_26[] PROGMEM = "AT+CIPGSMLOC=1,1\r\n";
const char AT_COMMAND_27[] PROGMEM = "AT+CLIP=1\r\n";
const char AT_COMMAND_28[] PROGMEM = "AT+DDET=1\r\n";
const char AT_COMMAND_29[] PROGMEM = "AT+GSMBUSY=0\r\n";
const char AT_COMMAND_30[] PROGMEM = "AT+GSMBUSY=1\r\n";
const char AT_COMMAND_31[] PROGMEM = "ATA\r\n";
const char AT_COMMAND_32[] PROGMEM = "ATH\r\n";
const char AT_COMMAND_33[] 		   = "ATD";
const char AT_COMMAND_34[] 		   = "AT+CMGS";
const char AT_COMMAND_35[] PROGMEM = "AT+CMGF=1\r\n";


const char AT_RING 				[] = "RING\r\n";
const char AT_BUSY 				[] = "BUSY\r\n";
const char AT_NO_ANSWER			[] = "NO ANSWER\r\n";
const char AT_NO_CARRIER 		[] = "NO CARRIER\r\n";
const char AT_OK				[] = "OK\r\n";
const char AT_END_LINE			[] = "\r\n";
const char AT_COMMAND_5_PART_1	[] = "ERROR";
const char AT_COMMAND_8_PART_1	[] = "+CSQ:";
const char AT_COMMAND_9_PART_1	[] = "+SAPBR: 1,1";
const char AT_COMMAND_9_PART_2	[] = "+SAPBR: 1,1";
const char AT_COMMAND_14_PART_1	[] = "+CPIN:";
const char AT_COMMAND_14_PART_2	[] = "+CPIN: READY";
const char AT_COMMAND_14_PART_3	[] = "+CPIN: SIM PIN";
const char AT_COMMAND_14_PART_4	[] = "+CME ERROR: incorrect password";
const char AT_COMMAND_14_PART_5	[] = "+CPIN: SIM PUK";
const char AT_COMMAND_15_PART	[] = "+CREG:";
const char AT_COMMAND_15_PART_0	[] = ",0\r\n";
const char AT_COMMAND_15_PART_1	[] = ",1\r\n";
const char AT_COMMAND_15_PART_2	[] = ",2\r\n";
const char AT_COMMAND_15_PART_3	[] = ",3\r\n";
const char AT_COMMAND_15_PART_4	[] = ",4\r\n";
const char AT_COMMAND_15_PART_5	[] = ",5\r\n";
const char AT_COMMAND_21_PART_1	[] = "DOWNLOAD\r\n";
const char AT_COMMAND_26_PART_1	[] = "+CIPGSMLOC: 0,";
const char AT_COMMAND_27_PART_1	[] = "+CLIP:";
const char AT_COMMAND_28_PART_1	[] = "+DTMF:";
const char AT_COMMAND_34_PART_1	[] = "+HTTPACTION:";



class ATCommandExecutor {

    private :

        HardwareSerial *hs;
        SIMActionHandler *action = NULL;

        bool readAndCheck(StringBuffer *responseBuffer, const char *firstPattern, const char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout, bool blockSIMActionHandler);
        void send(const char *cmd); // for progmem
        void send(StringBuffer *cmd);
        void flush();

    public :

        ATCommandExecutor(HardwareSerial *hs);
        ~ATCommandExecutor();
        void setSIMActionHandler(SIMActionHandler *action);

        bool sendAndCheck(StringBuffer  *cmd,  									const char *firstPattern, const char *secondPattern = NULL, 					uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000, bool blockSIMActionHandler = false);
        bool sendAndCheck(const char 	*cmd,  									const char *firstPattern, const char *secondPattern = NULL, 					uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000, bool blockSIMActionHandler = false);
        bool sendAndCheck(StringBuffer  *cmd, 	StringBuffer *responseBuffer,	const char *firstPattern, const char *secondPattern = NULL, 					uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000, bool blockSIMActionHandler = false);
        bool sendAndCheck(const char 	*cmd, 	StringBuffer *responseBuffer, 	const char *firstPattern, const char *secondPattern = NULL, 					uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000, bool blockSIMActionHandler = false);
        bool wait(								StringBuffer *responseBuffer, 	const char *firstPattern, const char *secondPattern = NULL,						uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000, bool blockSIMActionHandler = false);
        uint8_t multiWait(StringBuffer *responseBuffer, const char *pattern1, const char *pattern2, const char *pattern3 = NULL, const char *pattern4 = NULL, 	uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000);
        uint8_t multiWait(								const char *pattern1, const char *pattern2, const char *pattern3 = NULL, const char *pattern4 = NULL, 	uint32_t fullTimeout = 10000, uint32_t charTimeout = 10000);
};





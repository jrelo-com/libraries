/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 2.1.0
 * */
 
#pragma once
#include <Arduino.h>
#include <avr/pgmspace.h>

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

const char AT_OK				[] = "OK\r\n";
const char AT_END_LINE			[] = "\r\n";
const char AT_COMMAND_8_PART_1	[] = "+CSQ:"; 
const char AT_COMMAND_14_PART_1	[] = "+CPIN:";
const char AT_COMMAND_14_PART_2	[] = "+CPIN: READY";
const char AT_COMMAND_14_PART_3	[] = "+CPIN: SIM PIN";
const char AT_COMMAND_14_PART_4	[] = "+CME ERROR: incorrect password";
const char AT_COMMAND_14_PART_5	[] = "+CPIN: SIM PUK";
const char AT_COMMAND_15_PART_1	[] = "+CREG:";
const char AT_COMMAND_15_PART_2	[] = "+CREG: 0,1";
const char AT_COMMAND_15_PART_3	[] = "+CREG: 0,5";
const char AT_COMMAND_9_PART_1	[] = "+SAPBR: 1,1";
const char AT_COMMAND_9_PART_2	[] = "+SAPBR: 1,1";
const char AT_COMMAND_5_PART_1	[] = "ERROR";
const char AT_COMMAND_34_PART_1	[] = "+HTTPACTION:";
const char AT_COMMAND_21_PART_1	[] = "DOWNLOAD\r\n";

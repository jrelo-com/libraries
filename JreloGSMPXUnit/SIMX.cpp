#include <SIMX.h>

/*
 *
 *
 *
 *
 *
 *
 * PUBLIC
 * */
float* SIMX::getLocation(){
	return location;
} 
 
 
uint8_t SIMX::getSignalQuality() {
    return this->signalQuality;
}
         
uint16_t SIMX::getVoltage(){
	return this->voltage;
}

uint16_t SIMX::getResetCounter(){
	return resetCounter;
}
 
ATCommandExecutor* SIMX::getAtCmdEx() {
    return atEx;
}

void SIMX::setStringBox(StringBox *stringBox) {
    this->stringBox = stringBox;
}

SIMX::SIMX( HardwareSerial *hs, uint8_t powerPin) {

    this->powerPin = powerPin;
    pinMode(powerPin, OUTPUT);
    this->atEx = new ATCommandExecutor(hs);
}

SIMX::~SIMX() {}

bool SIMX::getAction(StringBuffer *responseBody, uint16_t *responseCode) {
    unsigned long start = millis();
    bool result = sendRequest(GET, responseBody, responseCode);

#ifdef DEBUG
    Serial.print(F("SIMX. Time GET request = "));
    Serial.println(millis() - start);
#endif

    return result;
}

bool SIMX::postAction(StringBuffer *requestBody, uint16_t *responseCode) {
    unsigned long start = millis();
    bool result = sendRequest(POST, requestBody, responseCode);

#ifdef DEBUG
    Serial.print(F("SIMX. Time POST request = "));
    Serial.println(millis() - start);
#endif

    return result;
}

void SIMX::useHTTPS(bool flag) {
    this->useHTTPSFlag = flag;
}

bool SIMX::isHTTPSUsed() {
    return useHTTPSFlag;
}

void SIMX::update() {

    if(!SIMAvailableFlag) {
        bool result = power();
        if(result) {
            SIMAvailableFlag = true;
            successProcessing(POWER_ON);
        } else {
            errorProcessing(POWER_ON);
            return;
        }
    }

    if(SIMAvailableFlag && !prepareFlag) {
        prepareFlag = true;
        if(checkPIN()) {
            successProcessing(CHECK_PIN);
            prepareFlag = true;
        } else {
            errorProcessing(CHECK_PIN);
        }
    }

    if(errorCounter)
        checkErrors();

	if(controlTimer0.event()) {

		Serial.print(F("SIMX. Signal quality = "));
		Serial.println(signalQuality);
		Serial.print(F("SIMX. Voltage = "));
		Serial.println(voltage);
		Serial.print(F("SIMX. Reset counter = "));
		Serial.println(resetCounter);
		Serial.print(F("SIMX. Failed action counter = "));
		Serial.println(failedActionCounter);

		if(SIMAvailableFlag) {
			
			if(!checkSIMBoard()) {
				SIMAvailableFlag = false;
				networkFlag = false;
				prepareFlag = false;
				GPRSConnectionFlag = false;
				Serial.println(F("SIMX. Board unavailable"));
				return;
			}

			if(checkSignal()) {
				successProcessing(CHECK_SIGNAL);

				if(signalQuality > 6) {
					if(!networkFlag && isNetworkReady()) {
						networkFlag = true;
						Serial.println(F("SIMX. Network is ready !"));
					}
					if(!GPRSConnectionFlag && prepareGPRS()) {
						GPRSConnectionFlag = true;
						Serial.println(F("SIMX. GPRS connection is ready !"));
					}
				}
			} else {
				errorProcessing(CHECK_SIGNAL);
				networkFlag = false;
				GPRSConnectionFlag = false;
			}
		}
	}
	
	if(SIMAvailableFlag && controlTimer1.event() ){
		
		if(checkVoltage()) {
			successProcessing(CHECK_VOLTAGE);
		} else {
			errorProcessing(CHECK_VOLTAGE);
		}
		
		if(signalQuality > 6 && networkFlag && checkLocation()) {
			successProcessing(GET_LOCATION);
		} else {
			errorProcessing(GET_LOCATION);
		}
	}

}

void SIMX::setPIN(char *PIN) {
    this->PIN = PIN;
}

void SIMX::setAPN(char *APN) {
    this->APN = APN;
}

void SIMX::setResetPin(uint8_t resetPin) {
    this->resetPin = resetPin;
    pinMode(resetPin, OUTPUT);
}

bool SIMX::isReady() {
    return networkFlag && GPRSConnectionFlag;
}

void SIMX::setUrl(char *url) {
    this->url = url;
}

void SIMX::setHeaders(char *headers) {
    this->headers = headers;
}

/*
 *
 *
 *
 *
 * PRIVATE
 * */
bool SIMX::checkLocation(){
	StringBuffer buffer0 = StringBuffer(stringBox);
	bool result = atEx->sendAndCheck(AT_COMMAND_26, &buffer0, AT_OK);
	if(!result)
		return false;
		
	if(!strstr(buffer0.toString(), AT_COMMAND_26_PART_1)) {
		return false;
	}
	
	StringBuffer buffer1 = StringBuffer(stringBox);
	StringBufferUtils::substringBetween(&buffer0, &buffer1, AT_COMMAND_26_PART_1, AT_END_LINE);

	char *part = strtok(buffer1.toString(), COMMA);
	uint8_t l = 0;	
	
	while(part != NULL && l != 2) {
		float coo = TypeConverter::charArrayToFloat(part);
		location[l] = coo;
		l++;
		part = strtok(NULL, COMMA);	
	}
	
	return true;
}

 
bool SIMX::checkVoltage(){
	StringBuffer buffer0 = StringBuffer(stringBox);
	bool result = atEx->sendAndCheck(AT_COMMAND_25, &buffer0, AT_OK);
	if(!result)
		return false;
		
	int index = StringBufferUtils::tailSearch(&buffer0, ",");
	if(index == -1)
		return false;
	
	StringBuffer buffer1 = StringBuffer(stringBox);
	StringBufferUtils::substring(&buffer0, &buffer1, index+1, buffer0.size()-8);
	
	int voltage = TypeConverter::charArrayToInt(buffer1.toString());
	if(voltage == 0)
		return false;
	
	this->voltage = voltage;
	
	return true;
} 
 
 
bool SIMX::power() {
    if(checkSIMBoard()) {
        return true;
    } else {
        powerOn();
        return checkSIMBoard();
    }
}

void SIMX::powerOn() {
    digitalWrite(powerPin,LOW);
    delay(10);
    digitalWrite(powerPin,HIGH);
    delay(1250);
    digitalWrite(powerPin,LOW);
    delay(10);
}

bool SIMX::checkSIMBoard() {
    return atEx->sendAndCheck(AT_COMMAND_1, AT_OK, NULL, 2000, 2000);
}

void SIMX::errorProcessing(Action lastFailureAction, char *message) {
    if(this->lastFailureAction != lastFailureAction) {
        this->lastFailureAction = lastFailureAction;
    }
    errorCounter++;
    failedActionCounter++;

    Serial.print(F("\t\t\t\t  ERROR ACTION - "));
    Serial.print(lastFailureAction);
    Serial.print(F(", COUNT - "));
    Serial.println(errorCounter);

    if(message == NULL)
        return;

    Serial.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
    Serial.println(message);
    Serial.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
}

void SIMX::successProcessing(Action lastSuccessfulAction) {
    if(this->lastFailureAction == lastSuccessfulAction) {
        this->errorCounter = 0;
    }
    this->lastSuccessfulAction = lastSuccessfulAction;

    Serial.print(F("\t\t\t\tSUCCESS ACTION - "));
    Serial.println(lastSuccessfulAction);
}

void SIMX::powerOff() {
    //~ atEx->sendAndCheck(AT_COMMAND_16, EMPTY_STRING, 100, 100); 
    
    digitalWrite(powerPin,LOW);
    delay(10);
    digitalWrite(powerPin,HIGH);
    delay(1250);
    digitalWrite(powerPin,LOW);
    delay(10);
}

void SIMX::restart() {
    lastFailureAction = EMPTY;
    lastSuccessfulAction = EMPTY;
    errorCounter = 0;
    resetCounter++;

    if(resetPin) {
        digitalWrite(resetPin,HIGH);
        delay(300);
        digitalWrite(resetPin,LOW);
    } else {
        powerOff();
    }
}

void SIMX::checkErrors() {

	if(failedActionCounter >= MAX_FAILED_ACTIONS){
	    Serial.println(F("SIMX. Reset "));
	    failedActionCounter = 0;
	    lastFailureAction = 0;
        restart();
	}

    if(lastFailureAction == RESPONSE_60x) {
        if(errorCounter > MCE_RESPONSE_60x) {
            Serial.println(F("SIMX. Response 60X. Restart 60 sec..."));
            restart();
        }
        return;
    }

    if(lastFailureAction == CHECK_PIN) {
        Serial.println(F("SIMX. Can not use SIM."));
        powerOff();
        return;
    }

    if(lastFailureAction == CHECK_NETWORK) {
        if(errorCounter > MCE_CHECK_NETWORK) {
            Serial.println(F("SIMX. Network problems. Restart..."));
            restart();
        }
        return;
    }

    if(lastFailureAction == INIT_HTTP) {
        if(errorCounter > MCE_INIT_HTTP) {
            Serial.println(F("SIMX. Can't initialize HTTP. Restart..."));
            restart();
        }
        return;
    }

    if(lastFailureAction == PREPARE_GPRS ) {
        if(errorCounter > MCE_PREPARE_GPRS) {
            Serial.println(F("SIMX. GPRS problems. Restart..."));
            restart();
        }
        return;
    }

    if(errorCounter > MCE_OTHER) {
        Serial.println(F("SIMX. I have problems, something is wrong. Restart..."));
        restart();
    }
}

bool SIMX::initHttp() {
    StringBuffer buffer = StringBuffer(stringBox);
    if(atEx->sendAndCheck(AT_COMMAND_5, &buffer, AT_OK)) {
        return true;
    } else if(strstr(buffer.toString(), AT_COMMAND_5_PART_1)) {
        if(httpTerm()) {
            if(atEx->sendAndCheck(AT_COMMAND_5, AT_OK)) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool SIMX::httpTerm() {
    return atEx->sendAndCheck(AT_COMMAND_6, AT_OK);
}

bool SIMX::selectProfile() {
    return atEx->sendAndCheck(AT_COMMAND_7, AT_OK);
}

bool SIMX::configUrl() {
    StringBuffer cmd = StringBuffer(stringBox);
    cmd.appendString(AT_COMMAND_18);
    cmd.appendString(url);
    cmd.appendString(AT_COMMAND_19);

    return atEx->sendAndCheck(&cmd, AT_OK);
}

bool SIMX::setHeader() {

    StringBuffer cmd = StringBuffer(stringBox);
    cmd.appendString(AT_COMMAND_20);
    cmd.appendString(headers);
    cmd.appendString(AT_COMMAND_19);

    return atEx->sendAndCheck(&cmd, AT_OK);
}

bool SIMX::sendRequest(RequestMethod method, StringBuffer *body, uint16_t *httpStatusCode) {

    if(initHttp()) {
        successProcessing(INIT_HTTP);
    } else {
        errorProcessing(INIT_HTTP);
        return false;
    }

    if(selectProfile()) {
        successProcessing(SELECT_PROFILE);
    } else {
        errorProcessing(SELECT_PROFILE);
        return false;
    }

    if(configUrl()) {
        successProcessing(SET_URL);
    } else {
        errorProcessing(SET_URL);
        return false;
    }

    if(setHeader()) {
        successProcessing(SET_HEADER);
    } else {
        errorProcessing(SET_HEADER);
        return false;
    }

    if(useHTTPSFlag) {
        if(enableSSL()) {
            successProcessing(SET_SSL);
        } else {
            errorProcessing(SET_SSL);
            return false;
        }
    }

    if(method == GET) {

        StringBuffer buffer = StringBuffer(stringBox);
        if(sendGetRequest(&buffer)) {
            successProcessing(SEND_REQUEST);
        } else {
            errorProcessing(SEND_REQUEST, buffer.toString());
            return false;
        }

        uint16_t dataLength = -1;

        if(getHttpStatusCodeAndDataLength(&buffer, httpStatusCode, &dataLength)) {
            successProcessing(GET_HTTP_STATUS_CODE);
        } else {
            errorProcessing(GET_HTTP_STATUS_CODE);
            return false;
        }

        if(*httpStatusCode == 200) {
            buffer.clear();

            if(atEx->sendAndCheck(AT_COMMAND_2, &buffer, AT_OK)) {
                successProcessing(HTTP_READ);
            } else {
                errorProcessing(HTTP_READ, buffer.toString());
                return false;
            }

            uint16_t len = buffer.size();
            uint16_t temp = len - 6 - dataLength;

            StringBufferUtils::substring(&buffer, body, temp, temp+dataLength);
        }
    } else if(method == POST) {

		if(atEx->sendAndCheck(AT_COMMAND_17, AT_OK)) {
			successProcessing(HTTP_PARA);
		} else {
			errorProcessing(HTTP_PARA);
			return false;
		}

		if(!setHttpData(body)) {
			return false;
		}

		StringBuffer buffer = StringBuffer(stringBox);
		if(sendPostRequest(&buffer)) {
			successProcessing(SEND_REQUEST);
		} else {
			errorProcessing(SEND_REQUEST);
			return false;
		}

		int dataLength = -1;

		if(getHttpStatusCodeAndDataLength(&buffer, httpStatusCode, &dataLength)) {
			successProcessing(GET_HTTP_STATUS_CODE);
		} else {
			errorProcessing(GET_HTTP_STATUS_CODE);
			return false;
		}
    }

	Serial.print(F("SIMX. HTTP response status code = "));
	Serial.println(*httpStatusCode);

    if(httpTerm()) {
        successProcessing(HTTP_TERM);
    } else {
        errorProcessing(HTTP_TERM);
        return false;
    }

	if(*httpStatusCode == 200 || *httpStatusCode == 204){
		failedActionCounter = 0;
		return true;
	}

	if(*httpStatusCode >= 400 && *httpStatusCode <= 526){	
		failedActionCounter = 0;
		return false;
	}
	
    if(*httpStatusCode >= 600) {
        Serial.print(F("SIMX. Error = "));
        Serial.println(*httpStatusCode);

        errorProcessing(RESPONSE_60x);
        return false;
    } 

    return false;
}

bool SIMX::setHttpData(StringBuffer *body) {
    char temp[5] = {0};

    TypeConverter::intToCharArray(temp, body->size());

    StringBuffer cmd = StringBuffer(stringBox);
    cmd.appendString(AT_COMMAND_21);
    cmd.appendString(temp);
    cmd.appendString(AT_COMMAND_22);

    bool result = atEx->sendAndCheck(&cmd, AT_COMMAND_21_PART_1);
    if(result) {
        successProcessing(HTTP_DATA_DOWNLOAD_P1);
    } else {
        errorProcessing(HTTP_DATA_DOWNLOAD_P1);
        return false;
    }

    cmd.clear();
    cmd.appendString(body->toString());
    cmd.appendString(AT_END_LINE);

    result = atEx->sendAndCheck(&cmd, AT_OK);
    if(result) {
        successProcessing(HTTP_DATA_DOWNLOAD_P2);
    } else {
        errorProcessing(HTTP_DATA_DOWNLOAD_P2);
        return false;
    }
    return true;
}

bool SIMX::getHttpStatusCodeAndDataLength(StringBuffer *buffer, uint16_t *httpStatusCode, uint16_t *dataLength) {

    int first = StringBufferUtils::search(buffer, COMMA);
    int last = StringBufferUtils::tailSearch(buffer, COMMA);

    if(first == -1 || last == -1)
        return false;

    StringBuffer tmp = StringBuffer(stringBox);

    StringBufferUtils::substring(buffer, &tmp, first+1, last);
    *httpStatusCode = TypeConverter::charArrayToInt(tmp.toString());

    tmp.clear();

    StringBufferUtils::substring(buffer, &tmp, last+1, buffer->size());
    *dataLength = TypeConverter::charArrayToInt(tmp.toString());

    return true;
}

bool SIMX::sendPostRequest(StringBuffer *buffer) {
    return atEx->sendAndCheck(AT_COMMAND_3, buffer, AT_COMMAND_34_PART_1, AT_END_LINE, 50000, 15000);
}

bool SIMX::sendGetRequest(StringBuffer *buffer) {
    return atEx->sendAndCheck(AT_COMMAND_4, buffer, AT_COMMAND_34_PART_1, AT_END_LINE, 50000, 15000);
}

bool SIMX::checkSignal() {
    StringBuffer buffer = StringBuffer(stringBox);
    bool result = atEx->sendAndCheck(AT_COMMAND_8, &buffer, AT_COMMAND_8_PART_1, AT_OK);

    if(!result) {
        signalQuality = 0;
        return false;
    }

    int start = StringBufferUtils::search(&buffer, AT_COMMAND_8_PART_1);
    int stop = StringBufferUtils::tailSearch(&buffer, COMMA);

    StringBuffer tmp = StringBuffer(stringBox);
    StringBufferUtils::substring(&buffer, &tmp, start + 6, stop);

    signalQuality = TypeConverter::charArrayToInt(tmp.toString());

    return true;
}

bool SIMX::checkPIN() {
    StringBuffer buffer = StringBuffer(stringBox);
    atEx->sendAndCheck(AT_COMMAND_14, &buffer, AT_COMMAND_14_PART_1, AT_OK);

    if(strstr(buffer.toString(), AT_COMMAND_14_PART_2)) {
        return true;

    } else if(strstr(buffer.toString(), AT_COMMAND_14_PART_3)) {
        if(PIN == NULL) {
            Serial.println(F("SIMX: Requires a PIN"));
            return false;
        }

        buffer.clear();
        StringBuffer cmd = StringBuffer(stringBox);
        cmd.appendString(AT_COMMAND_11);
        cmd.appendString(PIN);
        cmd.appendString(AT_END_LINE);

        bool result = atEx->sendAndCheck(&cmd, &buffer, AT_OK);

        if(!result) {
            return false;
        }

        if(strstr(buffer.toString(), AT_COMMAND_14_PART_4)) {
            Serial.println(F("SIMX. Incorrect PIN."));
            return false;
        }
        return true;

    } else if (strstr(buffer.toString(), AT_COMMAND_14_PART_5)) {
        Serial.println(F("SIMX. SIM card is locked."));
        return false;
    } else {
        return false;
    }
}

bool SIMX::configAPN() {
    if(APN == NULL)
        return false;

    if(!atEx->sendAndCheck(AT_COMMAND_13, AT_OK))
        return false;

    StringBuffer cmd = StringBuffer(stringBox);
    cmd.appendString(AT_COMMAND_23);
    cmd.appendString(APN);
    cmd.appendString(AT_COMMAND_19);

    return atEx->sendAndCheck(&cmd, AT_OK);
}

bool SIMX::prepareGPRS() {

    if(configAPN()) {
        successProcessing(CONFIG_APN);
    } else {
        errorProcessing(CONFIG_APN);
        return false;
    }

    if(openGPRSConnection()) {
        successProcessing(PREPARE_GPRS);
    } else {
        errorProcessing(PREPARE_GPRS);
        return false;
    }

    return true;
}

bool SIMX::enableSSL() {
    if(atEx->sendAndCheck(AT_COMMAND_12, AT_OK)) {
        return true;
    }

    Serial.println(F("SIMX. Failed to enable SSL"));
    return false;
}

// not used
bool SIMX::disableSSL() {
    if(atEx->sendAndCheck(AT_COMMAND_24, AT_OK)) {
        return true;
    }

    Serial.println(F("SIMX. Failed to disable SSL"));
    return false;
}

bool SIMX::openGPRSConnection() {

    if(atEx->sendAndCheck(AT_COMMAND_9, AT_COMMAND_9_PART_1))
        return true;

    if(atEx->sendAndCheck(AT_COMMAND_10, AT_OK)) {
        if(atEx->sendAndCheck(AT_COMMAND_9, AT_COMMAND_9_PART_2, AT_OK)) {
            return true;
        }
    }

    Serial.println(F("SIMX. Could not open GPRS connection !"));
    return false;
}

bool SIMX::isNetworkReady() {
    if(checkNetwork()) {
        successProcessing(CHECK_NETWORK);
        return true;
    } else {
        errorProcessing(CHECK_NETWORK);
        return false;
    }
}

bool SIMX::checkNetwork() {
    Serial.println(F("SIMX.Network search ..."));
    StringBuffer buffer = StringBuffer(stringBox);
    bool result = atEx->sendAndCheck(AT_COMMAND_15, &buffer, AT_COMMAND_15_PART_1, AT_OK);
    if(result) {
        if( strstr(buffer.toString(), AT_COMMAND_15_PART_2) || strstr(buffer.toString(), AT_COMMAND_15_PART_3) ) {
            Serial.println(F("SIMX.Network found !"));
            return true;
        }
    }
    Serial.println(F("SIMX. Network not found !"));
    return false;
}

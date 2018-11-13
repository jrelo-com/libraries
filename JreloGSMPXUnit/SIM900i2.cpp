#include <SIM900i2.h>

/*
 *
 * 
 * 
 * PUBLIC METHODS
 * 
 * 
 * */ 
void SIM900i2::setStringBox(StringBox *stringBox){
	this->stringBox = stringBox;
	this->responseBody = new StringBuffer(stringBox);
}

bool SIM900i2::isHTTPSUsed() {
    return https;
}

bool SIM900i2::isWorking() {
    return workFlag;
}

bool SIM900i2::isReady() {
    return workFlag && readyFlag;
}

int SIM900i2::getSignalQuality() {
    return signalQuality;
}

void SIM900i2::update() {
    
    if(!prepareFlag)
		prepareFlag = prepare();
    
    if(isWorking())
		checkErrors();

    if(selfControlTimer.event() && !checkPower()) {
		readyFlag = false;
		workFlag = false;
		prepareFlag  = false;
    }

    if(networkTimer.event() && isWorking()) {
        if(readyFlag && !checkSignal()) {
            readyFlag = false;
        }

        if(!readyFlag && isNetworkReady() ) {
            if(checkSignal() && signalQuality > NO) {
                if(prepareGPRS()) {
                    readyFlag = true;
                }
            } else {
                Serial.println(F("SIM900i2. Bad signal !"));
            }
        }
    }

    if(restartTimer.event()) {
        restartTimer.stop();
        workFlag = powerOn();
        prepareFlag  = false;
    }

}

bool SIM900i2::getData(char *url, char *header) {
    unsigned long start = millis();
    bool result = sendRequest(GET, url, header, NULL);

#ifdef DEBUG    
    Serial.print(F("SIM900i2. Time GET request = "));
    Serial.println(millis() - start);
#endif
    
    return result;
}

bool SIM900i2::postData(char *requestBody, char *url, char *header) {
    unsigned long start = millis();
    bool result = sendRequest(POST, url, header, requestBody);

#ifdef DEBUG        
    Serial.print(F("SIM900i2. Time POST request = "));
    Serial.println(millis() - start);
#endif    
    
    return result;
}

int SIM900i2::getHttpStatusCode() {
	return httpStatusCode;
}

StringBuffer* SIM900i2::getResponseBody() {
	return responseBody;
}

SIM900i2::SIM900i2(HardwareSerial *hs, int powerPin) {
    this->powerPin = powerPin;
    pinMode(powerPin, OUTPUT);
    this->at = new AT(hs);
}

SIM900i2::~SIM900i2(){
	delete at;
}

void SIM900i2::setPIN(char *pin) {
    this->pin = pin;
}

void SIM900i2::setAPN(char *apn) {
    this->apn = apn;
}

void SIM900i2::useHTTPS(bool https) {
    this->https = https;
}

void SIM900i2::setAT(AT *at) {
	this->at = at;
}

AT* SIM900i2::getAT() {
	return at;
}

StringBox* SIM900i2::getStringBox(){
	return stringBox;
}

/*
 *
 *
 *
 *
 * 
 * 
 * 
 *
 * 
 * 
 *
 *
 * PRIVATE METHODS
 * 
 * 
 * 
 * 
 * */
bool SIM900i2::getHttpStatusCodeAndDataLength(StringBuffer *sb, RequestMethod method, int *httpStatusCode, int *dataLength) {
    char *start = NULL;

    if(method == GET) {
        start = strstr(sb->toString(), "+HTTPACTION:0,");
    } else {
        start = strstr(sb->toString(), "+HTTPACTION:1,");
    }
    if(start == NULL)
        return false;

    int index0 = start - sb->toString() + 14;

    char tempHSC[4] = {'\0'};
    char tempDL[8] = {'\0'};

    int index1 = 0;
    int index2 = 0;

    bool k = false;

    while(true) {
        char c = sb->toString()[index0];
        if(c == ',') {
            k = true;
            index0++;
            continue;
        }

        if(!k) {
            tempHSC[index1] = c;
            index1++;
        } else {
            tempDL[index2] = c;
            index2++;
        }
        index0++;
        if(sb->toString()[index0] == '\r')
            break;
    }

    *httpStatusCode = atoi(tempHSC);
    *dataLength = atoi(tempDL);
    return true;
} 
 
 
bool SIM900i2::sendRequest(RequestMethod method, char *url, char *header, char *requestBody) {

	httpStatusCode = 0;
	
    if(initHttp()) {
        successProcessing(INIT_HTTP);
    } else {
        errorProcessing(INIT_HTTP, NULL);
        return false;
    }

    if(selectProfile()) {
        successProcessing(SELECT_PROFILE);
    } else {
        errorProcessing(SELECT_PROFILE, NULL);
        return false;
    }

    if(setUrl(url)) {
        successProcessing(SET_URL);
    } else {
        errorProcessing(SET_URL, NULL);
        return false;
    }

    if(setHeader(header)) {
        successProcessing(SET_HEADER);
    } else {
        errorProcessing(SET_HEADER, NULL);
        return false;
    }

    if(method == GET) {
		
        StringBuffer tempSb = StringBuffer(stringBox);
        if(sendGetRequest(&tempSb)) {
            successProcessing(SEND_GET_REQUEST); 
        } else {
			errorProcessing(SEND_GET_REQUEST, tempSb.toString()); 
			return false;
		}

        int httpStatusCode = -1;
        int dataLength = -1;

        if(getHttpStatusCodeAndDataLength(&tempSb, method, &httpStatusCode, &dataLength)) {
            successProcessing(GET_HTTP_STATUS_CODE);
        } else {
			errorProcessing(GET_HTTP_STATUS_CODE, NULL);
			return false;
		}

        Serial.print(F("SIM900i2. HttpStatusCode = "));
        Serial.println(httpStatusCode);

        this->httpStatusCode = httpStatusCode;

        if(httpStatusCode == 200) {
            StringBuffer tempSb1 = StringBuffer(stringBox); 
            			
			if(at->sendAndCheckPM(AT_COMMAND_2, &tempSb1, AT_OK_RESPONSE, NULL, 15000, 10000)){
				successProcessing(HTTP_READ);
			} else {
				errorProcessing(HTTP_READ, tempSb1.toString());
				return false;	
			}

			int lastChar = StringBufferUtils::tailSearch(&tempSb1, "\r\nOK\r\n");
            int firstChar = lastChar - dataLength;

            StringBufferUtils::substring(&tempSb1, responseBody, firstChar, lastChar);
        }

    } else if(method == POST) {
		if(at->sendAndCheckPM(AT_COMMAND_17, AT_OK_RESPONSE, 5000, 3000)) {
			successProcessing(HTTP_PARA);
        } else {
			errorProcessing(HTTP_PARA, NULL);
			return false;
		}
		
		if(!setHttpData(requestBody)){
			return false;
		}
        StringBuffer tempSb = StringBuffer(stringBox);
        if(sendPostRequest(&tempSb)){
			successProcessing(SEND_POST_REQUEST);
		} else {
			errorProcessing(SEND_POST_REQUEST, tempSb.toString());
			return false;
		}

        int httpStatusCode = -1;
        int dataLength = -1;

        if(getHttpStatusCodeAndDataLength(&tempSb, method, &httpStatusCode, &dataLength)) {
            successProcessing(GET_HTTP_STATUS_CODE_AND_DATA_LENGTH);
        } else {
			errorProcessing(GET_HTTP_STATUS_CODE_AND_DATA_LENGTH, NULL);
			return false;
		}
        this->httpStatusCode = httpStatusCode;
	}
	
    if(this->httpStatusCode == 600 || this->httpStatusCode == 601) {
        return false;
    }

    if(httpTerm()) {
        successProcessing(HTTP_TERM);
    } else {
		errorProcessing(HTTP_TERM, NULL);
		return false;
	}

    return true;
}

bool SIM900i2::setHttpData(char *requestBody){
	// TS
	char buffer[6];
	strcpy(buffer, ((String)strlen(requestBody)).c_str());

	at->flush();
	at->sendPM(AT_COMMAND_21);
	at->send(buffer);
	at->sendPM(AT_COMMAND_22);
	delay(10);
	bool result = at->readAndCheck("DOWNLOAD\r\n", 5000, 5000);
	if(result) {
		successProcessing(HTTP_DATA_DOWNLOAD_P1);
	} else {
		errorProcessing(HTTP_DATA_DOWNLOAD_P1, NULL);
		return false;
	}	

	at->flush();
	at->send(requestBody);
	at->send(AT_END);
	delay(10);
	result = at->readAndCheck(AT_OK_RESPONSE, 10000, 5000);
	if(result) {
		successProcessing(HTTP_DATA_DOWNLOAD_P2);
	} else {
		errorProcessing(HTTP_DATA_DOWNLOAD_P2, NULL);
		return false;
	}
	return true;
}

bool SIM900i2::sendPostRequest(StringBuffer *sb) {
    return at->sendAndCheckPM(AT_COMMAND_3, sb, "+HTTPACTION:", AT_END, 50000, 10000);
}

bool SIM900i2::sendGetRequest(StringBuffer *sb) {
    return at->sendAndCheckPM(AT_COMMAND_4, sb, "+HTTPACTION:", AT_END, 50000, 15000);   
}

bool SIM900i2::initHttp() {
    StringBuffer sb = StringBuffer(stringBox);
    bool result = at->sendAndCheckPM(AT_COMMAND_5, &sb, AT_OK_RESPONSE, NULL, 5000, 5000);
        
    if(result) {
        return true;
    } else if(strstr(sb.toString(), "+CME ERROR:")) {
        if(httpTerm()) {
            if(at->sendAndCheckPM(AT_COMMAND_5, AT_OK_RESPONSE, 5000, 5000)) {
				return true;      
            }else{
				return false;
			}
        } else {
            return false;
        }
    }
}

bool SIM900i2::httpTerm() {
    return at->sendAndCheckPM(AT_COMMAND_6, AT_OK_RESPONSE, 5000, 5000);
}

bool SIM900i2::selectProfile() {
    return at->sendAndCheckPM(AT_COMMAND_7, AT_OK_RESPONSE, 5000, 5000);
}

bool SIM900i2::setUrl(char *url) {
	// TS
	at->flush();
    at->sendPM(AT_COMMAND_18);
    at->send(url);
    at->sendPM(AT_COMMAND_19);
    delay(10);
    bool result = at->readAndCheck(AT_OK_RESPONSE, 5000, 5000);
    return result;
}

bool SIM900i2::setHeader(char *header) {
	// TS
    at->flush();
    at->sendPM(AT_COMMAND_20);
    at->send(header);
    at->sendPM(AT_COMMAND_19);
    delay(10);
    bool result = at->readAndCheck(AT_OK_RESPONSE, 5000, 5000);
    return result;
}

bool SIM900i2::checkSignal() {
    StringBuffer sb = StringBuffer(stringBox);
    bool result = at->sendAndCheckPM(AT_COMMAND_8, &sb, "+CSQ:", AT_OK_RESPONSE, 7000, 5000);
    if(!result) {
        signalQuality = NO;
        return false;
    }

	StringBuffer sbTemp = StringBuffer(stringBox);
   
    if(!StringBufferUtils::substringBetween(&sb, &sbTemp, "+CSQ: ", ",")) {
        signalQuality = NO;
		return false;
    }

    int x = atoi(sbTemp.toString());
    sbTemp.clear();

    if(x >= 2 && x <= 9)
        signalQuality = MARGINAL;
    else if(x >= 10 && x <= 14)
        signalQuality = OK;
    else if(x >= 15 && x <= 19)
        signalQuality = GOOD;
    else if(x >= 20 && x <= 30)
        signalQuality = EXCELLENT;
    else
        signalQuality = NO;

    Serial.print(F("SIM900i2. Signal - "));
    Serial.println(signalQuality);

    return true;
}

bool SIM900i2::isNetworkReady() {
    if(checkNetwork()) {
        successProcessing(CHECK_NETWORK);
    } else {
        errorProcessing(CHECK_NETWORK, NULL);
        return false;;
    }

    return true;
}

bool SIM900i2::openGPRSConnection() {
	StringBuffer sb = StringBuffer(stringBox);
    bool check = at->sendAndCheckPM(AT_COMMAND_9, &sb, "+SAPBR: 1,1", AT_OK_RESPONSE, 7000, 5000);
	
    if(check)
        return true;

    check = at->sendAndCheckPM(AT_COMMAND_10, AT_OK_RESPONSE, 7000, 5000);
    sb.clear();
    if(check) {
        if(at->sendAndCheckPM(AT_COMMAND_9, &sb, "+SAPBR: 1,1", AT_OK_RESPONSE, 7000, 5000)) {
            return true;
        }
    }
    return false;
}

bool SIM900i2::enableSSL() {
    return at->sendAndCheckPM(AT_COMMAND_12, AT_OK_RESPONSE, 5000, 5000);
}

bool SIM900i2::configAPN() {
    if(!at->sendAndCheckPM(AT_COMMAND_13, AT_OK_RESPONSE, 5000, 5000))
        return false;
    
    // TS
    at->flush();
    at->sendPM(AT_COMMAND_23);
    at->send(apn);
    at->sendPM(AT_COMMAND_19);
    delay(10);
    bool result = at->readAndCheck(AT_OK_RESPONSE, 5000, 5000);
    return result;
}

bool SIM900i2::prepareGPRS() {

    if(apn) {
        if(configAPN()) {
            successProcessing(CONFIG_APN);
        } else {
            errorProcessing(CONFIG_APN, NULL);
            return false;
        }
    }

    if(openGPRSConnection()) {
        successProcessing(PREPARE_GPRS);
    } else {
        errorProcessing(PREPARE_GPRS, NULL);
        return false;
    }

    if(isHTTPSUsed()) {
        if(enableSSL()) {
            successProcessing(SET_SSL);
        } else {
            errorProcessing(SET_SSL, NULL);
            return false;
        }
    }

    return true;
}

bool SIM900i2::prepare() {

    if(powerOn()) {
        successProcessing(POWER_UP);
        workFlag = true;
    } else {
        errorProcessing(POWER_UP, NULL);
        return false;
    }

    if(checkPin()) {
        successProcessing(CHECK_PIN);
    } else {
        errorProcessing(CHECK_PIN, NULL);
        return false;
    }

    return true;
}

void SIM900i2::checkErrors() {

    if(lastError == CHECK_PIN) {
        Serial.println(F("SIM900i2. Can not use SIM900."));
        powerOff();
        return;
    }

    if(lastError == CHECK_NETWORK) {
        if(errorCounter > MAX_NETWORK_CHECKS) {
            Serial.println(F("SIM900i2. Network problems. Restart 60 sec..."));
            reset();
        }
        return;
    }

    if(lastError == PREPARE_GPRS ) {
        if(errorCounter > MAX_PREP_GPRS) {
            Serial.println(F("SIM900i2. GPRS problems. Restart 60 sec..."));
            reset();
        }
        return;
    }

	if(errorCounter > MAX_OTHER_PROBLEMS) {
		Serial.println(F("SIM900i2. I have problems, something is wrong. Restart 60 sec..."));
		reset();
	}

}

void SIM900i2::reset() {
    lastError = EMPTY;
    lastSuccess = EMPTY;
    errorCounter = 0;
    rebootCounter++;

    if(powerOff())
        restartTimer.start();
}

bool SIM900i2::checkPin() {
    StringBuffer sb = StringBuffer(stringBox);
    at->sendAndCheckPM(AT_COMMAND_14, &sb, "+CPIN:", AT_OK_RESPONSE, 5000, 5000);

    if(strstr(sb.toString(), "+CPIN: READY")) {
        return true;
    } else if(strstr(sb.toString(), "+CPIN: SIM PIN")) {
        if(pin == NULL) {
            Serial.println(F("SIM900: Requires a PIN"));
            return false;
        }

		at->flush();
		at->sendPM(AT_COMMAND_24);
		at->send(pin);
		at->send(AT_END);
		delay(10);
		StringBuffer sb1 = StringBuffer(stringBox);
		bool result = at->readAndCheck(&sb1, AT_OK_RESPONSE, NULL, 5000, 5000);
		
		if(!result) {
            return false;
        }

        if(strstr(sb1.toString(), "+CME ERROR: incorrect password\r\n")) {
            Serial.println(F("SIM900i2. Incorrect PIN."));
            return false;
        }
        return true;

    } else if (strstr(sb.toString(), "+CPIN: SIM PUK")) {
        Serial.println(F("SIM900i2. SIM card is locked."));
        return false;
    } else {
        return false;
    }
}

bool SIM900i2::checkNetwork() {
    Serial.println(F("Network search ..."));
    StringBuffer sb = StringBuffer(stringBox);
    bool result = at->sendAndCheckPM(AT_COMMAND_15, &sb, "+CREG:", AT_OK_RESPONSE, 10000, 10000);
    if(result) {
        if( strstr(sb.toString(),"+CREG: 0,1") || strstr(sb.toString(),"+CREG: 0,5") ) {
            return true;
        }
    }
    Serial.println(F("SIM900. Network not found !"));
    return false;
}


void SIM900i2::errorProcessing(Action lastError, char *message) {
    if(this->lastError != lastError) {
        this->lastError = lastError;
    }
    errorCounter++;

    Serial.print(F("\t\t\t\t  ERROR ACTION - "));
    Serial.print(lastError);
    Serial.print(F(", COUNT - "));
    Serial.println(errorCounter);
    
    if(message == NULL)
		return;
		
    Serial.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
    Serial.println(message);
    Serial.println(F("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"));
}

void SIM900i2::successProcessing(Action lastSuccess) {
    if(this->lastError == lastSuccess) {
        this->errorCounter = 0;
    }
    this->lastSuccess = lastSuccess;

    Serial.print(F("\t\t\t\tSUCCESS ACTION - "));
    Serial.println(lastSuccess);
}

bool SIM900i2::powerOn() {
    if(checkPower()) {
        return true;
    }

	digitalWrite(powerPin,LOW);
    delay(1100);
    digitalWrite(powerPin,HIGH);
    delay(2300);
    digitalWrite(powerPin,LOW);
    delay(500);

    if(checkPower()) {
        return true;
    }
    
    return false;
}

bool SIM900i2::powerOff() {
    if(!checkPower()) {
        workFlag = false;
        return true;
    }

    // FAST POWER OFF
    at->sendAndWaitPM(AT_COMMAND_16, 1000);

    if(!checkPower()) {
        workFlag = false;
        return true;
    }

    return false;
}

bool SIM900i2::checkPower() {
    return at->sendAndCheckPM(AT_COMMAND_1, AT_OK_RESPONSE, 5000, 5000);
}


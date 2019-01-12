#include <ATCommandExecutor.h>

ATCommandExecutor::ATCommandExecutor(HardwareSerial *hs) {
    this->hs = hs;
}

ATCommandExecutor::~ATCommandExecutor() {}

void ATCommandExecutor::send(const char *cmd) {
    int len = strlen_P(cmd);
    for (int i = 0; i < len; i++) {
        hs->write(pgm_read_byte_near(cmd + i));
        WDT::reset();
    }
}

void ATCommandExecutor::send(StringBuffer *cmd) {
    while(1) {
        if(hs->availableForWrite()) {
            hs->write(cmd->toString());
            break;
        }
        WDT::reset();
    }
}

void ATCommandExecutor::flush() {
    while(hs->available()) {
        int data = hs->read();

#ifdef DEBUG

        Serial.println(F("AT. Flush"));
        Serial.println((char)data);
        Serial.println(F("~~~~~~~~~~"));
#endif

        WDT::reset();
    }
}


bool ATCommandExecutor::sendAndCheck(StringBuffer *cmd, const char *firstPattern, const char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout, bool blockSIMActionHandler) {
    bool result =  sendAndCheck(cmd, NULL, firstPattern, secondPattern, fullTimeout, charTimeout, blockSIMActionHandler);
    return result;
}


bool ATCommandExecutor::sendAndCheck(StringBuffer *cmd, StringBuffer *responseBuffer, const char *firstPattern, const char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout, bool blockSIMActionHandler) {
    flush();
    send(cmd);

    if(firstPattern == NULL)
        return true;

    bool result = readAndCheck(responseBuffer, firstPattern, secondPattern, fullTimeout, charTimeout, blockSIMActionHandler);
    return result;
}


bool ATCommandExecutor::sendAndCheck(const char *cmd, StringBuffer *responseBuffer, const char *firstPattern, const char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout, bool blockSIMActionHandler) {
    flush();
    send(cmd);

    if(firstPattern == NULL)
        return true;

    bool result = readAndCheck(responseBuffer, firstPattern, secondPattern, fullTimeout, charTimeout, blockSIMActionHandler);
    return result;
}


bool ATCommandExecutor::sendAndCheck(const char *cmd, const char *firstPattern, const char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout, bool blockSIMActionHandler) {
    bool result = sendAndCheck(cmd, NULL, firstPattern, secondPattern, fullTimeout, charTimeout, blockSIMActionHandler);
    return result;
}

/*
 *
 * responseBuffer can be NULL
 * firstPattern can`t be NULL
 * secondPattern can be NULL
 *
 * */
bool ATCommandExecutor::readAndCheck(	StringBuffer *responseBuffer,
                                        const char *firstPattern, 		const char *secondPattern,
                                        uint32_t fullTimeout, 			uint32_t charTimeout, 		bool blockSIMActionHandler) {

    delay(DELAY);

    uint16_t firstPatternLength = strlen(firstPattern);
    uint16_t secondPatternLength = strlen(secondPattern);
    uint16_t ringLength = strlen(AT_RING);
    uint16_t noCarrierLength = strlen(AT_NO_CARRIER);
    uint16_t firstPatternCursor = 0;
    uint16_t secondPatternCursor = 0;
    uint16_t ringCursor = 0;
    uint16_t noCarrierCursor = 0;
    uint32_t start = millis();
    uint32_t lastChar = 0;

    bool result = false;
    bool firstPatternFindFlag = false;
    bool secondPatternFindFlag = secondPattern == NULL? true : false;
    bool ringFindFlag = false;
    bool noCarrierFindFlag = false;

    while(true) {
        WDT::reset();
        while(hs->available()) {
            WDT::reset();
            char c = hs->read();
#ifdef DEBUG
            Serial.print(c);
#endif
            if(responseBuffer != NULL)
                responseBuffer->append(c);

            lastChar = millis();

            if(!firstPatternFindFlag) {
                firstPatternCursor = (firstPattern[firstPatternCursor] == c)? ++firstPatternCursor : 0;
                if(firstPatternCursor == firstPatternLength) {
                    firstPatternFindFlag = true;
                }
            } else if(secondPattern) {
                secondPatternCursor = (secondPattern[secondPatternCursor] == c)? ++secondPatternCursor : 0;
                if(secondPatternCursor == secondPatternLength) {
                    secondPatternFindFlag = true;
                }
            }

            if(!blockSIMActionHandler) {
                ringCursor = (AT_RING[ringCursor] == c)? ++ringCursor : 0;
                if(ringCursor == ringLength) {
                    ringFindFlag = true;
                    if(action != NULL) {
                        action->ring();
                        return false;
                    }
                }

                noCarrierCursor = (AT_NO_CARRIER[noCarrierCursor] == c)? ++noCarrierCursor : 0;
                if(noCarrierCursor == noCarrierLength) {
                    noCarrierFindFlag = true;
                    if(action != NULL) {
                        action->noCarrier();
                        return false;
                    }
                }

            }
        }

        if(firstPatternFindFlag && secondPatternFindFlag) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_1:Find patterns"));
#endif
            result = true;
            break;
        }
        if ((millis() - start) > fullTimeout) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_1:Timeout"));
#endif
            result = false;
            break;
        }

        if (((millis() - lastChar) > charTimeout) && lastChar != 0) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_1:Chartimeout"));
#endif
            result = false;
            break;
        }
    }
    responseBuffer->trim();
    return result;
}

void ATCommandExecutor::setSIMActionHandler(SIMActionHandler *action) {
    this->action = action;
}


bool ATCommandExecutor::wait(StringBuffer *responseBuffer, const char *firstPattern, 	const char *secondPattern, 	uint32_t fullTimeout, uint32_t charTimeout, bool blockSIMActionHandler) {
    return readAndCheck(responseBuffer, firstPattern, secondPattern, fullTimeout, charTimeout, blockSIMActionHandler);
}


uint8_t ATCommandExecutor::multiWait(const char *pattern1, const char *pattern2, const char *pattern3, const char *pattern4, uint32_t fullTimeout, uint32_t charTimeout ) {
    return multiWait(NULL, pattern1, pattern2, pattern3, pattern4, fullTimeout, charTimeout);
}


uint8_t ATCommandExecutor::multiWait(StringBuffer *responseBuffer, const char *pattern1, const char *pattern2, const char *pattern3, const char *pattern4, uint32_t fullTimeout, uint32_t charTimeout) {
    uint16_t pattern1Length = strlen(pattern1);
    uint16_t pattern2Length = strlen(pattern2);
    uint16_t pattern3Length = strlen(pattern3);
    uint16_t pattern4Length = strlen(pattern4);

    uint16_t pattern1Cursor = 0;
    uint16_t pattern2Cursor = 0;
    uint16_t pattern3Cursor = 0;
    uint16_t pattern4Cursor = 0;

    uint32_t start = millis();
    uint32_t lastChar = 0;

    while(true) {
        WDT::reset();
        while(hs->available()) {
            WDT::reset();
            char c = hs->read();
#ifdef DEBUG
            Serial.print(c);
#endif
            if(responseBuffer != NULL)
                responseBuffer->append(c);

            lastChar = millis();

            pattern1Cursor = (pattern1[pattern1Cursor] == c)? ++pattern1Cursor : 0;
            if(pattern1Cursor == pattern1Length) {
                return 1;
            }


            pattern2Cursor = (pattern2[pattern2Cursor] == c)? ++pattern2Cursor : 0;
            if(pattern2Cursor == pattern2Length) {
                return 2;
            }

            if(pattern3 != NULL) {
                pattern3Cursor = (pattern3[pattern3Cursor] == c)? ++pattern3Cursor : 0;
                if(pattern3Cursor == pattern3Length) {
                    return 3;
                }
            }

            if(pattern4 != NULL) {
                pattern4Cursor = (pattern4[pattern4Cursor] == c)? ++pattern4Cursor : 0;
                if(pattern4Cursor == pattern4Length) {
                    return 4;
                }
            }
        }

        if ((millis() - start) > fullTimeout) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_1:Timeout"));
#endif
            break;
        }

        if (((millis() - lastChar) > charTimeout) && lastChar != 0) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_1:Chartimeout"));
#endif
            break;
        }
    }

    return 0;
}








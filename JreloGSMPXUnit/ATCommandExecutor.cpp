#include <ATCommandExecutor.h>

ATCommandExecutor::ATCommandExecutor(HardwareSerial *hs) {
    this->hs = hs;
}

ATCommandExecutor::~ATCommandExecutor() {}

void ATCommandExecutor::send(const char *cmd) {
    int len = strlen_P(cmd);
    for (int i = 0; i < len; i++) {
        hs->write(pgm_read_byte_near(cmd + i));
    }
}

void ATCommandExecutor::send(StringBuffer *cmd) {
    while(1) {
        if(hs->availableForWrite()) {
            hs->write(cmd->toString());
            break;
        }
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
    }
}


bool ATCommandExecutor::sendAndCheck(StringBuffer *cmd, char *firstPattern, char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout) {
	return sendAndCheck(cmd, NULL, firstPattern, secondPattern, fullTimeout, charTimeout);
}


bool ATCommandExecutor::sendAndCheck(StringBuffer *cmd, StringBuffer *responseBuffer, char *firstPattern, char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout) {
    flush();
    send(cmd);
	
    if(firstPattern == NULL)
        return true;

    return readAndCheck(responseBuffer, firstPattern, secondPattern, fullTimeout, charTimeout);
}


bool ATCommandExecutor::sendAndCheck(const char *cmd, StringBuffer *responseBuffer, char *firstPattern, char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout) {
    flush();
    send(cmd);

    if(firstPattern == NULL)
        return true;

    return readAndCheck(responseBuffer, firstPattern, secondPattern, fullTimeout, charTimeout);
}


bool ATCommandExecutor::sendAndCheck(const char *cmd, char *firstPattern, char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout ) {
    return sendAndCheck(cmd, NULL, firstPattern, secondPattern, fullTimeout, charTimeout);
}


bool ATCommandExecutor::readAndCheck(StringBuffer *responseBuffer, char *firstPattern, char *secondPattern, uint32_t fullTimeout, uint32_t charTimeout) {
    delay(DELAY);
    
    uint16_t length = strlen(firstPattern);
    uint16_t lengthSP = strlen(secondPattern);
    uint16_t cursor = 0;
    uint16_t cursorSP = 0;
    uint32_t start = millis();
    uint32_t lastChar = 0;

    bool result = false;
    bool findPattern = false;
    bool findSecondPattern = secondPattern == NULL? true : false;
	
    while(true) {

        while(hs->available()) {

            char c = hs->read();
#ifdef DEBUG
            Serial.print(c);
#endif
            if(responseBuffer != NULL)
                responseBuffer->append(c);

            lastChar = millis();

            if(!findPattern) {
                cursor = (firstPattern[cursor] == c)? ++cursor : 0;
                if(cursor == length) {
                    findPattern = true;
                }
            } else if(secondPattern) {
                cursorSP = (secondPattern[cursorSP] == c)? ++cursorSP : 0;
                if(cursorSP == lengthSP) {
                    findSecondPattern = true;
                }
            }

        }

        if(findPattern && findSecondPattern) {
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

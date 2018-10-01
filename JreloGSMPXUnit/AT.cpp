#include <AT.h>
#include <avr/pgmspace.h>

AT::AT(HardwareSerial *hs) {
    this->hs = hs;
}

AT::~AT() {
}

void AT::sendAndWaitPM(const char *cmd, unsigned int time) {
    flush();
    sendPM(cmd);
    delay(time);
}

bool AT::sendAndCheckPM(const char *cmd, char *pattern, unsigned long timeout, unsigned long chartimeout) {
    flush();
    sendPM(cmd);
    delay(10);
    bool result = readAndCheck(pattern, timeout, chartimeout);
    flush();
    return result;
}

bool AT::sendAndCheckPM(const char *cmd, StringBuffer *sb, char *firstPattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout) {
    flush();
    sendPM(cmd);
    delay(10);
    bool result = readAndCheck(sb, firstPattern, secondPattern, timeout, chartimeout);
    flush();
    return result;
}

bool AT::sendAndCheck(char *cmd, StringBuffer *sb, char *firstPattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout) {
    flush();
    send(cmd);
    delay(10);
    bool result = readAndCheck(sb, firstPattern, secondPattern, timeout, chartimeout);
    flush();
    return result;
}

bool AT::sendAndCheck(char *cmd, char *pattern, unsigned long timeout, unsigned long chartimeout) {
    flush();
    send(cmd);
    delay(10);
    bool result = readAndCheck(pattern, timeout, chartimeout);
    flush();
    return result;
}

void AT::sendAndWait(char *cmd, unsigned int time) {
    flush();
    send(cmd);
    delay(time);
}

void AT::sendPM(const char *cmd) {
    int len = strlen_P(cmd);
    for (int i = 0; i < len; i++) {
        hs->write(pgm_read_byte_near(cmd + i));
    }
}

void AT::send(char *cmd) {

    while(1) {
        if(hs->availableForWrite()) {
            hs->write(cmd);
            break;
        }
    }
}

void AT::flush() {
    while(hs->available()) {
        int data = hs->read();
#ifdef DEBUG
        Serial.println(F("AT. Flush"));
        Serial.println((char)data);
        Serial.println(F("~~~~~~~~~~"));
#endif
    }
}

// 1
bool AT::readAndCheck(StringBuffer *sb, char *pattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout) {
    int length = strlen(pattern);
    int lengthSP = strlen(secondPattern);
    int cursor = 0;
    int cursorSP = 0;
    unsigned long start = millis();
    unsigned long lastChar = 0;

    bool result = false;
    bool findPattern = false;
    bool findSecondPattern = secondPattern == NULL? true : false;

    while(true) {

        while(hs->available()) {
            char c = hs->read();

            if(!sb->append(c)) {
                Serial.println(F("AT. Append error !"));
            }

            lastChar = millis();

            if(!findPattern) {
                cursor = (pattern[cursor] == c)? ++cursor : 0;
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
        if ((millis() - start) > timeout) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_1:Timeout"));
#endif
            result = false;
            break;
        }

        if (((millis() - lastChar) > chartimeout) && lastChar != 0) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_1:Chartimeout"));
#endif
            result = false;
            break;
        }
    }
    sb->trim();
    return result;
}

// 2
bool AT::readAndCheck(char *pattern, unsigned long timeout, unsigned long chartimeout) {
    bool result = false;
    int length = strlen(pattern);
    int cursor = 0;
    unsigned long start = millis();
    unsigned long lastChar = 0;

    while(true) {
        while (hs->available()) {

            char c = hs->read();

            lastChar = millis();
            cursor = (pattern[cursor] == c)? ++cursor : 0;
            if(cursor == length) {
                result = true;
                break;
            }
        }
        if(cursor == length) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_2:Find pattern"));
#endif
            break;
        }
        if ((millis() - start) > timeout) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_2:Timeout"));
#endif
            break;
        }

        if (((millis() - lastChar) > chartimeout) && lastChar != 0) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_2:Chartimeout"));
#endif
            break;
        }
    }
    return result;
}





bool AT::readAndCheck(String *str, char *pattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout) {
    int length = strlen(pattern);
    int lengthSP = strlen(secondPattern);
    int cursor = 0;
    int cursorSP = 0;
    unsigned long start = millis();
    unsigned long lastChar = 0;

    bool result = false;
    bool findPattern = false;
    bool findSecondPattern = secondPattern == NULL? true : false;

    while(true) {

        while(hs->available()) {
            char c = hs->read();
            (*str) += (char)c;

            lastChar = millis();

            if(!findPattern) {
                cursor = (pattern[cursor] == c)? ++cursor : 0;
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
        if ((millis() - start) > timeout) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_1:Timeout"));
#endif
            result = false;
            break;
        }

        if (((millis() - lastChar) > chartimeout) && lastChar != 0) {
#ifdef DEBUG
            Serial.println(F("AT. ReadAndCheck_1:Chartimeout"));
#endif
            result = false;
            break;
        }
    }
    str->trim();
    return result;
}


bool AT::sendAndCheck(char *cmd, String *str, char *firstPattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout) {
    flush();
    send(cmd);
    delay(25);
    bool result = readAndCheck(str, firstPattern, secondPattern, timeout, chartimeout);
    delay(25);
    flush();
    
    return result;
}

bool AT::sendAndCheckPM(const char *cmd, String *str, char *firstPattern, char *secondPattern, unsigned long timeout, unsigned long chartimeout) {
    flush();
    sendPM(cmd);
    delay(25);
    bool result = readAndCheck(str, firstPattern, secondPattern, timeout, chartimeout);
    delay(25);
    flush();
    
    return result;
}


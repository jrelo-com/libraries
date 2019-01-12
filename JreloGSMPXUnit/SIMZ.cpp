#include <SIMZ.h>

SIMZ::SIMZ() {}

SIMZ::~SIMZ() {}

ATCommandExecutor* SIMZ::getATCommandExecutor() {
    return atEx;
}

void SIMZ::setATCommandExecutor(ATCommandExecutor *atEx) {
    this->atEx = atEx;
    this->atEx->setSIMActionHandler(this);
}

void SIMZ::setStringBox(StringBox *stringBox) {
    this->stringBox = stringBox;
}

StringBox* SIMZ::getStringBox() {
    return stringBox;
}

void SIMZ::setDTMFActions(DTMFActions *actions) {
    this->actions = actions;
}

bool SIMZ::answerAnIncommingCall() {
    if(atEx->sendAndCheck(AT_COMMAND_31, AT_OK)) {
        return true;
    }
    return false;
}

bool SIMZ::disconnectExistingConnection() {
    return atEx->sendAndCheck(AT_COMMAND_32, AT_END_LINE);
}

bool SIMZ::checksPhoneNumber() {
    if(phoneNumbersStorage == NULL)
        return true;

    StringBuffer sb0 = StringBuffer(stringBox);
    if(atEx->wait(&sb0, AT_COMMAND_27_PART_1, AT_END_LINE, 10000, 10000, true)) {

        StringBuffer sb1 = StringBuffer(stringBox);
        phoneNumbersStorage->getPhoneNumbers(&sb1);

        char *temp = (char*)sb1.toString();
        char *part = strtok(temp, ";");

        uint8_t index = 0;
        while(part != NULL) {
            if(strstr(sb0.toString(), part)) {
                return true;
            }
            part = strtok(NULL, ";");
        }
        disconnectExistingConnection();
    }
    return false;
}

void SIMZ::ring() {
    bool checksPhoneNumberFlag = false;
    bool answerAnIncommingCallFlag = false;
    ringFlag = true;

    Serial.println(F("SIMZ. Ring ..."));

    while(ringFlag) {

        if(!checksPhoneNumberFlag && checksPhoneNumber()) {
            checksPhoneNumberFlag = true;
            if(answerAnIncommingCall()) {
                answerAnIncommingCallFlag = true;
            }
        }

        if(answerAnIncommingCallFlag) {
            StringBuffer sb = StringBuffer(stringBox);
            if(atEx->wait(&sb, AT_COMMAND_28_PART_1, AT_END_LINE, 10000, 10000, true)) {
                dtfmActionExec(&sb);
                disconnectExistingConnection();
                return;
            }
        }
    }

    disconnectExistingConnection();
}

void SIMZ::dtfmActionExec(StringBuffer *stringBuffer) {
    char temp = stringBuffer->toString()[stringBuffer->size()-3];
    int dtfmNumber = temp - '0';

    switch(dtfmNumber) {
    case 0 :
        actions->zero();
        break;
    case 1 :
        actions->one();
        break;
    case 2 :
        actions->two();
        break;
    case 3 :
        actions->three();
        break;
    case 4 :
        actions->four();
        break;
    case 5 :
        actions->five();
        break;
    case 6 :
        actions->six();
        break;
    case 7 :
        actions->seven();
        break;
    case 8:
        actions->eight();
        break;
    case 9:
        actions->nine();
    };
}

void SIMZ::noCarrier() {
    Serial.println(F("SIMZ. Disconnect existing connection."));
    ringFlag = false;
}

bool SIMZ::init() {
    if(!atEx->sendAndCheck(AT_COMMAND_27, AT_OK)) {
        Serial.println(F("SIMZ. Error 0"));
        return false;
    }
    if(actions != NULL) {
        if(!atEx->sendAndCheck(AT_COMMAND_28, AT_OK)) {
            Serial.println(F("SIMZ. Error 1"));
            return false;
        }
    }
    if(!atEx->sendAndCheck(AT_COMMAND_35, AT_OK)) {
        Serial.println(F("SIMZ. Error 2"));
        return false;
    }
    return true;
}

void SIMZ::update() {
    if(!initFlag) {
        init();
        initFlag = true;
    }
}

void SIMZ::setPhoneNumbersStorage(PhoneNumbersStorage *phoneNumbersStorage) {
    this->phoneNumbersStorage = phoneNumbersStorage;
}

OUTGOING_CALL_RESULT SIMZ::outgoingCall(const char *phoneNumber) {

    StringBuffer sb = StringBuffer(stringBox);
    sb.appendString(AT_COMMAND_33);
    sb.appendString(phoneNumber);
    sb.appendString(";\r\n");

    if(!atEx->sendAndCheck(&sb, AT_OK)) {
        Serial.println(F("SIMZ. Error 3"));
        return OCR_FAIL;
    }

    switch(atEx->multiWait(AT_NO_CARRIER, AT_BUSY, AT_NO_ANSWER, NULL, 70000, 70000)) {
    case 0 :
        return OCR_FAIL;
    case 1 :
        return OCR_OK;
    case 2 :
        return OCR_BUSY;
    case 3 :
        return OCR_NO_ANSWER;
    default:
        return OCR_FAIL;
    }

}

bool SIMZ::enableIncomingCalls() {
    Serial.println(F("SIMZ. Incoming calls are enabled"));
    return atEx->sendAndCheck(AT_COMMAND_29, AT_OK);
}

bool SIMZ::disableIncomingCalls() {
    Serial.println(F("SIMZ. Incoming calls are disabled"));
    return atEx->sendAndCheck(AT_COMMAND_30, AT_OK);
}

bool SIMZ::sendSMS(const char *phoneNumber, const char *text) {
    StringBuffer sb = StringBuffer(stringBox);
    sb.appendString(AT_COMMAND_34);
    sb.appendString("=\"");
    sb.appendString(phoneNumber);
    sb.appendString("\"\r\n");

    if(!atEx->sendAndCheck(&sb, ">", NULL, 10000, 10000)) {
        return false;
    }

    sb.clear();
    sb.appendString(text);
    sb.append(26);

    Serial.println(F("SIMZ. Send sms..."));
    return atEx->sendAndCheck(&sb, AT_OK, NULL, 15000, 15000);
}


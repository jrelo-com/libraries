/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <ATCommandExecutor.h>
#include <StringBox.h>
#include <DTMFActions.h>
#include <SIMActionHandler.h>
#include <PhoneNumbersStorage.h>

enum OUTGOING_CALL_RESULT {
    OCR_EMPTY,
    OCR_FAIL,
    OCR_OK,
    OCR_BUSY,
    OCR_NO_ANSWER
};

class SIMZ : public SIMActionHandler {

    private :

        PhoneNumbersStorage *phoneNumbersStorage = NULL;
        ATCommandExecutor *atEx = NULL;
        StringBox *stringBox = NULL;
        DTMFActions *actions = NULL;
        bool ringFlag = false;
        bool initFlag = false;

        void dtfmActionExec(StringBuffer *stringBuffer);
        bool answerAnIncommingCall();
        bool disconnectExistingConnection();
        bool checksPhoneNumber();
        bool init();

    public :

        SIMZ();
        ~SIMZ();

        void setATCommandExecutor(ATCommandExecutor *atEx);
        ATCommandExecutor* getATCommandExecutor();
        void setStringBox(StringBox *stringBox);
        StringBox* getStringBox();
        void setDTMFActions(DTMFActions *actions);
        void setPhoneNumbersStorage(PhoneNumbersStorage *phoneNumbersStorage);
        void update();

        bool sendSMS(const char *phoneNumber, const char *text);
        OUTGOING_CALL_RESULT outgoingCall(const char *phoneNumber);

        bool enableIncomingCalls();
        bool disableIncomingCalls();

        void ring(); 		//override
        void noCarrier(); 	//override

};

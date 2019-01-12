/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <SIMZ.h>

class OutgoingCallModule : public Module {

    private :

        SIMZ *simz = NULL;
        bool needCallAction = false;
        char phoneNumber[14] = {0};
        OUTGOING_CALL_RESULT status = OCR_EMPTY;

    public :

        OutgoingCallModule(const char *key, SIMZ *simz);
        ~OutgoingCallModule();
        void update();
        void inputData(const char *data);
        void outputData(Pipe *pipe);

};

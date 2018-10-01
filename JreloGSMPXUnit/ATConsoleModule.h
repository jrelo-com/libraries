#pragma once
#include <Arduino.h>
#include <Module.h>
#include <AT.h>
#include <StringBuffer.h>
#include <SIM900i2.h>

class ATConsoleModule : public Module {

    private :

        StringBuffer *inBuffer = NULL;
        StringBuffer *outBuffer = NULL;
        StringBox *box = NULL;
        AT *at = NULL;
        bool needActionFlag = false;

    public :

        ATConsoleModule(char *key, SIM900i2 *sim);
        ~ATConsoleModule();
        void update();
        void inputData(char *data);
        void outputData(Pipe *pipe);

};


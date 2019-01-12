/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <SIMZ.h>
#include <TypeConverter.h>

class SendSMSModule : public Module {

    private :

        SIMZ *simz = NULL;
        uint8_t counter = 0;

    public :

        SendSMSModule(const char *key, SIMZ *simz);
        ~SendSMSModule();
        void update();
        void inputData(const char *data);
        void outputData(Pipe *pipe);

};

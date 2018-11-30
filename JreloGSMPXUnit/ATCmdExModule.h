/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 2.1.0
 * */
 
#pragma once
#include <Arduino.h>
#include <Module.h>
#include <ATCommandExecutor.h>
#include <StringBufferUtils.h>
#include <StringBuffer.h>
#include <ATCommands.h>


class ATCmdExModule : public Module {

    private :
		StringBox *stringBox = NULL;
        StringBuffer *inputBuffer = NULL;
        StringBuffer *outputBuffer = NULL;
        ATCommandExecutor *atEx = NULL;
        bool needActionFlag = false;

    public :

        ATCmdExModule(char *key, ATCommandExecutor *atEx, StringBox *stringBox);
        ~ATCmdExModule();
        void update();
        void inputData(char *data);
        void outputData(Pipe *pipe);

};


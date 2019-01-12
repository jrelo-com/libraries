/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 2.1.2
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <ATCommandExecutor.h>
#include <StringBufferUtils.h>
#include <StringBuffer.h>


class ATCommandExecutorModule : public Module {

    private :
        StringBox *stringBox = NULL;
        StringBuffer *inputBuffer = NULL;
        StringBuffer *outputBuffer = NULL;
        ATCommandExecutor *atEx = NULL;
        bool needActionFlag = false;

    public :

        ATCommandExecutorModule(const char *key, ATCommandExecutor *atEx, StringBox *stringBox);
        ~ATCommandExecutorModule();
        void update();
        void inputData(const char *data);
        void outputData(Pipe *pipe);

};


/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <LcdAdapter.h>

class LcdModule : public Module {

    private :

        LcdAdapter *lcdAdapter = NULL;
        int row = 0;

    public :

        LcdModule(char *key, LcdAdapter *lcdAdapter, int row) ;
        ~LcdModule();
        void update();
        void inputData(char *data);
        void outputData(Pipe *pipe);

};

/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>

class RelayModule : public Module {

    private :

        int pin;
        bool value = false;
        bool inversion = true;
        bool init = false;

    public :

        RelayModule(const char *key, int pin, bool inversion = true);
        ~RelayModule();
        
        void setValue(bool flag);
        bool getValue();
         
        void inputData(const char *data);
        void outputData(Pipe *pipe);
        void update();


};


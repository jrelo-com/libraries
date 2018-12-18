/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <EEPROM.h>

class RelaySSModule : public Module {

    private :

        int pin;
        int address;
        bool value = false;
        bool inversion = true;
        bool init = false;

        void loadValue();
        void saveValue();

    public :

        RelaySSModule(const char *key, int pin, int address, bool inversion = true);
        ~RelaySSModule();
        
        void setValue(bool flag);
        bool getValue();
         
        void inputData(const char *data);
        void outputData(Pipe *pipe);
        void update();
        
};


#pragma once
#include <Arduino.h>
#include <Module.h>
#include <EEPROM.h>

class RelaySSModule : public Module {

    private :

        int pin;
        int firstAddress;
        bool value = false;
        bool inversion = true;
        bool init = false;

        void loadValue();
        void saveValue();

    public :

        RelaySSModule(char *key, int pin, int firstAddressbool, bool inversion = true);
        ~RelaySSModule();
        
        void setValue(bool flag);
        bool getValue();
         
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();
        
};


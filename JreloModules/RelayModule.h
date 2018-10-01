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

        RelayModule(char *key, int pin, bool inversion = true);
        ~RelayModule();
        
        void setValue(bool flag);
        bool getValue();
         
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();


};


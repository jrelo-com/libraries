/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <TypeConverter.h>

class MultiRelayModule : public Module {

    private :

        int *ports;
        int count;
        bool inversion = true;
        bool init = false;

    public :

        MultiRelayModule(char *key, int *ports, int count, bool inversion = true);
        ~MultiRelayModule();
        
        bool getValue(int port);
        bool getValueByIndex(int index);
        void setValue(int port, bool value);
        void setValueByIndex(int index, bool value);
        
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();


};


/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <TypeConverter.h>
#include <EEPROM.h>

class MultiRelaySSModule : public Module {

    private :

        int *ports;
        int count;
        int address;
        bool inversion = true;
        bool init = false;

		void loadValue();
		void saveValue();

    public :

        MultiRelaySSModule(char *key, int *ports, int count, int address, bool inversion = true);
        ~MultiRelaySSModule();
        
        bool getValue(int port);
        bool getValueByIndex(int index);
        void setValue(int port, bool value);
        void setValueByIndex(int index, bool value);
        
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();

};


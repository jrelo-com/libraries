/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <SimpleTimer.h>
#include <TypeConverter.h>

class AnalogReadModule : public Module {

    private :

        int port = 0;
        SimpleTimer timer = SimpleTimer(10000);

    public :

        AnalogReadModule(char *key, int port);
        ~AnalogReadModule();
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();

};

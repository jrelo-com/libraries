/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <DallasTemperature.h>
#include <SimpleTimer.h>
#include <TypeConverter.h>

class DallasTemperatureModule : public Module {

    private :

        DallasTemperature *sensors = NULL;
        SimpleTimer timer = SimpleTimer(60000);
        int index = 0;

    public :

        DallasTemperatureModule(const char *key, DallasTemperature *sensors, int index);
        ~DallasTemperatureModule();
        void inputData(const char *data);
        void outputData(Pipe *pipe);
        void update();

};

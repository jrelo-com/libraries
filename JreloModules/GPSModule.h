/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <SimpleTimer.h>
#include <TinyGPS.h>

class GPSModule : public Module {

    private:

        SimpleTimer timer = SimpleTimer(15000);
        TinyGPS *gps = NULL;
        HardwareSerial *serial = NULL;
        void read(unsigned long ms);

    public :

        GPSModule(char *key, TinyGPS *gps, HardwareSerial *serial);
        ~GPSModule();
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();

};

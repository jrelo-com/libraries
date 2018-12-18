/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 2.0.1
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <SimpleTimer.h>
#include <LocationProvider.h>

class GPSModule : public Module {

    private:

        SimpleTimer timer = SimpleTimer(30000);
		LocationProvider *locationProvider = NULL;

    public :

        GPSModule(const char *key, LocationProvider *locationProvider);
        ~GPSModule();
        void inputData(const char *data);
        void outputData(Pipe *pipe);
        void update();

};

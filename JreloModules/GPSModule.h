/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 2.0.0
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

        GPSModule(char *key, LocationProvider *locationProvider);
        ~GPSModule();
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();

};

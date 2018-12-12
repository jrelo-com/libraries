/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <LocationProvider.h>
#include <TinyGPS.h>

class TinyGPSLocationProvider : public LocationProvider {

    private:
    
		TinyGPS *gps = NULL;
        HardwareSerial *serial = NULL;
		float location[2] = {0};
		
		void read(unsigned long ms);

    public :

        TinyGPSLocationProvider(TinyGPS *gps, HardwareSerial *serial);
        ~TinyGPSLocationProvider();
        float* getLocation();

};

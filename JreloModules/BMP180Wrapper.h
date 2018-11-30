/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <SFE_BMP180.h>
#include <SimpleTimer.h>

class BMP180Wrapper {

    private :
    
        SFE_BMP180 *bmp180 = NULL;
        SimpleTimer timer = SimpleTimer(50000);
		double temperature;
		double pressure;
		void process();
		
    public :
    
        BMP180Wrapper(SFE_BMP180 *bmp180);
        ~BMP180Wrapper();
		double getTemperature();
		double getPressure();
		void update();
		void begin();

};

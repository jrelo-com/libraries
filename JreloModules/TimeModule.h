/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <TypeConverter.h>
#include <SimpleTimer.h>
#include <time.h>
#include <TimeProvider.h>

class TimeModule : public Module, public TimeProvider {

	private :
	
		unsigned long difference = 0;
        unsigned long timeFromService = 0;
        int timeZoneOffset = 0;
        bool readyFlag = false;
        SimpleTimer initTimer = SimpleTimer(60000);
        SimpleTimer updateTimer = SimpleTimer(1000);
		struct tm* tm = NULL;
					
	public :
	
		TimeModule(int timeZoneOffset = 0);
        ~TimeModule();
        
        struct tm* getTime();
		bool isReady();
		int getSec();
		int getMin();
		int getHour();
		int getDay();
		int getWDay();
		int getMonth();
		int getYear();
 
        void inputData(const char *data);
        void outputData(Pipe *pipe);
        void update();
	
};

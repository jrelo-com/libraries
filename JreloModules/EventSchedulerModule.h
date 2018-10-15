#pragma once
#include <Arduino.h>
#include <EEPROM.h>
#include <Module.h>
#include <TimeProvider.h>
#include <SimpleTimer.h>
#include <TypeConverter.h>

class EventSchedulerModule : public Module {

	private :
		
		TimeProvider *timeProvider = NULL;
		int firstAddress = 0;
		
		SimpleTimer timer = SimpleTimer(1000);
		byte sec = 0;
		byte min = 0;
		byte hour = 0;
		bool week[7] = {0}; 
		bool enable = false;
		
		bool initFlag = false;
		bool eventFlag = false;
		bool bounceFlag = false;
		
		void init();
			
	public :
	
		EventSchedulerModule(char *key, TimeProvider *timeProvider, int firstAddress);
        ~EventSchedulerModule();
        
        void reset();
        bool event();
        
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();
	
};
#pragma once
#include <Arduino.h>
#include <EEPROM.h>
#include <Module.h>
#include <TimeProvider.h>
#include <SimpleTimer.h>
#include <TypeConverter.h>

class WorkSchedulerModule : public Module {

	private :
		
		TimeProvider *timeProvider = NULL;
		int firstAddress = 0;
		
		SimpleTimer timer = SimpleTimer(1000);
		
		byte startSec = 0;
		byte startMin = 0;
		byte startHour = 0;
		byte endSec = 0;
		byte endMin = 0;
		byte endHour = 0;
		bool week[7] = {0}; 
		bool enable = false;
		
		bool initFlag = false;
		bool eventFlag = false;
		
		void init();
			
	public :
	
		WorkSchedulerModule(char *key, TimeProvider *timeProvider, int firstAddress);
        ~WorkSchedulerModule();
        
        bool event();
                
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();
	
};

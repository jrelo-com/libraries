#pragma once
#include <time.h>
#include <Arduino.h>

class TimeProvider {
	
	public :
	
		virtual int getSec() 	= 0;
		virtual int getMin() 	= 0;
		virtual int getHour()	= 0;
		virtual int getDay() 	= 0;
		virtual int getWDay() 	= 0;
		virtual int getMonth() 	= 0;
		virtual int getYear() 	= 0;
	
};

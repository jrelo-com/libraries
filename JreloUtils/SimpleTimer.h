#pragma once
#include <Arduino.h>


class SimpleTimer {

  private :

    unsigned long lastEvent = 0;
    unsigned long period = 0;
    bool workFlag;
    bool interval;

  public :
    /*
     * period - time
     * interval - loop or timer
     * starFlag - start the timer after creating an instance 
     * */
    SimpleTimer(unsigned long period, bool interval = true, bool startFlag = true);
    
    ~SimpleTimer() ;

    bool event();
    
    void start();
    
    void stop();
    
    bool isWorking();
    
    void setPeriod(unsigned long  period);
	
	unsigned long getPeriod();
	
	void reset();
	
	void setInterval(bool flag);
	
	bool isInterval();
    
};


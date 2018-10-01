#include <SimpleTimer.h>


SimpleTimer::SimpleTimer(unsigned long period, bool interval, bool startFlag){
	this->period = period;
	this->interval = interval;
	
	if(startFlag)
		start();
}

SimpleTimer::~SimpleTimer() {}

bool SimpleTimer::event() {

    if(!workFlag)
        return false;

    bool result = false;
    unsigned long now = millis();

    if ( (now - lastEvent) > period) {
        result = true;
        lastEvent = now;
        
        if(!interval)
			stop();
    }

    return result;
}

void SimpleTimer::start() {
	lastEvent = millis();
    workFlag = true;
}

void SimpleTimer::stop() {
    workFlag = false;
}

bool SimpleTimer::isWorking() {
    return workFlag;
}

void SimpleTimer::setPeriod(unsigned long  period) {
    this->period = period;
}

unsigned long SimpleTimer::getPeriod() {
    return period;
}

void SimpleTimer::reset(){
	lastEvent = millis();
}

void SimpleTimer::setInterval(bool flag){
	interval = flag;
}

bool SimpleTimer::isInterval(){
	return interval;
}
    

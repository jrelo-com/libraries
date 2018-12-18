#include <TimeModule.h>


TimeModule::TimeModule(int timeZoneOffset) : Module("$ts") {
    setFeedback(false);
    this->timeZoneOffset = timeZoneOffset * 3600;
}

TimeModule::~TimeModule() {}

void TimeModule::inputData(const char *data) {
    readyFlag = true;

    timeFromService = TypeConverter::charArrayToUnsignedLong(data);
    
	this->timeFromService += timeZoneOffset;
}

void TimeModule::outputData(Pipe *pipe) {
    pipe->push('0');
    difference = millis() / 1000;
}

void TimeModule::update() {

    if(!readyFlag) {
        if(initTimer.event()) {
            inform();
		}
    } else {
        if(updateTimer.event()) {
            time_t time = timeFromService - difference + (millis()/1000) - UNIX_OFFSET;
            tm = gmtime(&time);
        }
    }
}

struct tm* TimeModule::getTime(){
	return tm;
}

bool TimeModule::isReady() {
    return readyFlag;
}

int TimeModule::getSec() {
    return readyFlag? tm->tm_sec : -1;
}

int TimeModule::getMin() {
    return readyFlag? tm->tm_min : -1;
}

int TimeModule::getHour() {
    return readyFlag? tm->tm_hour : -1;
}

int TimeModule::getDay() {
    return readyFlag? tm->tm_mday : -1;
}

int TimeModule::getWDay() {
    return readyFlag? tm->tm_wday : -1;
}

int TimeModule::getMonth() {
    return readyFlag? tm->tm_mon  : -1;
}

int TimeModule::getYear() {
    return readyFlag? tm->tm_year + 1900: -1;
}

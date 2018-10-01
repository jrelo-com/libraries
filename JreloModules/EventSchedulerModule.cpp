#include <EventSchedulerModule.h>

EventSchedulerModule::EventSchedulerModule(char *key, TimeProvider *timeProvider, int firstAddress) : Module(key) {
    this->timeProvider = timeProvider;
    this->firstAddress = firstAddress;
}

EventSchedulerModule::~EventSchedulerModule() {}

bool EventSchedulerModule::event() {
    return eventFlag;
}

void EventSchedulerModule::init() {

    hour = EEPROM.read(firstAddress);
    min  = EEPROM.read(firstAddress + 1);
    sec  = EEPROM.read(firstAddress + 2);
    byte config = EEPROM.read(firstAddress + 3);

    week[0] = config & (1 << 0);
    week[1] = config & (1 << 1);
    week[2] = config & (1 << 2);
    week[3] = config & (1 << 3);
    week[4] = config & (1 << 4);
    week[5] = config & (1 << 5);
    week[6] = config & (1 << 6);
    enable  = !(config & (1 << 7));
}

void EventSchedulerModule::reset() {
    eventFlag = false;
}

void EventSchedulerModule::inputData(char *data) {

    char *temp = strtok(data, ":");
    hour = (byte)TypeConverter::charArrayToInt(temp);

    temp = strtok(NULL, ":");
    min = (byte)TypeConverter::charArrayToInt(temp);

    temp = strtok(NULL, ":");
    sec = (byte)TypeConverter::charArrayToInt(temp);

    temp = strtok(NULL, ":");
    byte config = (byte)TypeConverter::charArrayToInt(temp);

	week[0] = (config >> 0) & 1;
	week[1] = (config >> 1) & 1;
	week[2] = (config >> 2) & 1;
	week[3] = (config >> 3) & 1;
	week[4] = (config >> 4) & 1;
	week[5] = (config >> 5) & 1;
	week[6] = (config >> 6) & 1;
	enable  = (config >> 7) & 1;

	config ^= 1 << 7;

    EEPROM.write(firstAddress, hour);
    EEPROM.write(firstAddress + 1, min);
    EEPROM.write(firstAddress + 2, sec);
    EEPROM.write(firstAddress + 3, config);
}

void EventSchedulerModule::outputData(Pipe *pipe) {
    pipe->push('"');

    char temp[4] = {0};
    TypeConverter::intToCharArray(temp, hour == 255? -1 : hour);
    pipe->push(temp);
    pipe->push(":");

    TypeConverter::intToCharArray(temp, min == 255? -1 : min);
    pipe->push(temp);
    pipe->push(":");

    TypeConverter::intToCharArray(temp, sec == 255? -1 : sec);
    pipe->push(temp);
    pipe->push(":");

    byte config = 0;
    config ^= week[0] << 0;
    config ^= week[1] << 1;
    config ^= week[2] << 2;
    config ^= week[3] << 3;
    config ^= week[4] << 4;
    config ^= week[5] << 5;
    config ^= week[6] << 6;
    config ^= enable  << 7;

    TypeConverter::intToCharArray(temp, config);
    pipe->push(temp);

    pipe->push('"');
}

void EventSchedulerModule::update() {

    if(initFlag) {			
        if(enable && !eventFlag && timer.event()) {
            if(timeProvider->getMonth() < 0)
                return;

            int sec = timeProvider->getSec();
            int min = timeProvider->getMin();
            int hour = timeProvider->getHour();
            int wDay = timeProvider->getWDay();

			if((bounceFlag && sec > this->sec + 10) || this->sec == 255){
				bounceFlag = false;
			}

			if(bounceFlag)
				return;


            if( ((sec >= this->sec && sec <= this->sec + 10) || this->sec == 255) && 
				((min == this->min) || this->min == 255)&& 
				((hour == this->hour) || this->hour == 255) && 
				(week[wDay]) ) {
				
				bounceFlag = true;	
                eventFlag = true;
            }
        }
    } else {
        init();
        initFlag = true;
    }
}

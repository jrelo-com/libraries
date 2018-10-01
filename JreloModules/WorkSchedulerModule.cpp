#include <WorkSchedulerModule.h>

WorkSchedulerModule::WorkSchedulerModule(char *key, TimeProvider *timeProvider, int firstAddress) : Module(key) {
    this->timeProvider = timeProvider;
    this->firstAddress = firstAddress;
}

WorkSchedulerModule::~WorkSchedulerModule() {}

bool WorkSchedulerModule::event() {
    return enable && eventFlag;
}

void WorkSchedulerModule::init() {

    startHour   = EEPROM.read(firstAddress);
    startMin    = EEPROM.read(firstAddress + 1);
    startSec    = EEPROM.read(firstAddress + 2);
    endHour	    = EEPROM.read(firstAddress + 3);
    endMin      = EEPROM.read(firstAddress + 4);
    endSec      = EEPROM.read(firstAddress + 5);
    byte config = EEPROM.read(firstAddress + 6);

    week[0] = config & (1 << 0);
    week[1] = config & (1 << 1);
    week[2] = config & (1 << 2);
    week[3] = config & (1 << 3);
    week[4] = config & (1 << 4);
    week[5] = config & (1 << 5);
    week[6] = config & (1 << 6);
    enable  = !(config & (1 << 7));
}


void WorkSchedulerModule::inputData(char *data) {

    char *temp = strtok(data, ":");
    startHour = (byte)TypeConverter::charArrayToInt(temp);

    temp = strtok(NULL, ":");
    startMin = (byte)TypeConverter::charArrayToInt(temp);

    temp = strtok(NULL, ":");
    startSec = (byte)TypeConverter::charArrayToInt(temp);
    
    temp = strtok(NULL, ":");
    endHour = (byte)TypeConverter::charArrayToInt(temp);

    temp = strtok(NULL, ":");
    endMin = (byte)TypeConverter::charArrayToInt(temp);

    temp = strtok(NULL, ":");
    endSec = (byte)TypeConverter::charArrayToInt(temp);

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
	
    EEPROM.write(firstAddress,     startHour);
    EEPROM.write(firstAddress + 1, startMin);
    EEPROM.write(firstAddress + 2, startSec);
    EEPROM.write(firstAddress + 3, endHour);
    EEPROM.write(firstAddress + 4, endMin);
    EEPROM.write(firstAddress + 5, endSec);
    EEPROM.write(firstAddress + 6, config);
}

void WorkSchedulerModule::outputData(Pipe *pipe) {
    pipe->push('"');

    char temp[4] = {0};
    TypeConverter::intToCharArray(temp, startHour);
    pipe->push(temp);
    pipe->push(":");

    TypeConverter::intToCharArray(temp, startMin);
    pipe->push(temp);
    pipe->push(":");

    TypeConverter::intToCharArray(temp, startSec);
    pipe->push(temp);
    pipe->push(":");
    
    TypeConverter::intToCharArray(temp, endHour);
    pipe->push(temp);
    pipe->push(":");

    TypeConverter::intToCharArray(temp, endMin);
    pipe->push(temp);
    pipe->push(":");

    TypeConverter::intToCharArray(temp, endSec);
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

void WorkSchedulerModule::update() {

    if(initFlag) {			
        if(enable &&  timer.event()) {
			            
            if(timeProvider->getMonth() == 0)
                return;

            int sec = timeProvider->getSec();
            int min = timeProvider->getMin();
            int hour = timeProvider->getHour();
            int wDay = timeProvider->getWDay();       
                        
            long now   = ((long)hour      * 3600) + (min      * 60) + sec;
            long start = ((long)startHour * 3600) + (startMin * 60) + startSec;
            long end   = ((long)endHour   * 3600) + (endMin   * 60) + endSec;

			if( (start  <= now  && now  < end  ) &&  week[wDay] ) {
				eventFlag = true;
			} else {
				eventFlag = false;
			}
     
        }
    } else {
        init();
        initFlag = true;
    }
}

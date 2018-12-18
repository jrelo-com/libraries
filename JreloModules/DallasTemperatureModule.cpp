#include <DallasTemperatureModule.h>


DallasTemperatureModule::DallasTemperatureModule(const char *key, DallasTemperature *sensors, int index) : Module(key) {
    this->sensors = sensors;
    this->index = index;
}

void DallasTemperatureModule::update() {
    if(timer.event()) {
        inform();
    }
}

DallasTemperatureModule::~DallasTemperatureModule() {}

void DallasTemperatureModule::inputData(const char *data) {}

void DallasTemperatureModule::outputData(Pipe *pipe) {
	sensors->requestTemperatures();
    char temp[8];
    TypeConverter::floatToCharArray(temp, sensors->getTempCByIndex(index), 7, 2);
		
    pipe->push(temp);
}


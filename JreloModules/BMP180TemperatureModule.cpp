#include <BMP180TemperatureModule.h>

BMP180TemperatureModule::BMP180TemperatureModule(const char *key, BMP180Wrapper *bmp180) : Module(key) {
    this->bmp180 = bmp180;
}

void BMP180TemperatureModule::update() {
	bmp180->update();
	
    if(timer.event()) {
        inform();
    }
}

void BMP180TemperatureModule::inputData(const char *data) {}

void BMP180TemperatureModule::outputData(Pipe *pipe) {
	
	char temp[10];
		
    TypeConverter::floatToCharArray(temp, (float)bmp180->getTemperature(), 6, 2);
		
    pipe->push(temp);
}

BMP180TemperatureModule::~BMP180TemperatureModule() {}

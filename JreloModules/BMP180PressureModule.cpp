#include <BMP180PressureModule.h>

BMP180PressureModule::BMP180PressureModule(char *key, BMP180Wrapper *bmp180) : Module(key) {
    this->bmp180 = bmp180;
}

void BMP180PressureModule::update() {
	bmp180->update();
	
    if(timer.event()) {
        inform();
    }
}

void BMP180PressureModule::inputData(char *data) {}

void BMP180PressureModule::outputData(Pipe *pipe) {
	
	char temp[10];
		
    TypeConverter::floatToCharArray(temp, (float)bmp180->getPressure(), 8, 2);
		
    pipe->push(temp);
}

BMP180PressureModule::~BMP180PressureModule() {}

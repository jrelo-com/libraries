#include <AnalogReadModule.h>

AnalogReadModule::AnalogReadModule(char *key, int port) : Module(key) {
    this->port = port;
}

AnalogReadModule::~AnalogReadModule(){}

void AnalogReadModule::update() {
    if(timer.event())
        inform();
}

void AnalogReadModule::inputData(char *data) {}

void AnalogReadModule::outputData(Pipe *pipe) {
	
	float v = 5 * analogRead(port) / 1024.0;
    char temp[5];
    TypeConverter::floatToCharArray(temp, v, 4, 2);
    
	pipe->push(temp);
}

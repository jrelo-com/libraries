#include <LifetimeModule.h>

LifetimeModule::LifetimeModule(char *key) : Module(key) {}

LifetimeModule::~LifetimeModule() {}

void LifetimeModule::update() {
    if(timer.event()) {
        inform();
    }
}

void LifetimeModule::inputData(char *data) {}

void LifetimeModule::outputData(Pipe *pipe) {
	
	char value[11];
	TypeConverter::unsignedLongToCharArray(value, millis());
	
	pipe->push(value);
}

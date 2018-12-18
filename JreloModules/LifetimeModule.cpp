#include <LifetimeModule.h>

LifetimeModule::LifetimeModule(const char *key) : Module(key) {}

LifetimeModule::~LifetimeModule() {}

void LifetimeModule::update() {
    if(timer.event()) {
        inform();
    }
}

void LifetimeModule::inputData(const char *data) {}

void LifetimeModule::outputData(Pipe *pipe) {
	
	char value[11];
	TypeConverter::unsignedLongToCharArray(value, millis());
	
	pipe->push(value);
}

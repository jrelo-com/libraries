#include <RelayModule.h>

RelayModule::RelayModule(char *key, int pin, bool inversion) : Module(key) {
    this->pin = pin;
    this->inversion = inversion;
}

void RelayModule::update() {
	if(init)
		return;
		
	init = true;
	pinMode(pin, OUTPUT);
    digitalWrite(pin, inversion?!value:value);
}

RelayModule::~RelayModule() {}

void RelayModule::inputData(char *data) {
    this->value = data && strcmp(data, "true") == 0;
    digitalWrite(pin, inversion?!value:value);
}

void RelayModule::outputData(Pipe *pipe) {
    if(value)
        pipe->push("true");
    else
        pipe->push("false");
}

void RelayModule::setValue(bool flag) {
	value = flag;
	digitalWrite(pin, inversion?!value:value);
	inform();
}

bool RelayModule::getValue() {
	return value;
}

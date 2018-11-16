#include <RelaySSModule.h>

RelaySSModule::RelaySSModule(char *key, int pin, int addressbool, bool inversion) : Module(key) {
    this->pin = pin;
    this->inversion = inversion;
    this->address = address;
    loadValue();
}

void RelaySSModule::update() {
	if(init)
		return;
		
	init = true;
	pinMode(pin, OUTPUT);
    digitalWrite(pin, inversion?!value:value);
}

RelaySSModule::~RelaySSModule() {}

void RelaySSModule::inputData(char *data) {
    this->value = data && strcmp(data, "true") == 0;
    digitalWrite(pin, inversion?!value:value);
	saveValue();
}

void RelaySSModule::outputData(Pipe *pipe) {
    if(value)
        pipe->push("true");
    else
        pipe->push("false");
}

void RelaySSModule::setValue(bool flag) {
	value = flag;
	digitalWrite(pin, inversion?!value:value);
	saveValue();
	inform();
}

bool RelaySSModule::getValue() {
	return value;
}

void RelaySSModule::loadValue(){
	byte valueFromMemory = EEPROM.read(this->address);
	if(valueFromMemory == 255){
		this->value = false;
		digitalWrite(pin, inversion?!value:value);
	} else {
		this->value = true;
		digitalWrite(pin, inversion?!value:value);
	}
}

void RelaySSModule::saveValue(){
	if(this->value){
		EEPROM.write(this->address, 0);
	} else {
		EEPROM.write(this->address, 255);
	}
}

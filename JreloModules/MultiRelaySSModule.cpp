#include <MultiRelaySSModule.h>

MultiRelaySSModule::MultiRelaySSModule(const char *key, int *ports, int count, int address, bool inversion) : Module(key) {
    this->ports = ports;
    this->count = count;
    this->inversion = inversion;
    this->address = address;
}

void MultiRelaySSModule::inputData(const char *data) {
    int val = atoi(data);

    for(int i=0; i < count; i++) {
        bool v = (val >> i) & 1;
        digitalWrite(ports[i], inversion?!v:v);
    }

    saveValue();
}

void MultiRelaySSModule::outputData(Pipe *pipe) {
    int val = 0;
    for(int i=0; i < count; i++) {
        bool v = digitalRead(ports[i]);
        val ^= (inversion?!v:v) << i;
    }

    char temp[5] = {0};
    TypeConverter::intToCharArray(temp, val);
    pipe->push(temp);
}

void MultiRelaySSModule::update() {
    if(init)
        return;

    init=true;
    for(int i=0; i < count; i++) {
        pinMode(ports[i], 1);
        digitalWrite(ports[i], inversion?1:0);
    }
    
    loadValue();
}

MultiRelaySSModule::~MultiRelaySSModule() {}

bool MultiRelaySSModule::getValue(int port) {
    bool v = digitalRead(port);
    return inversion?!v:v;
}

void MultiRelaySSModule::setValue(int port, bool value) {
    digitalWrite(port, inversion?!value:value);
    inform();
    saveValue();
}

bool MultiRelaySSModule::getValueByIndex(int index) {
    bool v = digitalRead(ports[index]);
    return inversion?!v:v;
}

void MultiRelaySSModule::setValueByIndex(int index, bool value) {
    digitalWrite(ports[index], inversion?!value:value);
    inform();
    saveValue();
}

void MultiRelaySSModule::loadValue() {
    byte val = EEPROM.read(this->address);      
    int temp = 255 - val;
	
    for(int i=0; i < count; i++) {
        bool v = (temp >> i) & 1;
        digitalWrite(ports[i], inversion?!v:v);
    }
}

void MultiRelaySSModule::saveValue() {
    int val = 0;
    for(int i=0; i < count; i++) {
        bool v = digitalRead(ports[i]);
        val ^= (inversion?!v:v) << i;
    }
    
    int temp = val - 255;
    if(temp < 0)
		temp = -temp;
    
	EEPROM.write(this->address, temp);
}

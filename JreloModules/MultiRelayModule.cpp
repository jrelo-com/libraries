#include <MultiRelayModule.h>

MultiRelayModule::MultiRelayModule(const char *key, int *ports, int count, bool inversion) : Module(key) {
    this->ports = ports;
    this->count = count;
    this->inversion = inversion;
}


void MultiRelayModule::inputData(const char *data) {
    int val = atoi(data);

    for(int i=0; i < count; i++) {
        bool v = (val >> i) & 1;      
        digitalWrite(ports[i], inversion?!v:v);
    }
}

void MultiRelayModule::outputData(Pipe *pipe) {
    int val = 0;
    for(int i=0; i < count; i++) {
		bool v = digitalRead(ports[i]);
        val ^= (inversion?!v:v) << i;
    }

    char temp[5] = {0};
    TypeConverter::intToCharArray(temp, val);
    pipe->push(temp);
}

void MultiRelayModule::update() {
    if(init)
        return;

    init=true;
    for(int i=0; i < count; i++) {
        pinMode(ports[i], 1);
        digitalWrite(ports[i], inversion?1:0);
    }
}

MultiRelayModule::~MultiRelayModule() {}

bool MultiRelayModule::getValue(int port) {
    bool v = digitalRead(port);
    return inversion?!v:v;
}

void MultiRelayModule::setValue(int port, bool value) {
    digitalWrite(port, inversion?!value:value);
    inform();
}

bool MultiRelayModule::getValueByIndex(int index) {
    bool v = digitalRead(ports[index]);
    return inversion?!v:v;
}

void MultiRelayModule::setValueByIndex(int index, bool value) {
    digitalWrite(ports[index], inversion?!value:value);
    inform();
}

#include <DHTTemperatureModule.h>

DHTTemperatureModule::DHTTemperatureModule(char *key, DHT *dht) : Module(key) {
    this->dht = dht;
}

void DHTTemperatureModule::update() {
    if(timer.event()) {
        inform();
    }
}

void DHTTemperatureModule::inputData(char *data) {}

void DHTTemperatureModule::outputData(Pipe *pipe) {
	
	char temp[7];
    TypeConverter::floatToCharArray(temp, dht->readTemperature(), 6, 2);
		
    pipe->push(temp);
}

DHTTemperatureModule::~DHTTemperatureModule() {}

#include <DHTHumidityModule.h>

DHTHumidityModule::DHTHumidityModule(char *key, DHT *dht): Module(key) {
    this->dht = dht;
}

void DHTHumidityModule::update() {
    if(timer.event()) {
        inform();
    }
}

void DHTHumidityModule::inputData(char *data) {}

void DHTHumidityModule::outputData(Pipe *pipe) {
		
	char temp[7];
    TypeConverter::floatToCharArray(temp, dht->readHumidity(), 6, 1);
		
    pipe->push(temp);
}

DHTHumidityModule::~DHTHumidityModule() {}

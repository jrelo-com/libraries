#include <GPSModule.h>

GPSModule::GPSModule(char *key, LocationProvider *locationProvider) : Module(key) {
    this->locationProvider = locationProvider;
}

GPSModule::~GPSModule() {}


void GPSModule::update() {
    if(timer.event())
        inform();
}

void GPSModule::inputData(char *data) {}

void GPSModule::outputData(Pipe *pipe) {
    
    char temp[12] = {0};

	float *location = locationProvider->getLocation();

    if(location[0] == 1000.0  || location[1] == 1000.0) {
        pipe->push("null");
        return;
    }
    
    pipe->push("{\"lon\":");
    pipe->push(dtostrf(location[0], 10, 6, temp));
    pipe->push(",\"lat\":");
    pipe->push(dtostrf(location[1], 10, 6, temp));
    pipe->push("}");
}


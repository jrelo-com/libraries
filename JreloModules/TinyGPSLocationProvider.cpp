#include <TinyGPSLocationProvider.h>

TinyGPSLocationProvider::TinyGPSLocationProvider(TinyGPS *gps, HardwareSerial *serial) {
    this->gps = gps;
    this->serial = serial;
}

TinyGPSLocationProvider::~TinyGPSLocationProvider() {}

float* TinyGPSLocationProvider::getLocation(){
	read();
	return location;
}

void TinyGPSLocationProvider::read() {

    unsigned long start = millis();
    do  {
        while (serial->available()) {
            char c = serial->read();
            this->gps->encode(c);
        }
    } while (millis() - start < 1000);
    
    unsigned long age;
    gps->f_get_position(&location[1], &location[0], &age);
    
}


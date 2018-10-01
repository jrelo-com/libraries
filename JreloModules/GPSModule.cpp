#include <GPSModule.h>


GPSModule::GPSModule(char *key, TinyGPS *gps, HardwareSerial *serial) : Module(key) {
    this->gps = gps;
    this->serial = serial;
}

GPSModule::~GPSModule() {}


void GPSModule::update() {
    if(timer.event())
        inform();
    
}

void GPSModule::read(unsigned long ms) {

    unsigned long start = millis();
    do  {
        while (serial->available()) {
            char c = serial->read();
            this->gps->encode(c);
        }
    } while (millis() - start < ms);
}

void GPSModule::inputData(char *data) {}

void GPSModule::outputData(Pipe *pipe) {
    read(100);
    float flat, flon;
    long age;
    char temp[11] = {0};

    gps->f_get_position(&flat, &flon, &age);

    if(flat == 1000.0 || flon == 1000.0) {
        pipe->push("null");
        return;
    }
    pipe->push("{\"lng\":");
    pipe->push(dtostrf(flon, 10, 6, temp));
    pipe->push(",\"lat\":");
    pipe->push(dtostrf(flat, 10, 6, temp));
    pipe->push("}");
}

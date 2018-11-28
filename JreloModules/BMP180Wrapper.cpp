#include <BMP180Wrapper.h>

BMP180Wrapper::BMP180Wrapper(SFE_BMP180 *bmp180) {
    this->bmp180 = bmp180;
}

BMP180Wrapper::~BMP180Wrapper() {}

void BMP180Wrapper::begin() {
    bmp180->begin();
    process();
}

void BMP180Wrapper::process() {
    char status = bmp180->startTemperature();
    if (status != 0) {
        delay(status);
        status = bmp180->getTemperature(temperature);
        if (status != 0) {
            status = bmp180->startPressure(3);
            if (status != 0) {
                delay(status);
                status = bmp180->getPressure(pressure,temperature);
            }
        }
    }
}

void BMP180Wrapper::update() {
    if(timer.event()) {
        process();
    }
}

double BMP180Wrapper::getTemperature() {
    return temperature;
}

double BMP180Wrapper::getPressure() {
    return pressure;
}

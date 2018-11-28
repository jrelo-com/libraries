#pragma once
#include <Arduino.h>
#include <Module.h>
#include <BMP180Wrapper.h>
#include <SimpleTimer.h>
#include <TypeConverter.h>

class BMP180PressureModule : public Module {

    private :

        BMP180Wrapper *bmp180 = NULL;
        SimpleTimer timer = SimpleTimer(60000);

    public :

        BMP180PressureModule(char *key, BMP180Wrapper *bmp180);
        ~BMP180PressureModule();
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();

};

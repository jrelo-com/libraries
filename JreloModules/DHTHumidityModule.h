#pragma once
#include <Arduino.h>
#include <Module.h>
#include <DHT.h>
#include <SimpleTimer.h>
#include <TypeConverter.h>

class DHTHumidityModule : public Module {

    private :
    
        DHT *dht = NULL;
        SimpleTimer timer = SimpleTimer(10 * 1000);

    public :
    
        DHTHumidityModule(char *key, DHT *dht);
        ~DHTHumidityModule();
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();

};

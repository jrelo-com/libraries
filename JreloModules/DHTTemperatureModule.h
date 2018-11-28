#pragma once
#include <Arduino.h>
#include <Module.h>
#include <DHT.h>
#include <SimpleTimer.h>
#include <TypeConverter.h>

class DHTTemperatureModule : public Module {

    private :

        DHT *dht = NULL;
        SimpleTimer timer = SimpleTimer(60000);

    public :

        DHTTemperatureModule(char *key, DHT *dht);
        ~DHTTemperatureModule();
        void inputData(char *data);
        void outputData(Pipe *pipe);
        void update();


};

/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.1.0
 * */
 
#pragma once
#include <Arduino.h>
#include <Module.h>
#include <SIMX.h>
#include <SimpleTimer.h>
#include <TypeConverter.h>


class GSMUnitInfoModule : public Module {

    private :
		SIMX *simx	= NULL;
        SimpleTimer timer = SimpleTimer(60000);

    public :

        GSMUnitInfoModule(char *key, SIMX *simx);
        ~GSMUnitInfoModule();
        void update();
        void inputData(char *data);
        void outputData(Pipe *pipe);

};


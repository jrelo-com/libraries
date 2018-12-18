/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <SimpleTimer.h>
#include <TypeConverter.h>


class LifetimeModule : public Module {

	private :

		SimpleTimer timer = SimpleTimer(60000);

    public :

        LifetimeModule(const char *key);
        ~LifetimeModule();
        void inputData(const char *data);
        void outputData(Pipe *pipe);
		void update();

};

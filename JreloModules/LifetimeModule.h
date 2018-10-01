#pragma once
#include <Arduino.h>
#include <Module.h>
#include <SimpleTimer.h>
#include <TypeConverter.h>


class LifetimeModule : public Module {

	private :

		SimpleTimer timer = SimpleTimer(30 * 1000);

    public :

        LifetimeModule(char *key);
        ~LifetimeModule();
        void inputData(char *data);
        void outputData(Pipe *pipe);
		void update();

};

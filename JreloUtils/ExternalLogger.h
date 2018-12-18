/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <TimeProvider.h>
#include <StringBuffer.h>
#include <SimpleTimer.h>


class ExternalLogger {

	private :
	
		const char *fileName = NULL;
		HardwareSerial *hs = NULL;
		StringBuffer *stringBuffer = NULL;
		SimpleTimer simpleTimer = SimpleTimer(30000);
	
	public :
	
		ExternalLogger(const char *fileName, HardwareSerial *hs, StringBox *stringBox);
		void update();
		void init();
	
};


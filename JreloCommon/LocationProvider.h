/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>

class LocationProvider {
	
	public :
	
		virtual float* getLocation() 	= 0;

	
};

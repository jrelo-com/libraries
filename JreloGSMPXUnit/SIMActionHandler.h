/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>

class SIMActionHandler {

    public :

        virtual void ring() 		= 0;
        virtual void noCarrier() 	= 0;

};

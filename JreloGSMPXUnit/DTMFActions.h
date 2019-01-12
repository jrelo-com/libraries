/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>

class DTMFActions {

    public :

        virtual void zero() 	= 0;
        virtual void one() 		= 0;
        virtual void two() 		= 0;
        virtual void three() 	= 0;
        virtual void four() 	= 0;
        virtual void five() 	= 0;
        virtual void six() 		= 0;
        virtual void seven() 	= 0;
        virtual void eight() 	= 0;
        virtual void nine() 	= 0;

};


/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <avr/wdt.h>

class WDT {

    private :
        static bool flag;

    public :
        static void start();
        static void stop();
        static void reset();
        static void use(bool flag);
        static bool isUsed();

};

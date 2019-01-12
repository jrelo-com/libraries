/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <StringBuffer.h>

class PhoneNumbersStorage {

    public :
        /*
         * pattern : +380955555555;+3915555555;+380675555555
         * */
        virtual void getPhoneNumbers(StringBuffer *sb) = 0;

};

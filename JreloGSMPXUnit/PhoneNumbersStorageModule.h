/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <EEPROM.h>
#include <PhoneNumbersStorage.h>

class PhoneNumbersStorageModule : public Module, public PhoneNumbersStorage {

    private :

        int firstAddress = 0; // need 70 bytes (5x numbers with ';')

    public :

        PhoneNumbersStorageModule(const char *key, int firstAddress);
        ~PhoneNumbersStorageModule();
        void update();
        void inputData(const char *data);
        void outputData(Pipe *pipe);
        void getPhoneNumbers(StringBuffer *stringBuffer);

};

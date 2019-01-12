/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>
#include <PhoneNumbersStorage.h>

class StaticPhoneNumbersStorage :  public PhoneNumbersStorage {

    private :

        const char *phoneNumbers = NULL;

    public :

        StaticPhoneNumbersStorage(const char *phoneNumbers);
        ~StaticPhoneNumbersStorage();
        void getPhoneNumbers(StringBuffer *stringBuffer);

};

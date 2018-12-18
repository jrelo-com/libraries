/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>


class XXTEAHelper {

    public :

        static char* decryptData(const char *data, int dataLength, const char *encryptionPassword);

        static char* encryptData(const char *data, int dataLength, const char *encryptionPassword);

};



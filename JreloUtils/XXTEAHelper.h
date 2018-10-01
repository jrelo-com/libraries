#pragma once
#include <Arduino.h>


class XXTEAHelper {

    public :

        static char* decryptData(char *data, int dataLength, char *encryptionPassword);

        static char* encryptData(char *data, int dataLength, char *encryptionPassword);

};



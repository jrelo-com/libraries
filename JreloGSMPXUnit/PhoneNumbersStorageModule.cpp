#include <PhoneNumbersStorageModule.h>


PhoneNumbersStorageModule::PhoneNumbersStorageModule(const char *key, int firstAddress) : Module(key) {
    this->firstAddress = firstAddress;
}

PhoneNumbersStorageModule::~PhoneNumbersStorageModule() {}

void PhoneNumbersStorageModule::update() {}

void PhoneNumbersStorageModule::inputData(const char *data) {
    if(strlen(data) > 70) {
        return;
    }
    for(uint8_t i = 0; i < 70; i++) {
        if(data[i] == 0)
            break;

        EEPROM.write(firstAddress + i, (byte)data[i]);
        Serial.print(data[i]);
    }
}

void PhoneNumbersStorageModule::outputData(Pipe *pipe) {
    pipe->push('"');
    for(uint8_t i = 0; i < 70; i++) {
        byte data = EEPROM.read(firstAddress + i);
        if(data > 0 && data < 128)
            pipe->push((char)data);
    }
    pipe->push('"');
}

void PhoneNumbersStorageModule::getPhoneNumbers(StringBuffer *stringBuffer) {
    for(uint8_t i = 0; i < 64; i++) {
        stringBuffer->append( EEPROM.read(firstAddress + i) );
    }
}

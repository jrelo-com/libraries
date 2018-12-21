#include <UJsonListener.h>

void UJsonListener::setModules(Module **modules, uint8_t *moduleCount) {
    this->modules = modules;
    this->moduleCount = moduleCount;
}

void UJsonListener::key(String key) {
    index = -1;

#ifdef DEBUG
    Serial.print(F("key : "));
    Serial.println(key);
    Serial.print(F("RAM : "));
    Serial.println(RAM::free());
#endif
    for (int i = 0; i < *moduleCount; i++) {
		Module *module = modules[i];
		
        if (strcmp(module->getKey(), key.c_str()) == 0) {
#ifdef DEBUG
            Serial.print(F("idnex : "));
            Serial.println(i);
#endif
            this->index = i;
            break;
        }
    }
}

void UJsonListener::value(String value) {

#ifdef DEBUG
    Serial.print(F("value : "));
    Serial.println(value);
    Serial.print(F("RAM : "));
    Serial.println(RAM::free());
#endif

    if (index == -1)
        return;

	Module *module = modules[this->index];

    if (strcmp(value.c_str(), "?") == 0) { // if value '?' -> need to inform
        module->inform();
    } else {
        module->inputData(value.c_str());
		module->apply();
    }

}

void UJsonListener::whitespace(char c) {}

void UJsonListener::startDocument() {}

void UJsonListener::endArray() {}

void UJsonListener::endObject() {}

void UJsonListener::endDocument() {}

void UJsonListener::startArray() {}

void UJsonListener::startObject() {}


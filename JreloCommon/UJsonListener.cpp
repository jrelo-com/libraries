#include <UJsonListener.h>

void UJsonListener::setModules(LList<Module> *modules) {
    this->modules = modules;
}

void UJsonListener::key(String key) {
    index = -1;

#ifdef DEBUG
    Serial.print(F("key : "));
    Serial.println(key);
    Serial.print(F("RAM : "));
    Serial.println(RAM::free());
#endif
    for (int i = 0; i < modules->size(); i++) {
        if (strcmp(modules->get(i)->getKey(), key.c_str()) == 0) {
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

    if (strcmp(value.c_str(), "?") == 0) { // if value '?' -> need to inform
        modules->get(this->index)->inform();
    } else {
        modules->get(this->index)->inputData(value.c_str());
		modules->get(this->index)->apply();
    }

}

void UJsonListener::whitespace(char c) {}

void UJsonListener::startDocument() {}

void UJsonListener::endArray() {}

void UJsonListener::endObject() {}

void UJsonListener::endDocument() {}

void UJsonListener::startArray() {}

void UJsonListener::startObject() {}


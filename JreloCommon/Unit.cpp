#include <Unit.h>

void Unit::setValuesInRequest(uint8_t valuesInRequest) {
    this->valuesInRequest = valuesInRequest;
}

void Unit::executor(String *json) {

#ifdef DEBUG
    Serial.print(F("download. json : "));
    Serial.println(*json);
#endif

    UJsonListener listener;
    listener.setModules(modules, &length);

    JsonStreamingParser parser;
    parser.setListener(&listener);

    for (unsigned int i = 0; i < json->length(); i++) {
        parser.parse((*json)[i]);
    }
    parser.reset();
}

void Unit::updateValuesInModules() {
    for (int i = 0; i < length; i++) {
        Module *module = modules[i];
        module->update();

        if (module->needToApply()) {
            module->applied();

            if(module->isFeedback())
                module->inform();
        }
    }
}

void Unit::getRequest() {
    if(!isReady())
        return;

    String str = "";
    bool exec = false;
    bool result = getData(&str, &exec);

#ifdef DEBUG
    Serial.print(F("GET data - "));
    if(result) {
        Serial.println(F("Success"));
    } else {
        Serial.println(F("Failure"));
    }
#endif

    if(exec)
        executor(&str);
}

void Unit::prepareOutgoingData() {
    if(!isReady())
        return;

    if (!needToSend())
        return;

    bool first = true;
    String str = "";
    StringPipe pipe(&str); // adapter

    str += '{';
    uint8_t sendTo = 0;
    for (int i = 0; i < length; i++) {
        if (modules[i]->needToInform()) {

            Module *module = modules[i];

            if (!first) {
                str += ',';
            } else {
                first = false;
            }

            str += '\"';
            str += module->getKey();
            str += "\":";
            module->outputData(&pipe);
            module->informed();

            sendTo++;

            if(sendTo == valuesInRequest)
                break;
        }
    }
    str += '}';

#ifdef DEBUG
    Serial.print(F("upload. json : "));
    Serial.println(str);
#endif

    bool result = postData(&str);
#ifdef DEBUG
    Serial.print(F("POST data - "));
    if(result) {
        Serial.println(F("Success"));
    } else {
        Serial.println(F("Failure"));
    }
#endif
}

bool Unit::needToSend() {
    bool result = false;

    for (int i = 0; i < length; i++) {
        if (modules[i]->needToInform()) {
            result = true;
            break;
        }
    }
    return result;
}

void Unit::putModule(Module *module) {
    if(length > MAX_NUMBER_OF_MODULES) {
        Serial.println(F("Maximum number of modules reached!"));
        return;
    }

    modules[length] = module;
    length++;
}

Unit::~Unit() {
}

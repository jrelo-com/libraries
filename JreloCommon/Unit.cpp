#include <Unit.h>

void Unit::setKeysInMessage(uint8_t keysInMessage){
	this->keysInMessage = keysInMessage;
}

void Unit::executor(String *json) {
	
#ifdef DEBUG
    Serial.print(F("download. json : "));
    Serial.println(*json);
#endif
	
    UJsonListener listener;
    listener.setModules(modules, &moduleCount);

    JsonStreamingParser parser;
    parser.setListener(&listener);

    for (unsigned int i = 0; i < json->length(); i++) {
        parser.parse((*json)[i]);
    }
    parser.reset();
}

void Unit::updateValuesInModules() {
    for (int i = 0; i < moduleCount; i++) {
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
    bool result = getData(&str);

    Serial.print(F("GET data - "));
    if(result) {
        Serial.println(F("Success"));
    } else {
        Serial.println(F("Failure"));
    }

    if (!result) {
        return;
    }

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
    for (int i = 0; i < moduleCount; i++) {
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
        }
    }
    str += '}';

#ifdef DEBUG
    Serial.print(F("upload. json : "));
    Serial.println(str);
#endif

    bool result = postData(&str);
	Serial.print(F("POST data - "));
	if(result) {
		Serial.println(F("Success"));
	} else {
		Serial.println(F("Failure"));
	}
}

bool Unit::needToSend() {
    bool result = false;

    for (int i = 0; i < moduleCount; i++) {
        if (modules[i]->needToInform()) {
            result = true;
            break;
        }
    }
    return result;
}

void Unit::putModule(Module *module) {
    modules[moduleCount] = module;
    moduleCount++;
}

Unit::~Unit(){
}

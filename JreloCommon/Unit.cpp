#include <Unit.h>

void Unit::executor(String *json) {
	
#ifdef DEBUG
    Serial.print(F("download. json : "));
    Serial.println(*json);
#endif
	
    UJsonListener listener;
    listener.setModules(modules);

    JsonStreamingParser parser;
    parser.setListener(&listener);

    for (int i = 0; i < json->length(); i++) {
        parser.parse((*json)[i]);
    }
    parser.reset();
}

void Unit::updateValuesInModules() {
    for (int i = 0; i < modules->size(); i++) {

        modules->get(i)->update();

        if (modules->get(i)->needToApply()) {
            modules->get(i)->applied();
            
            if(modules->get(i)->isFeedback())
				modules->get(i)->inform();
        }
    }
}

void Unit::getRequest() {
	if(!isReady())
		return;
	
	String str = "";
    bool response = getData(&str);

    if (!response) {
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
    for (int i = 0; i < modules->size(); i++) {
        if (modules->get(i)->needToInform()) {

			Module *module = modules->get(i);

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

     postData(&str);
}

bool Unit::needToSend() {
    bool result = false;

    for (int i = 0; i < modules->size(); i++) {
        if (modules->get(i)->needToInform()) {
            result = true;
            break;
        }
    }
    return result;
}

void Unit::putModule(Module *module) {
    this->modules->add(module);
}

Unit::~Unit(){
	delete modules;
}

#include <XUnit.h>

void XUnit::setValuesInRequest(uint8_t valuesInRequest) {
    this->valuesInRequest = valuesInRequest;
}

void XUnit::executor(const char *json) {

#ifdef DEBUG
    Serial.print(F("download. json : "));
    Serial.println(json);
#endif

    UJsonListener listener;
    listener.setModules(modules, &length);

    JsonStreamingParser parser;
    parser.setListener(&listener);

    for (unsigned int i = 0; i < strlen(json); i++) {
        parser.parse(json[i]);
    }
    parser.reset();
}

void XUnit::updateValuesInModules() {
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

void XUnit::getRequest() {
    if(!isReady())
        return;

    bool exec = false;
    StringBuffer sb = StringBuffer(&stringBox);
    bool result = getData(&sb, &exec);

#ifdef DEBUG
    Serial.print(F("GET data - "));
    if(result) {
        Serial.println(F("Success"));
    } else {
        Serial.println(F("Failure"));
    }
#endif

    if (!exec) {
        return;
    }

    if(encryption) {
        char* json = XXTEAHelper::decryptData(sb.toString(), sb.size(), encryptionPassword);
        executor(json);
        delete [] json;

    } else {
        executor(sb.toString());
    }

}

void XUnit::prepareOutgoingData() {
    if(!isReady())
        return;

    if (!needToSend())
        return;

    bool first = true;
    StringBuffer sb = StringBuffer(&stringBox);
    StringBufferPipe pipe = StringBufferPipe(&sb); // adapter

    sb.append('{');
    uint8_t sendTo = 0;
    for (int i = 0; i < length; i++) {
        Module *module = modules[i];
        if (module->needToInform()) {

            if (!first) {
                sb.append(',');
            } else {
                first = false;
            }

            sb.append('\"');
            sb.appendString(module->getKey());
            sb.appendString("\":");
            module->outputData(&pipe);
            module->informed();

            if(sendTo == valuesInRequest)
                break;
        }
    }
    sb.append('}');
    sb.trim();

#ifdef DEBUG
    Serial.print(F("upload. json : "));
    Serial.println(sb.toString());
#endif

    if (encryption) {
        char *json  = XXTEAHelper::encryptData(sb.toString(), sb.size(), encryptionPassword);
        sb.clear();
        sb.appendString(json);
        sb.trim();
        delete [] json;
    }

    bool result = postData(&sb);
#ifdef DEBUG
    Serial.print(F("POST data - "));
    if(result) {
        Serial.println(F("Success"));
    } else {
        Serial.println(F("Failure"));
    }
#endif
}

bool XUnit::needToSend() {
    bool result = false;

    for (int i = 0; i < length; i++) {
        if (modules[i]->needToInform()) {
            result = true;
            break;
        }
    }
    return result;
}

void XUnit::useEncryption(bool encryption) {
    this->encryption = encryption;
}

void XUnit::setEncryptionPassword(const char *encryptionPassword) {
    this->encryptionPassword = encryptionPassword;
}

void XUnit::putModule(Module *module) {
    if(length > MAX_NUMBER_OF_MODULES) {
        Serial.println(F("Maximum number of modules reached!"));
        return;
    }

    modules[length] = module;
    length++;
}

XUnit::~XUnit() {}

StringBox* XUnit::getStringBox() {
    return &stringBox;
}

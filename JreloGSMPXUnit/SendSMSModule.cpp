#include <SendSMSModule.h>

SendSMSModule::SendSMSModule(const char *key, SIMZ *simz) : Module(key) {
    this->simz = simz;
}

SendSMSModule::~SendSMSModule() {}

void SendSMSModule::update() {

}

void SendSMSModule::inputData(const char *data) {
    if(strlen(data) == 0)
        return;

    char *phoneNumber = strtok((char*)data, ";");
    char *text = strtok(NULL, ";");
    if(text == NULL)
        return;

    if(simz->sendSMS(phoneNumber, text))
        counter++;
}

void SendSMSModule::outputData(Pipe *pipe) {
    char temp[6] = {0};
    TypeConverter::intToCharArray(temp, counter);
    pipe->push(temp);
}

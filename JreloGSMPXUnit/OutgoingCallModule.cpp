#include <OutgoingCallModule.h>

OutgoingCallModule::OutgoingCallModule(const char *key, SIMZ *simz)  : Module(key) {
    this->simz = simz;
    setFeedback(false);
}

OutgoingCallModule::~OutgoingCallModule() {}

void OutgoingCallModule::update() {
    if(!needCallAction)
        return;

    status = simz->outgoingCall(phoneNumber);
    needCallAction = false;
    inform();
}

void OutgoingCallModule::inputData(const char *data) {
    strcpy(phoneNumber, data);
    needCallAction = true;
    status = OCR_EMPTY;
}

void OutgoingCallModule::outputData(Pipe *pipe) {
    pipe->push('"');
    switch (status) {
    case OCR_EMPTY :
        pipe->push("EMPTY");
        break;
    case OCR_FAIL :
        pipe->push("FAIL");
        break;
    case OCR_OK :
        pipe->push("OK");
        break;
    case OCR_BUSY :
        pipe->push("BUSY");
        break;
    case OCR_NO_ANSWER :
        pipe->push("NO ANSWER");
        break;
    }
    pipe->push('"');
}

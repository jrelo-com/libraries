#include <Module.h>


void Module::setFeedback(bool flag) {
    feedbackFlag = flag;
}

bool Module::isFeedback() {
    return feedbackFlag;
}

const char* Module::getKey() {
    return key;
}

void Module::apply() {
    applyFlag = true;
}

bool Module::needToApply() {
    return applyFlag;
}

void Module::applied() {
    applyFlag = false;
}

void Module::inform() {
    informFlag = true;
}

void Module::informed() {
    informFlag = false;
}

bool Module::needToInform() {
    return informFlag;
}

Module::Module(const char *key){
	this->key = key;
}

Module::~Module(){}

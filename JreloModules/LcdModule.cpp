#include <LcdModule.h>


LcdModule::LcdModule(char *key, LcdAdapter *lcdAdapter, int row) : 	Module(key) {
    this->setFeedback(false);
    this->lcdAdapter = lcdAdapter;
    this->row = row;
}

LcdModule::~LcdModule() {
    delete lcdAdapter;
}

void LcdModule::inputData(char *data) {
	this->lcdAdapter->print(this->getKey(), data, this->row);
}

void LcdModule::outputData(Pipe *pipe) {
    pipe->push("null");
}

void LcdModule::update() {}


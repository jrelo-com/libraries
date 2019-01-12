#include <ATCommandExecutorModule.h>

ATCommandExecutorModule::ATCommandExecutorModule(const char *key, ATCommandExecutor *atEx, StringBox *stringBox) : Module(key) {
    this->atEx = atEx;
    this->inputBuffer  = new StringBuffer(stringBox);
    this->outputBuffer = new StringBuffer(stringBox);
    this->stringBox = stringBox;
}

ATCommandExecutorModule::~ATCommandExecutorModule() {
    delete this->inputBuffer;
    delete this->outputBuffer;
}

void ATCommandExecutorModule::inputData(const char *data) {
    this->inputBuffer->clear();
    this->inputBuffer->appendString(data);
    this->needActionFlag = true;
}

void ATCommandExecutorModule::outputData(Pipe *pipe) {
    pipe->push('"');
    pipe->push(this->outputBuffer->toString());
    pipe->push('"');
    this->outputBuffer->clear();
}

void ATCommandExecutorModule::update() {
    if(!this->needActionFlag)
        return;

    this->needActionFlag = false;

    const char *data = inputBuffer->toString();
    char str[strlen(data)+1] = {0};
    strcpy(str, data);

    char *part = strtok(str, "&");

    while(part != NULL) {

        StringBuffer buffer0(stringBox, part);
        StringBuffer cmd(stringBox);
        StringBuffer pat(stringBox);

        bool result0 = StringBufferUtils::substringBetween(&buffer0, &cmd, "'",  "'");
        bool result1 = StringBufferUtils::substringBetween(&buffer0, &pat, ",'",  "'");

        Serial.println(result0);
        Serial.println(result1);

        if(!result0 || !result1) {
            this->inputBuffer->clear();
            this->outputBuffer->clear();
            this->outputBuffer->appendString("Wrong format");
            inform();
            return;
        }

        buffer0.clear();
        cmd.appendString(AT_END_LINE);
        atEx->sendAndCheck(&cmd, &buffer0, pat.toString(), NULL, 15000, 15000);


        StringBufferUtils::escapeQuotes(&buffer0, outputBuffer);

        part = strtok(NULL, "&");
    }

    inputBuffer->clear();
    inform();
}

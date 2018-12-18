#include <ExternalLogger.h>

ExternalLogger::ExternalLogger(const char *fileName, HardwareSerial *hs, StringBox *stringBox) {
    this->fileName = fileName;
    this->hs = hs;

    stringBuffer = new StringBuffer(stringBox);
}

void ExternalLogger::init() {
    SD.begin(4);
}

void ExternalLogger::update() {

    while(hs->available()) {
        stringBuffer->append(hs->read());
    }

	if(simpleTimer.event() && stringBuffer->size() > 0) {

		File file = SD.open(fileName, FILE_WRITE);
		file.println(stringBuffer->toString());
		file.close();

		stringBuffer->clear();
	}

}

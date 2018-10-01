#include <GSMPXUnit.h>

void GSMPXUnit::prepare() {
	
	strcpy(this->url, "app.jrelo.com:818");
	if(sim->isHTTPSUsed())
		strcat(this->url, "4");
	else
		strcat(this->url, "3");
	strcat(this->url, "/api/v1/unit/");
	strcat(this->url, uuid);
		
	strcpy(this->header, "UCP: "); // header0: param0\r\nheader1: param1\r\nheader2: param3 
	strcat(this->header, connectionPassword);
}

bool GSMPXUnit::getData(StringBuffer *body) {
    bool result = false;

    if(sim->getData(url, header)) {
        if(sim->getHttpStatusCode() == 200) {
            body->appendString(sim->getResponseBody()->toString());
            sim->getResponseBody()->clear();
            result = true;
        }
    } else {
#ifdef SPEECH
        Serial.println(F("getData - ERROR !"));
#endif
        // ??????
    }

    return result;
}

bool GSMPXUnit::postData(char *body) {
    if(!sim->postData(body, url, header)) {
#ifdef SPEECH
		Serial.println(F("postData - ERROR !"));
#endif
        // ??????
    }
}

GSMPXUnit::GSMPXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, SIM *sim) {
    this->sim = sim;
    stringBox.init(stringBoxSize);  
    this->sim->setStringBox(&stringBox);
    
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    
}

GSMPXUnit::~GSMPXUnit() {
    delete sim;
}

void GSMPXUnit::update() {

	stringBox.update();

	if(!prepareUnitFlag){
		prepare();
		prepareUnitFlag = true;	
	}

	sim->update();
		
    if (timer.event())
        getRequest();

    updateValuesInModules();
    prepareOutgoingData();
}

bool GSMPXUnit::isReady() {
    return sim->isReady();
}


#include <GSMPXUnit.h>

void GSMPXUnit::prepare() {
	
    strcpy(this->url, "app.jrelo.com:818");
    if(simx->isHTTPSUsed()){
		strcat(this->url, "4");
	}else{
		strcat(this->url, "3");
	}
    strcat(this->url, "/api/v1/unit/");   
    strcat(this->url, uuid);

    strcpy(this->headers, "UCP: "); // header0: param0\r\nheader1: param1\r\nheader2: param3
    strcat(this->headers, connectionPassword);
    
    simx->setUrl(this->url);
    simx->setHeaders(this->headers);
}

bool GSMPXUnit::getData(StringBuffer *body) {
    bool result = false;
	
	uint16_t responseCode = 0;
    if(simx->getAction(body, &responseCode)) {	
        if(responseCode == 200) {
#ifdef DEBUG
            Serial.println(body->toString());
#endif
            result = true;
        }
    } else {
#ifdef DEBUG
        Serial.println(F("getData - ERROR !"));
#endif
    }
    return result;
}

bool GSMPXUnit::postData(StringBuffer *body) {
	uint16_t responseCode = 0;
    if(simx->postAction(body, &responseCode)) {
		return true;
    }
#ifdef DEBUG
        Serial.println(F("postData - ERROR !"));
#endif
    return false;
}

GSMPXUnit::GSMPXUnit(uint16_t stringBoxSize, const char *uuid, const char *connectionPassword) {
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->stringBox.init(stringBoxSize);  
}

GSMPXUnit::~GSMPXUnit() {}

void GSMPXUnit::update() {

	stringBox.update();

    if(!prepareUnitFlag) {
        prepare();
        prepareUnitFlag = true;
    }

    simx->update();

    if (requestTimer.event())
        getRequest();

    updateValuesInModules();
    prepareOutgoingData();
}

bool GSMPXUnit::isReady() {
    return simx->isReady();
}

void GSMPXUnit::setSIMX(SIMX *simx){
	this->simx = simx;
}

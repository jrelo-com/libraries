#include <EthernetWXUnit.h>

bool EthernetWXUnit::ethernetInit() {
    Serial.println(F("Ethernet init"));
    if(ip != NULL && dns == NULL) {
        Ethernet.begin(this->mac, IPAddress(ip[0], ip[1], ip[2], ip[3]));
        return true;
    } else if(ip != NULL && dns != NULL) {
        Ethernet.begin(this->mac, IPAddress(ip[0], ip[1], ip[2], ip[3]), IPAddress(dns[0], dns[1], dns[2], dns[3]));
        return true;
    } else {
        Serial.println(F("DHCP"));
        WDT::stop();
        bool result =  Ethernet.begin(this->mac, 10000);
        WDT::start();
        return result;
    }
}

void EthernetWXUnit::prepare() {
    webSocketClient.userAgent = (char*)userAgent;
	webSocketClient.host = (char*)host;
	webSocketClient.connectionPassword = (char*)connectionPassword;
	
	strcpy(this->path, "/api/v1/unit/");
    strcat(this->path, uuid);
	webSocketClient.path = this->path;
}

bool EthernetWXUnit::connection() {

	if(!ethernetReadyFlag)
		return false;
				
    if (ethernetClient.connect(host, 8181)) {
        Serial.println(F("Conected"));
    } else {
        Serial.println(F("Fail"));
        ethernetReadyFlag = false;
        return false;
    }
	WDT::reset();
    if (webSocketClient.handshake(ethernetClient)) {
        Serial.println(F("Handshake successful"));
    } else {
        Serial.println(F("Handshake failed."));
        return false;
    }
	WDT::reset();
    return true;
}

void EthernetWXUnit::connectionSurvival() {
    if(!ethernetReadyFlag) 
		return;
    
    if (ethernetClient.connected()) {
        return;
    }
	WDT::reset();
    ethernetClient.stop();
    delay(1000);
	WDT::reset();
	
    Serial.println(F("Try reconnect ..."));

    if (connection()) {
        Serial.println(F("Connection established !"));
    } else {
        Serial.println(F("Connection failed !"));
    }
}

bool EthernetWXUnit::getData(StringBuffer *buffer, bool *exec) {
	WDT::reset();
    this->webSocketClient.getData(buffer);
    if (buffer->size() != 0) {
        *exec = true;
    }
	WDT::reset();
    return true;
}

bool EthernetWXUnit::postData(StringBuffer *data) {
	WDT::reset();
    this->webSocketClient.sendData(data->toString());
    WDT::reset();
	return true;
}

EthernetWXUnit::EthernetWXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac) {
    stringBox.init(stringBoxSize);
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
    prepare();
}

EthernetWXUnit::EthernetWXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac, byte *ip) {
    stringBox.init(stringBoxSize);
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
    this->ip = ip;
    prepare();
}

EthernetWXUnit::EthernetWXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword,  byte *mac, byte *ip, byte *dns) {
    stringBox.init(stringBoxSize);
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
    this->ip = ip;
    this->dns = dns;
    prepare();
}

EthernetWXUnit::~EthernetWXUnit() {}

void EthernetWXUnit::update() {
	WDT::reset();
    if (!ethernetReadyFlag && connectionTimer.event()) {
        ethernetReadyFlag = ethernetInit();
        WDT::stop();
        WDT::start();
        Serial.print(F("Ethernet status = "));
        Serial.println(ethernetReadyFlag);

        connectionTimer.reset();
    }
	WDT::reset();
    connectionSurvival();
    WDT::reset();
    getRequest();
    WDT::reset();
    updateValuesInModules();
    WDT::reset();
    prepareOutgoingData();
    WDT::reset();
}

bool EthernetWXUnit::isReady() {
    return this->ethernetReadyFlag;
}

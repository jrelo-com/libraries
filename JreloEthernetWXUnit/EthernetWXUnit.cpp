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
        return Ethernet.begin(this->mac, 10000);
    }
}

void EthernetWXUnit::prepare() {
    webSocketClient.userAgent = userAgent;
	webSocketClient.host = host;
	webSocketClient.connectionPassword = connectionPassword;
	
	strcpy(this->path, "/api/v1/unit/");
    strcat(this->path, uuid);
	webSocketClient.path = this->path;
}

bool EthernetWXUnit::connection() {

	if(!ethernetReadyFlag)
		return;
				
    if (ethernetClient.connect(host, 8181)) {
        Serial.println(F("Conected"));
    } else {
        Serial.println(F("Fail"));
        ethernetReadyFlag = false;
        return false;
    }

    if (webSocketClient.handshake(ethernetClient)) {
        Serial.println(F("Handshake successful"));
    } else {
        Serial.println(F("Handshake failed."));
        return false;
    }

    return true;
};

void EthernetWXUnit::connectionSurvival() {
    if(!ethernetReadyFlag) 
		return;
    
    if (ethernetClient.connected()) {
        return;
    }

    ethernetClient.stop();
    delay(1000);

    Serial.println(F("Try reconnect ..."));

    if (connection()) {
        Serial.println(F("Connection established !"));
    } else {
        Serial.println(F("Connection failed !"));
    }
}

bool EthernetWXUnit::getData(StringBuffer *buffer) {
    this->webSocketClient.getData(buffer);
    if (buffer->size() == 0) {
        return false;
    }

    return true;
}

bool EthernetWXUnit::postData(StringBuffer *data) {
    this->webSocketClient.sendData(data->toString());
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

    if (!ethernetReadyFlag && connectionTimer.event()) {
        ethernetReadyFlag = ethernetInit();
        Serial.print(F("Ethernet status = "));
        Serial.println(ethernetReadyFlag);

        connectionTimer.reset();
    }

    connectionSurvival();
    getRequest();
    updateValuesInModules();
    prepareOutgoingData();
}

bool EthernetWXUnit::isReady() {
    return this->ethernetReadyFlag;
}




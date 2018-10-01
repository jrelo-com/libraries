#include <EthernetWUnit.h>

bool EthernetWUnit::ethernetInit() {
#ifdef DEBUG
    Serial.println(F("Ethernet init"));
#endif
    if(ip != NULL && dns == NULL) {
        Ethernet.begin(this->mac, IPAddress(ip[0], ip[1], ip[2], ip[3]));
        return true;
    } else if(ip != NULL && dns != NULL) {
        Ethernet.begin(this->mac, IPAddress(ip[0], ip[1], ip[2], ip[3]), IPAddress(dns[0], dns[1], dns[2], dns[3]));
        return true;
    } else {
#ifdef DEBUG
        Serial.println(F("DHCP"));
#endif
        return Ethernet.begin(this->mac, 10000);
    }
}

void EthernetWUnit::prepare() {
    webSocketClient.userAgent = userAgent;
    webSocketClient.host = host;
    webSocketClient.connectionPassword = connectionPassword;

    strcpy(this->path, "/ws/unit/");
    strcat(this->path, uuid);
    webSocketClient.path = path;
}

bool EthernetWUnit::connection() {

    if(!ethernetReadyFlag)
        return;

    if (ethernetClient.connect(host, 8181)) {
#ifdef DEBUG
        Serial.println(F("Conected"));
#endif
    } else {
#ifdef DEBUG
        Serial.println(F("Fail"));
#endif
        ethernetReadyFlag = false;
        return false;
    }

    if (webSocketClient.handshake(ethernetClient)) {
#ifdef DEBUG
        Serial.println(F("Handshake successful"));
#endif
    } else {
#ifdef DEBUG
        Serial.println(F("Handshake failed."));
#endif
        return false;
    }

    return true;
};

void EthernetWUnit::connectionSurvival() {
    if(!ethernetReadyFlag)
        return;

    if (ethernetClient.connected()) {
        return;
    }

    ethernetClient.stop();
    delay(1000);
#ifdef DEBUG
    Serial.println(F("Try reconnect ..."));
#endif
    if (connection()) {
#ifdef DEBUG
        Serial.println(F("Connection established !"));
#endif
    } else {
#ifdef DEBUG
        Serial.println(F("Connection failed !"));
#endif
    }
};

bool EthernetWUnit::getData(String *data) {

    this->webSocketClient.getData(*data);
    if (data->length() == 0) {
        return false;
    }

    return true;
}

bool EthernetWUnit::postData(String *data) {
    this->webSocketClient.sendData(*data);
}

EthernetWUnit::EthernetWUnit(const char *uuid, const char *connectionPassword, byte *mac) {
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
    prepare();
}

EthernetWUnit::EthernetWUnit(const char *uuid, const char *connectionPassword, byte *mac, byte *ip) {
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
    this->ip = ip;
    prepare();
}

EthernetWUnit::EthernetWUnit(const char *uuid, const char *connectionPassword, byte *mac, byte *ip, byte *dns) {
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
    this->ip = ip;
    this->dns = dns;
    prepare();
}

EthernetWUnit::~EthernetWUnit() {}

void EthernetWUnit::update() {

    if (!ethernetReadyFlag && connectionTimer.event()) {
        ethernetReadyFlag = ethernetInit();
#ifdef DEBUG
        Serial.print(F("Ethernet status = "));
        Serial.println(ethernetReadyFlag);
#endif
        connectionTimer.reset();
    }

    connectionSurvival();
    getRequest();
    updateValuesInModules();
    prepareOutgoingData();
}

bool EthernetWUnit::isReady() {
    return this->ethernetReadyFlag;
}




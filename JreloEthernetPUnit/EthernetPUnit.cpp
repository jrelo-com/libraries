#include <EthernetPUnit.h>


bool EthernetPUnit::getData(String *body) {
    if (!ethernetClient.connect("app.jrelo.com", 8183)) {
#ifdef DEBUG
        Serial.println(F("Connection ERROR"));
#endif
        ethernetInitFlag = false;
        return false;
    }

    ethernetClient.print(F("GET /api/v1/unit/"));
    ethernetClient.print(uuid);
    ethernetClient.println(F(" HTTP/1.1"));
    ethernetClient.println(F("Host: app.jrelo.com"));
    ethernetClient.println(F("User-Agent: PUnit"));
    ethernetClient.print(F("UCP: "));
    ethernetClient.println(connectionPassword);
    ethernetClient.println(F("Connection: close"));
    ethernetClient.println();

    while ( ethernetClient.connected() ) {
        if (ethernetClient.available()) {
            (*body) += (char)ethernetClient.read();
        }
    }

    ethernetClient.stop();
    body->trim();
    int status = statusCode(body->c_str());
#ifdef DEBUG
    Serial.print(F("HTTP status : "));
    Serial.println(status);
#endif
    if (status == 204) {
        return false;
    }

    if (status == 200) {
        int start = findHttpBody(body->c_str());
        body->remove(0, start);
#ifdef DEBUG
        Serial.print(F("HTTP body : "));
        Serial.println(*body);
#endif
        return true;
    }

    return false;
}

bool EthernetPUnit::postData(String *body) {
    if (!ethernetClient.connect("app.jrelo.com", 8183)) {
        Serial.println(F("Connection ERROR"));
        ethernetInitFlag = false;
        return false;
    }
    ethernetClient.print(F("POST /api/v1/unit/"));
    ethernetClient.print(uuid);
    ethernetClient.println(F(" HTTP/1.1"));
    ethernetClient.println(F("Host: app.jrelo.com"));
    ethernetClient.println(F("User-Agent: PXUnit"));
    ethernetClient.print(F("UCP: "));
    ethernetClient.println(connectionPassword);
    ethernetClient.println(F("Connection: close"));
    ethernetClient.print(F("Content-Length: "));
    ethernetClient.println(body->length());
    ethernetClient.println();
    ethernetClient.print(body->c_str());

    ethernetClient.stop();

    return true;
}

int EthernetPUnit::statusCode(char *response) {
    char *temp = strstr(response, " ");
    int space = temp - response + 1;

    char subbuff[4] = {'\0'};
    memcpy( subbuff, &response[space], 3);

    return atoi(subbuff);
}


int EthernetPUnit::findHttpBody(char *response) {
    char *temp = strstr(response, "\r\n\r\n");
    return temp - response + 4;
}

EthernetPUnit::EthernetPUnit(const char *uuid, const char *connectionPassword, byte *mac, byte *ip) {
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
    this->ip = ip;
}

EthernetPUnit::EthernetPUnit(const char *uuid, const char *connectionPassword, byte *mac, byte *ip, byte *dns) {
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
    this->ip = ip;
    this->dns = dns;
}

EthernetPUnit::EthernetPUnit(const char *uuid, const char *connectionPassword, byte *mac) {
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
}

bool EthernetPUnit::ethernetInit() {
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

EthernetPUnit::~EthernetPUnit() {}

bool EthernetPUnit::isReady() {
    return this->ethernetInitFlag;
}

void EthernetPUnit::update() {

    if (!ethernetInitFlag && connectionTimer.event()) {
        ethernetInitFlag = ethernetInit();
#ifdef DEBUG
        Serial.print(F("Ethernet status = "));
        Serial.println(ethernetInitFlag);
#endif
        connectionTimer.reset();
    }

    if (requestTimer.event())
        getRequest();

    updateValuesInModules();
    prepareOutgoingData();
}

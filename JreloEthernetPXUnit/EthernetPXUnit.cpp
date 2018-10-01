#include <EthernetPXUnit.h>


bool EthernetPXUnit::getData(StringBuffer *body) {
    if (!ethernetClient.connect("app.jrelo.com", 8183)) {
        Serial.println(F("Connection ERROR"));
        ethernetInitFlag = false;
        return false;
    }

    ethernetClient.print(F("GET /api/v1/unit/"));
    ethernetClient.print(uuid);
    ethernetClient.println(F(" HTTP/1.1"));
    ethernetClient.println(F("Host: app.jrelo.com"));
    ethernetClient.println(F("User-Agent: PXUnit"));
    ethernetClient.print(F("UCP: "));
    ethernetClient.println(connectionPassword);
    ethernetClient.println(F("Connection: close"));
    ethernetClient.println();

    while ( ethernetClient.connected() ) {
        if (ethernetClient.available()) {
            body->append(ethernetClient.read());
        }
    }

    ethernetClient.stop();
    body->trim();

    int status = statusCode(body->toString());

    Serial.print(F("HTTP status : "));
    Serial.println(status);

    if (status == 204) {
        return false;
    }

    if (status == 200) {
        int start = findHttpBody(body->toString());
        body->trim(start, body->size());
        return true;
    }

    return false;
}

bool EthernetPXUnit::postData(char *body) {
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
    ethernetClient.println(strlen(body));
    ethernetClient.println();
    ethernetClient.print(body);

    ethernetClient.stop();

    return true;
}

int EthernetPXUnit::statusCode(char *response) {
    char *temp = strstr(response, " ");
    int space = temp - response + 1;

    char subbuff[4] = {'\0'};
    memcpy( subbuff, &response[space], 3);

    return atoi(subbuff);
}


int EthernetPXUnit::findHttpBody(char *response) {
    char *temp = strstr(response, "\r\n\r\n");
    return temp - response + 4;
}

EthernetPXUnit::EthernetPXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac, byte *ip) {
    stringBox.init(stringBoxSize);
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
    this->ip = ip;
}

EthernetPXUnit::EthernetPXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac, byte *ip, byte *dns) {
    stringBox.init(stringBoxSize);
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
    this->ip = ip;
    this->dns = dns;
}

EthernetPXUnit::EthernetPXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac) {
    stringBox.init(stringBoxSize);
    this->uuid = uuid;
    this->connectionPassword = connectionPassword;
    this->mac = mac;
}

bool EthernetPXUnit::ethernetInit() {
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

EthernetPXUnit::~EthernetPXUnit() {}

bool EthernetPXUnit::isReady() {
    return this->ethernetInitFlag;
}

void EthernetPXUnit::update() {

    if (!ethernetInitFlag && connectionTimer.event()) {
        ethernetInitFlag = ethernetInit();
        Serial.print(F("Ethernet status = "));
        Serial.println(ethernetInitFlag);

        connectionTimer.reset();
    }

    if (requestTimer.event())
        getRequest();

    updateValuesInModules();
    prepareOutgoingData();
}


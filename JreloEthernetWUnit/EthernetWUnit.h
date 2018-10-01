#pragma once
#include <WebSocketClient.h>
#include <EthernetClient.h>
#include <Unit.h>
#include <SPI.h>
#include <Ethernet.h>
#include <WebSocketClient.h>
#include <SimpleTimer.h>

#define DEBUG true

class EthernetWUnit : public Unit {

    private :

		SimpleTimer connectionTimer = SimpleTimer(10000);
        WebSocketClient webSocketClient;
        EthernetClient ethernetClient;
        
        char path[46] = {0};
        const char *host = "app.jrelo.com";
        const char *userAgent = "WUnit";

        byte *mac = NULL;
        byte *ip = NULL;
        byte *dns = NULL;
        
		bool ethernetReadyFlag = false;
		
		void prepare();
		bool ethernetInit();
		bool connection();
		void connectionSurvival();

    protected :

        bool getData(String *data);
        bool postData(String *data);
        int statusCode(char *response) ;
        int findHttpBody(char *response);

    public :
    
		bool isReady();
		EthernetWUnit(const char *uuid, const char *connectionPassword, byte *mac);
        EthernetWUnit(const char *uuid, const char *connectionPassword, byte *mac, byte *ip);
        EthernetWUnit(const char *uuid, const char *connectionPassword, byte *mac, byte *ip, byte *dns);
        ~EthernetWUnit();
        void update();

};

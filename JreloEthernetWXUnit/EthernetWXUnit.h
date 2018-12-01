/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.1.0
 * */

#pragma once
#include <StringBuffer.h>
#include <WebSocketClient.h>
#include <EthernetClient.h>
#include <XUnit.h>
#include <SPI.h>
#include <Ethernet.h>
#include <WebSocketClient.h>
#include <SimpleTimer.h>

#define DEBUG true

class EthernetWXUnit : public XUnit {

    private :

		SimpleTimer connectionTimer = SimpleTimer(10000);
        WebSocketClient webSocketClient;
        EthernetClient ethernetClient;
        
        char path[51] = {0};
        const char *host = "app.jrelo.com";
        const char *userAgent = "WXUnit";
                
        byte *mac = NULL;
        byte *ip = NULL;
        byte *dns = NULL;
        
		bool ethernetReadyFlag = false;
		
		void prepare();
		bool ethernetInit();
		bool connection();
		void connectionSurvival();

    protected :

        bool getData(StringBuffer *body);
        bool postData(StringBuffer *body);
        int statusCode(char *response) ;
        int findHttpBody(char *response);

    public :
		
		bool isReady();
		EthernetWXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac);
        EthernetWXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac, byte *ip);
        EthernetWXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac, byte *ip, byte *dns);
        ~EthernetWXUnit();
        void update();

};

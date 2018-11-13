#pragma once
#include <SimpleTimer.h>
#include <EthernetClient.h>
#include <XUnit.h>
#include <SPI.h>
#include <Ethernet.h>

#define DEBUG true

class EthernetPXUnit : public XUnit {

    private :

        SimpleTimer requestTimer = SimpleTimer(7500);
        SimpleTimer connectionTimer = SimpleTimer(10000);
        EthernetClient ethernetClient;
				
		bool ethernetInitFlag = false;
		byte *mac = NULL;
		byte *ip = NULL; 
		byte *dns = NULL;
    
		bool ethernetInit();
        
    protected :
	
        bool getData(StringBuffer *body);
        bool postData(char *body);
        int statusCode(char *response) ;
        int findHttpBody(char *response);

    public :

		bool isReady();
		EthernetPXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac);
        EthernetPXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac, byte *ip);
        EthernetPXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac, byte *ip, byte *dns);
        ~EthernetPXUnit();
        void update();

};

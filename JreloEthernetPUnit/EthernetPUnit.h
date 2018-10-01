#pragma once
#include <SimpleTimer.h>
#include <EthernetClient.h>
#include <Unit.h>
#include <SPI.h>
#include <Ethernet.h>

class EthernetPUnit : public Unit {

    private :

        SimpleTimer requestTimer = SimpleTimer(5000);
        SimpleTimer connectionTimer = SimpleTimer(10000);
        EthernetClient ethernetClient;
		
		bool ethernetInitFlag = false;	
		byte *mac = NULL;
		byte *ip = NULL; 
		byte *dns = NULL;
    
		bool ethernetInit();
        
    protected :
	
        bool getData(String *body);
        bool postData(String *body);
        int statusCode(char *response) ;
        int findHttpBody(char *response);

    public :
    
		bool isReady();
		EthernetPUnit(const char *uuid, const char *connectionPassword, byte *mac);
        EthernetPUnit(const char *uuid, const char *connectionPassword, byte *mac, byte *ip);
        EthernetPUnit(const char *uuid, const char *connectionPassword, byte *mac, byte *ip, byte *dns);
        ~EthernetPUnit();
        void update();

};

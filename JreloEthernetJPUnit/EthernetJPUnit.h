#pragma once
#include <SimpleTimer.h>
#include <SPI.h>
#include <UIPEthernet.h>
#include <Unit.h>

#define DEBUG

class EthernetJPUnit : public Unit {

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
		EthernetJPUnit(const char *uuid, const char *connectionPassword, byte *mac);
        EthernetJPUnit(const char *uuid, const char *connectionPassword, byte *mac, byte *ip);
        EthernetJPUnit(const char *uuid, const char *connectionPassword, byte *mac, byte *ip, byte *dns);
        ~EthernetJPUnit();
        void update();

};

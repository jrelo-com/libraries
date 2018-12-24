/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.2.0
 * */

#pragma once
#include <SimpleTimer.h>
#include <EthernetClient.h>
#include <XUnit.h>
#include <SPI.h>
#include <Ethernet.h>

//~ #define DEBUG

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
	
        bool getData(StringBuffer *body, bool *exec);
        bool postData(StringBuffer *body);
        int statusCode(const char *response) ;
        int findHttpBody(const char *response);

    public :

		bool isReady();
		EthernetPXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac);
        EthernetPXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac, byte *ip);
        EthernetPXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, byte *mac, byte *ip, byte *dns);
        ~EthernetPXUnit();
        void update();

};

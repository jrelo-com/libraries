#pragma once
#include <Arduino.h>
#include <SIM.h>
#include <SimpleTimer.h>
#include <XUnit.h>

#define DEBUG

class GSMPXUnit : public XUnit {

	private :
	
        SIM *sim = NULL;
        SimpleTimer timer = SimpleTimer(10000);
        char url[70] = {0};
        char header[40] = {0};
        bool prepareUnitFlag = false;
        
        void prepare();

    protected :
    
        bool getData(StringBuffer *body);
        bool postData(char *body);
				
    public :
		
        GSMPXUnit(int stringBoxSize, const char *uuid, const char *connectionPassword, SIM *sim);
        ~GSMPXUnit();
        void update();
        bool isReady();

};

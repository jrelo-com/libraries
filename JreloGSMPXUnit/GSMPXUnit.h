/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 2.2.0
 * */

#define DEBUG

#pragma once
#include <Arduino.h>
#include <SIMX.h>
#include <SimpleTimer.h>
#include <XUnit.h>
#include <StringBuffer.h>

class GSMPXUnit : public XUnit {

	private :
	
        SIMX *simx = NULL;
        SimpleTimer requestTimer = SimpleTimer(5000);
        char url[70] = {0};
        char headers[40] = {0};
        bool prepareUnitFlag = false;
        
        void prepare();

    protected :
    
        bool getData(StringBuffer *body, bool *exec);
        bool postData(StringBuffer *body);
				
    public :
		
        GSMPXUnit(uint16_t stringBoxSize, const char *uuid, const char *connectionPassword);
        ~GSMPXUnit();
        void update();
        bool isReady();
		void setSIMX(SIMX *simx);

};

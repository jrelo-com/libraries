#pragma once
#include <Arduino.h>
#include <Module.h>
#include <StringBuffer.h>

class SIM {

	public:
	
	    virtual void setPIN(char *pin) ;
        virtual void setAPN(char *apn) ;
        virtual void useHTTPS(bool https);
        virtual bool getData(char *url, char *header);
        virtual bool postData(char *requestBody, char *url, char *header);
        virtual int getHttpStatusCode();
        virtual StringBuffer* getResponseBody();
		virtual void update();
		virtual bool isHTTPSUsed();
		virtual bool isReady();
		virtual void setStringBox(StringBox *stringBox);
		virtual ~SIM(){};

};


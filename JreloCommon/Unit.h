/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.2.0
 * */

#pragma once
#include <Arduino.h>
#include <WDT.h>
#include <Module.h>
#include <StringPipe.h>
#include <UJsonListener.h>
#include <JsonStreamingParser.h>

#define DEBUG 

#define MAX_NUMBER_OF_MODULES 12 

class Unit {

    protected :

        Module *modules[MAX_NUMBER_OF_MODULES];
        uint8_t length = 0;
        
        virtual bool getData(String *body, bool *exec) = 0;
        virtual bool postData(String *body) = 0;
        const char *connectionPassword = NULL;
        const char *uuid = NULL;     
        void executor(String *json);
        void updateValuesInModules();
        void getRequest() ;
        void prepareOutgoingData();
        bool needToSend();
        
        uint8_t valuesInRequest = MAX_NUMBER_OF_MODULES; 

	public :

        virtual void update() = 0;  
        virtual bool isReady() = 0;
        virtual ~Unit();

        void putModule(Module *module);
        
        void setValuesInRequest(uint8_t valuesInRequest);
 
};


/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>
#include <Module.h>
#include <StringPipe.h>
#include <UJsonListener.h>
#include <JsonStreamingParser.h>

#define DEBUG 

class Unit {

    protected :

        Module *modules[12];
        uint8_t moduleCount = 0;
        
        virtual bool getData(String *body) = 0;
        virtual bool postData(String *body) = 0;
        const char *connectionPassword = NULL;
        const char *uuid = NULL;     
        void executor(String *json);
        void updateValuesInModules();
        void getRequest() ;
        void prepareOutgoingData();
        bool needToSend();
        
        uint8_t keysInMessage = 12; //maximum number of keys in the message.
        uint8_t numberOfUnsentKeys = 0; 

	public :

        virtual void update() = 0;  
        virtual bool isReady() = 0;
        virtual ~Unit();

        void putModule(Module *module);
        void setKeysInMessage(uint8_t keysInMessage);
 
};


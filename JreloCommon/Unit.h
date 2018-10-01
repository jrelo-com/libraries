#pragma once
#include <Arduino.h>
#include <LList.h>
#include <Module.h>
#include <StringPipe.h>
#include <UJsonListener.h>
#include <JsonStreamingParser.h>

#define DEBUG 

class Unit {

    protected :

        LList<Module> *modules = new LList<Module>;
        virtual bool getData(String *body) = 0;
        virtual bool postData(String *body) = 0;
        char *connectionPassword = NULL;
        char *uuid = NULL;     
        void executor(String *json);
        void updateValuesInModules();
        void getRequest() ;
        void prepareOutgoingData();
        bool needToSend();

	public :

        virtual void update() = 0;  
        virtual bool isReady() = 0;
        virtual ~Unit();

        void putModule(Module *module);
 
};


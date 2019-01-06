/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.3.0
 * */

#pragma once
#include <Arduino.h>
#include <WDT.h>
#include <StringBuffer.h>
#include <StringBufferPipe.h>
#include <StringBox.h>
#include <Module.h>
#include <UJsonListener.h>
#include <JsonStreamingParser.h>
#include <XXTEAHelper.h>

//~ #define DEBUG 

#define MAX_NUMBER_OF_MODULES 12 

class XUnit {

    protected :

        Module *modules[MAX_NUMBER_OF_MODULES];
        uint8_t length = 0;
        uint8_t valuesInRequest = MAX_NUMBER_OF_MODULES; 
        bool encryption = false;
               
        StringBox stringBox = StringBox(); 
        const char *encryptionPassword = NULL;
        const char *connectionPassword = NULL;
        const char *uuid = NULL;
        
        virtual bool getData(StringBuffer *buffer, bool *exec) = 0;
        virtual bool postData(StringBuffer *buffer) = 0;       
        void executor(const char *json);
        void updateValuesInModules();
        void getRequest() ;
        void prepareOutgoingData();
        bool needToSend();
        
	public :

        virtual void update() = 0;  
        virtual bool isReady() = 0;
        virtual ~XUnit();
        
        void useEncryption(bool encryption);
        void setEncryptionPassword(const char *encryptionPassword);
        void putModule(Module *module);
        StringBox* getStringBox();
        
        void setValuesInRequest(uint8_t valuesInRequest);
               
};


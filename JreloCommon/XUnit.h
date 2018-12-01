/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.1.0
 * */

#pragma once
#include <Arduino.h>
#include <StringBuffer.h>
#include <StringBufferPipe.h>
#include <StringBox.h>
#include <LList.h>
#include <Module.h>
#include <UJsonListener.h>
#include <JsonStreamingParser.h>
#include <XXTEAHelper.h>

//~ #define DEBUG 

class XUnit {

    protected :

        LList<Module> *modules = new LList<Module>;
        StringBox stringBox = StringBox(); 
        char encryptionPassword[51] = {0};
        char *connectionPassword = NULL;
        char *uuid = NULL;
        bool encryption = false;
        virtual bool getData(StringBuffer *buffer) = 0;
        virtual bool postData(StringBuffer *buffer) = 0;       
        void executor(char *json);
        void updateValuesInModules();
        void getRequest() ;
        void prepareOutgoingData();
        bool needToSend();

	public :

        virtual void update() = 0;  
        virtual bool isReady() = 0;
        virtual ~XUnit();
        
        void useEncryption(bool encryption) ;
        void setEncryptionPassword(char *encryptionPassword) ;
        void putModule(Module *module);
        StringBox* getStringBox();
       
};


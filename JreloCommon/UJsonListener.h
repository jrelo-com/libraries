/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.1.0
 * */

#pragma once
#include <Arduino.h>
#include <JsonListener.h>
#include <Module.h>

//~ #define DEBUG 

#ifdef DEBUG
	#include <RAM.h>
#endif


class UJsonListener : public JsonListener {

  private :
  
    Module **modules = NULL;
    uint8_t *length = NULL;
    int index = 0;

  public :

    void setModules(Module **modules, uint8_t *length);

    void key(String key);

    void value(String value) ;

    void whitespace(char c);

    void startDocument();

    void endArray();

    void endObject() ;

    void endDocument() ;

    void startArray() ;

    void startObject() ;

};



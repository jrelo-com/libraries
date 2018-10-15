#pragma once
#include <Arduino.h>
#include <StringBox.h>

//~ #define DEBUG

class StringBuffer {

  private :

	StringBox *stringBox = NULL;
	int ticket = 0;
	
    int index = 0;
    int length = 0;
    bool initFlag = false;
    int startLength = 8;

    bool expand();
    bool init();

  public :

    StringBuffer(StringBox *stringBox);
    
    StringBuffer(StringBox *stringBox, int bufferSize);
    
    StringBuffer(StringBox *stringBox, char *string);

    ~StringBuffer();

    bool append(char c);

    bool appendString(char *string);

    char* toString();

    void clear();

    int size();

    bool trim();
    
    bool trim(int start, int finish);
    
    StringBox* getStringBox();
    
};

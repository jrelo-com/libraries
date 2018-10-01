#pragma once
#include <Arduino.h>
#include <Pipe.h>
#include <StringBuffer.h>

class StringBufferPipe : public Pipe {

	private:
	
		StringBuffer *buffer = NULL;

    public:
    
		StringBufferPipe(StringBuffer *buffer);
		~StringBufferPipe();
		void push(char c);
		void push(char *str);
		void push(String *str);

};

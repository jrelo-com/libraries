/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

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
		void push(const char *str);
		void push(String *str);

};

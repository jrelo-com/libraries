/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>
#include <Pipe.h>

class StringPipe : public Pipe {

	private:
	
		String *str = NULL;

    public:
    
		StringPipe(String *str);
		~StringPipe();
		void push(char c);
		void push(const char *str);
		void push(String *str);

};

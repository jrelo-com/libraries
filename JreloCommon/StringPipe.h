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
		void push(char *str);
		void push(String *str);

};

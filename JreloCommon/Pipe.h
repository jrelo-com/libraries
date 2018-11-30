/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.0
 * */

#pragma once
#include <Arduino.h>

class Pipe {

    public:
		
		virtual void push(char c) = 0;
		virtual void push(char *str) = 0;
		virtual void push(String *str) = 0;

};

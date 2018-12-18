/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>
#include <SimpleTimer.h>

//~ #define DEBUG

struct Item {
	int address = 0;
	int length = 0;
};

class StringBox {
	
	private:
	
		bool tickets[128] = {0};
		int countOfTickets = 0;
		char *memory = NULL;
		int memoryLength = 0;
		SimpleTimer defragmentationTimer = SimpleTimer(60000);

	 public:

        StringBox(int length);
        StringBox();
        ~StringBox();
        void init();
		void init(int memoryLength);
		int getTicket(int size); // false == 0, key --> -1 ... -128
		bool resizeTicket(int *ticket, int newSize);
		void defragmentation();
		char* getStringByTicket(int ticket);
		void returnTicket(int ticket);
		void showMemory();
		void update();
		int availableMemory();
		int getMemoryLength();

};

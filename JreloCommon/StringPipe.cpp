#include <StringPipe.h>

StringPipe::StringPipe(String *str) {
	this->str = str;
}

StringPipe::~StringPipe() {}

void StringPipe::push(char c) {
	(*this->str) += c;
}

void StringPipe::push(const char *str) {
	(*this->str) += str;
}

void StringPipe::push(String *str) {
	(*this->str) += (*str);
}

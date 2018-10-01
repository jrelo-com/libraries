#include <StringBufferPipe.h>

StringBufferPipe::StringBufferPipe(StringBuffer *buffer) {
	this->buffer = buffer;
}

StringBufferPipe::~StringBufferPipe() {}

void StringBufferPipe::push(char c) {
	buffer->append(c);
}

void StringBufferPipe::push(char *str) {
	buffer->appendString(str);
}

void StringBufferPipe::push(String *str) {
	buffer->appendString(str->c_str());
}

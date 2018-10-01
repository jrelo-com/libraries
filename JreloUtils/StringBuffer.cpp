#include <StringBuffer.h>


StringBuffer::StringBuffer(StringBox *stringBox) {
	this->stringBox = stringBox;
}

StringBuffer::StringBuffer(StringBox *stringBox, int bufferSize) {
	this->stringBox = stringBox;
	this->startLength = bufferSize;
}

bool StringBuffer::init() {
	if(stringBox == NULL){
		Serial.println(F("StringBuffer. StringBox not found !"));
		delay(10000);
		return;	
	}
	
	this->initFlag = true;
    this->index = 0;
    this->length = this->startLength;    
    this->ticket = stringBox->getTicket(length);
    
    if(this->ticket == 0)
		return false;

    return true;
}

StringBuffer::StringBuffer(StringBox *stringBox, char *string) {
	this->startLength = strlen(string) + 1;
	this->stringBox = stringBox;
    this->appendString(string);
}

StringBuffer::~StringBuffer() {
	if(this->ticket == 0)
		return;
		
    stringBox->returnTicket(this->ticket); 
}

bool StringBuffer::expand() {
    int newLenght = this->length;
    newLenght = newLenght + newLenght/3 + 1; 

    if(!stringBox->resizeTicket(&this->ticket, newLenght)){ // v2
		return false;
	} 
	
    this->length = newLenght;

    return true;
}

bool  StringBuffer::append(char c) {
	if(!initFlag) 
		init();

	if(c < 0){
		Serial.println(F("StringBuffer. Invalid character !"));
		return false;
	}

    if(this->index == this->length ) {
        if(!this->expand()){
			return false;
		}
    }
        
	char *buffer = stringBox->getStringByTicket(this->ticket);	
    buffer[index] = c;
    this->index++;

    return true;
}

bool StringBuffer::appendString(char *string) {
    int len = strlen(string);
    
    for (int i = 0; i < len; i++) {
        
        if(!this->append(string[i])){
			return false;
		}
    }
    return true;
}

char* StringBuffer::toString() {
    char *result = stringBox->getStringByTicket(this->ticket);
    if(result == NULL)
		return "";
		
	return result;
}

void StringBuffer::clear() {
    stringBox->returnTicket(this->ticket);
	this->ticket = 0;
    initFlag = false;
    this->index = 0;
}

int StringBuffer::size() {
    return this->index;
}

bool StringBuffer::trim() {

	if(!stringBox->resizeTicket(&this->ticket, this->index)){ // v2
		return false;
	}
	
	this->length = this->index;
	
	return true;
}

bool StringBuffer::trim(int start, int finish) {

	int newLength = finish - start;
	int newTicket = stringBox->getTicket(newLength);
	if(newTicket == 0)
		return false;
	
	
	char *newBuffer = stringBox->getStringByTicket(newTicket);
	char *oldBuffer = stringBox->getStringByTicket(this->ticket);
	
    for(int i=0, j=start; i < newLength; i++, j++) {
        newBuffer[i] = oldBuffer[j];
    }

	stringBox->returnTicket(this->ticket);

    this->ticket = newTicket;
    this->length = newLength;
    this->index = newLength;
    
    return true;
}

StringBox* StringBuffer::getStringBox(){
	return stringBox;
}

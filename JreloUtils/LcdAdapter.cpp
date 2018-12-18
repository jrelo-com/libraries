#include <LcdAdapter.h>

LcdAdapter::LcdAdapter(int address, int len, int row) {

    this->lcd = new LiquidCrystal_I2C(address, len, row); //0x20 or 0x27 or 0x3F
    this->row = row;
    this->len = len;

    this->temp = new char*[row];
    for(int i=0; i<row; i++)
        this->temp[i] = new char[len+1] {0};
}

void LcdAdapter::init(){
	if(initFlag)
		return;
		
	initFlag = true;
	this->lcd->init();
    this->lcd->backlight();
}

void LcdAdapter::print(const char *text, int row) {
    init();
    
    strcpy(this->temp[row], text);

    this->lcd->clear();

    for(int i=0; i < this->row; i++) {
        this->lcd->setCursor(0,i);
        this->lcd->print(this->temp[i]);
    }
}

void LcdAdapter::print(const char *prefix, const char *text, int row) {
	init();
	
    strcpy(this->temp[row], prefix);
    strcat(this->temp[row], " ");
    strcat(this->temp[row], text);

    this->lcd->clear();

    for(int i=0; i < this->row; i++) {
        this->lcd->setCursor(0,i);
        this->lcd->print(this->temp[i]);
    }
}

LcdAdapter::~LcdAdapter() {

    for(int i=0; i<row; i++)
        delete [] this->temp[i];

    delete [] temp;
}

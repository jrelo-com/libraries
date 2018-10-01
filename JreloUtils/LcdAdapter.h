#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LcdAdapter {

    private :
    
        LiquidCrystal_I2C *lcd = NULL;
        int len = 0;
        int row = 0;
        char **temp = NULL;
        bool initFlag = false;
        void init();

    public :
    
        LcdAdapter(int address, int len, int row);
        ~LcdAdapter();
        void print(char *text, int row);
        void print(char *prefix, char *text, int row);

};

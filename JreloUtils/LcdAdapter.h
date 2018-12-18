/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

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
        void print(const char *text, int row);
        void print(const char *prefix, const char *text, int row);

};

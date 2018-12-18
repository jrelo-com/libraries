/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>
#include <Pipe.h>

class Module {

  private :

    const char *key = NULL;
    bool applyFlag = false;
    bool informFlag = true;
    bool feedbackFlag = true; 

  public :
	
    const char* getKey();
    void apply();
    bool needToApply();
    void applied();
    void inform();
    void informed();
    bool needToInform();
    void setFeedback(bool flag); 
    bool isFeedback();
    
    Module(const char *key);
    virtual ~Module();
    virtual void inputData(const char *data) = 0;
    virtual void outputData(Pipe *pipe) = 0;
    virtual void update() = 0;

};


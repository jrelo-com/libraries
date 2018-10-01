#pragma once
#include <Arduino.h>
#include <Pipe.h>

class Module {

  private :

    char *key = NULL;
    bool applyFlag = false;
    bool informFlag = true;
    bool feedbackFlag = true; 

  public :
	
    char* getKey();
    void apply();
    bool needToApply();
    void applied();
    void inform();
    void informed();
    bool needToInform();
    void setFeedback(bool flag); 
    bool isFeedback();
    
    Module(char *key);
    virtual ~Module();
    virtual void inputData(char *data) = 0;
    virtual void outputData(Pipe *pipe) = 0;
    virtual void update() = 0;

};


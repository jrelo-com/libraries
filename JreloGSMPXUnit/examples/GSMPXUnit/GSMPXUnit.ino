#include <RAM.h>
#include <GSMPXUnit.h>
#include <StringBox.h>
#include <SIMX.h>
#include <LifetimeModule.h>
#include <ATCommandExecutorModule.h>
#include <GSMUnitInfoModule.h>

//~ #define DEBUG
#define POWER_PIN  22
//~ #define RESET_PIN  23

#ifdef DEBUG
SimpleTimer memoryTimer(10000);
#endif

const char *APN = "INTERNET";
const char *PIN = "0000";
SIMX simx(&Serial3, POWER_PIN);

const char *uuid = "00000000-0000-0000-0000-0000000";
const char *connectionPassword = "00000000000000000000000000000";
GSMPXUnit unit(1024, uuid, connectionPassword);

LifetimeModule ltm("ltm");
ATCommandExecutorModule atcmdexm("atm", simx.getAtCmdEx(), unit.getStringBox());
GSMUnitInfoModule im("im", &simx);

void setup() {
    Serial.begin(9600);
    Serial3.begin(9600);
    Serial.println(F("Init ..."));
    
    unit.setSIMX(&simx);
    simx.setStringBox(unit.getStringBox());
    
    simx.setPIN(PIN);
    simx.setAPN(APN);
    
    //~ simx.useHTTPS(true);
    //~ simx.setResetPin(RESET_PIN); // if you have an external module for resetting the SIM board

    unit.putModule(&ltm);
    unit.putModule(&atcmdexm);
    unit.putModule(&im);

    Serial.println(F("Application started !"));
#ifdef DEBUG
    showMemory();
#endif
}


#ifdef DEBUG
void showMemory() {
    Serial.print(F("Time - "));
    Serial.print(millis());
    Serial.print(F(", free memory - "));
    Serial.print(RAM::free());
    Serial.println(F(" bytes"));
}
#endif


void loop() {
    unit.update();

#ifdef DEBUG
    if (memoryTimer.event()) {
        showMemory();
    }
#endif
}

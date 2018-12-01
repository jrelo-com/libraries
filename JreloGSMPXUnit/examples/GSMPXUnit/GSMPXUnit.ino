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

SIMX simx(&Serial3, POWER_PIN);
GSMPXUnit unit(1024, "92969ef4-0000-0000-0000-4de2ad1118db", "6809bed7d27440c89216bf540c000000");
char *APN = "INTERNET";
char *PIN = "0000";

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

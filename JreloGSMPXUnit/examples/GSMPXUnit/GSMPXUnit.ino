#include <GSMPXUnit.h>
#include <SIMX.h>
#include <LifetimeModule.h>

#define POWER_PIN  22
//~ #define RESET_PIN  23

//~ const char *APN = "INTERNET";
//~ const char *PIN = "0000";
SIMX simx(&Serial3, POWER_PIN);

const char *uuid = "00000000-0000-0000-0000-0000000";
const char *connectionPassword = "00000000000000000000000000000";
GSMPXUnit unit(1024, uuid, connectionPassword);

LifetimeModule ltm("ltm");

void setup() {
    Serial.begin(9600);
    Serial3.begin(9600);
    Serial.println(F("Init ..."));

    unit.setSIMX(&simx);
    simx.setStringBox(unit.getStringBox());

    //~ simx.setPIN(PIN); 				// if you use PIN-code
    //~ simx.setAPN(APN); 				// if you use APN
    //~ WDT::use(true);   				// if your bootloader supports watchdog
    //~ simx.useHTTPS(true); 			// if your SIM board supports HTTPS
    //~ simx.setResetPin(RESET_PIN); 	// if you have an external module for resetting the SIM board

    unit.putModule(&ltm);

    Serial.println(F("Application started !"));
}

void loop() {
    unit.update();
}

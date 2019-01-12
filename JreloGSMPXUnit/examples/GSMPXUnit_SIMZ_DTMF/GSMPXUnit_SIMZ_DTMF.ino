#include <GSMPXUnit.h>
#include <PhoneNumbersStorageModule.h>
#include <StaticPhoneNumbersStorage.h>
#include "MyDTMF.cpp"

#define POWER_PIN  22
#define RESET_PIN  23

//~ const char *APN = "INTERNET";
//~ const char *PIN = "0000";
const char *uuid = "00000000-0000-0000-0000-0000000";
const char *connectionPassword = "00000000000000000000000000000";

GSMPXUnit unit(1024, uuid, connectionPassword);
ATCommandExecutor atEx(&Serial3);
SIMX simx(POWER_PIN);
SIMZ simz;

/*
 * 
 * MyDTMF is simple implementation of the DTMFActions class. Which implements the logic for dialing button event handling.
 * 
 * StaticPhoneNumbersStorage is simple static storage for phone numbers.
 * PhoneNumbersStorageModule is the storage of telephone numbers as a module. The module supports dynamic change of the list of telephone numbers.
 * Format: "+380675555555;+380955555555;...;...;"
 * 
 * If not setup ***PhoneNumbersStorage, SIMZ will automatically answer any phone number.
 * 
 * */
MyDTMF myDTMF;
//~ StaticPhoneNumbersStorage spns("+380675555555;+380955555555;");
PhoneNumbersStorageModule pnsm("pnsm", 0); // need 70 bytes EEPROM (for storage)

void setup() {
    Serial.begin(9600);
    Serial3.begin(9600);
    Serial.println(F("Init ..."));

    unit.setSIMX(&simx);
    unit.setSIMZ(&simz);
    simx.setStringBox(unit.getStringBox());
    simz.setStringBox(unit.getStringBox());
    simx.setATCommandExecutor(&atEx);
    simz.setATCommandExecutor(&atEx);

    simz.setDTMFActions(&myDTMF);
    //~ simz.setPhoneNumbersStorage(&spns); // static
    simz.setPhoneNumbersStorage(&pnsm);

    //~ WDT::use(true);   				// if your bootloader supports watchdog
    //~ simx.setPIN(PIN); 				// if you use PIN-code
    //~ simx.setAPN(APN); 				// if you use APN
    //~ simx.useHTTPS(true); 			// if your SIM board supports HTTPS
    //~ simx.setResetPin(RESET_PIN); 	// if you have an external module for resetting the SIM board

    unit.putModule(&pnsm);

    Serial.println(F("Application started !"));
}

void loop() {
    unit.update();
}




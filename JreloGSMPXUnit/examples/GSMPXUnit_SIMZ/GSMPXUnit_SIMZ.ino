#include <GSMPXUnit.h>
#include <OutgoingCallModule.h>
#include <SendSMSModule.h>

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

OutgoingCallModule ocm("ocm", &simz); 	// request format: "+380955555555"; response: "EMPTY", "OK", "FAIL", "BUSY", "NO ANSWER"
SendSMSModule ssm("ssm", &simz); 		// request format: "+380955555555;MESSAGE_TEXT"; response: number of messages sent

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

    //~ WDT::use(true);   				// if your bootloader supports watchdog
    //~ simx.setPIN(PIN); 				// if you use PIN-code
    //~ simx.setAPN(APN); 				// if you use APN
    //~ simx.useHTTPS(true); 			// if your SIM board supports HTTPS
    //~ simx.setResetPin(RESET_PIN); 	// if you have an external module for resetting the SIM board

    unit.putModule(&ocm);
    unit.putModule(&ssm);

    Serial.println(F("Application started !"));
}

void loop() {
    unit.update();
}




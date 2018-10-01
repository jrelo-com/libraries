#include <RAM.h>
#include <GSMPXUnit.h>
#include <SIM900i2.h>
#include <LifetimeModule.h>
#include <ATConsoleModule.h>

//#define DEBUG

#define POWER_PIN  22

#ifdef DEBUG
SimpleTimer memoryTimer(10000);
#endif

SIM900i2 sim(&Serial3, POWER_PIN); // &Serial1 - 18/19 ; &Serial2 - 17/16 ;  >>> &Serial3 - 15/14 <<< 
GSMPXUnit unit(1024,"00000000-0000-0000-0000-0000000", "00000000000000000000000000000", &sim);

ATConsoleModule atcm("at", &sim);
LifetimeModule ltm("lt");

void setup() {
    Serial.begin(9600);  // FOR CONSOLE
    Serial3.begin(19200); // FOR SIM900

    //~ sim.setPIN("0000");
    //~ sim.setAPN("INTERNET");
    sim.useHTTPS(true);
      
	unit.putModule(&atcm);
    unit.putModule(&ltm);
    
    Serial.println(F("Application started !"));
}


void loop() {
	
    unit.update();

#ifdef DEBUG
    if (memoryTimer.event()) {
		Serial.print(F("Time - "));
		Serial.print(millis());
        Serial.print(F(", free memory - "));
        Serial.print(RAM::free());
        Serial.println(F(" bytes"));
    }
#endif
}

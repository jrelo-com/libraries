#include <EthernetPUnit.h>
#include <LifetimeModule.h>
#include <SimpleTimer.h>
#include <RAM.h>

#define DEBUG 

#ifdef DEBUG
SimpleTimer timer(10000);
#endif

const char *uuid = "00000000-0000-0000-0000-0000000";
const char *connectionPassword = "00000000000000000000000000000";
byte mac[] = { 0xDE, 0xAB, 0xBE, 0xEF, 0xFA, 0xEF };

EthernetPUnit unit(uuid, connectionPassword, mac);

LifetimeModule ltm("lt");

void setup() {
    Serial.begin(9600);

    unit.putModule(&ltm);
        
    Serial.println(F("Application started !"));
}

void loop() {
    unit.update();

#ifdef DEBUG
    if(timer.event()) {
        Serial.print(F("Time - "));
        Serial.print(millis());
        Serial.print(F(", free memory - "));
        Serial.print(RAM::free());
        Serial.println(F(" bytes"));
    }
#endif
}

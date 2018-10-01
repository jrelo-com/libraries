#include <EthernetPJUnit.h>
#include <LifetimeModule.h>
#include <SimpleTimer.h>
#include <RAM.h>

#define DEBUG 

#ifdef DEBUG
SimpleTimer timer(10000);
#endif

byte mac[] = { 0xDE, 0xAB, 0xDE, 0xEF, 0xFF, 0xEF };
EthernetPJUnit unit("4786362e-6603-4d7e-b677-ce1f25268341", "25bb64b14604451f858bb8cd4c8e24ef", mac);

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

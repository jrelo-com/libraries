#include <EthernetWXUnit.h>
#include <LifetimeModule.h>
#include <SimpleTimer.h>
#include <RAM.h>

//#define DEBUG

#ifdef DEBUG
SimpleTimer timer(10000);
#endif

byte mac[] = { 0xDE, 0xAB, 0xBE, 0xEF, 0xFE, 0xE7 };
EthernetWXUnit unit(512, "00000000-0000-0000-0000-0000000", "00000000000000000000000000000", mac);

LifetimeModule ltm("lt");

void setup() {
    Serial.begin(9600);
    
    //unit.setEncryptionPassword("00000000");
    //unit.useEncryption(true);

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

#include <EthernetPXUnit.h>
#include <LifetimeModule.h>

const char *uuid = "00000000-0000-0000-0000-0000000";
const char *connectionPassword = "00000000000000000000000000000";
byte mac[] = { 0xDE, 0xAB, 0xDE, 0xEF, 0xFF, 0xEF };
EthernetPXUnit unit(1024, uuid, connectionPassword, mac);

LifetimeModule ltm("lt");

void setup() {
    Serial.begin(9600);

    //~ unit.setEncryptionPassword("00000000");
    //~ unit.useEncryption(true);
    //~ WDT::use(true); // if your bootloader supports watchdog

    unit.putModule(&ltm);

    Serial.println(F("Application started !"));
}

void loop() {
    unit.update();
}

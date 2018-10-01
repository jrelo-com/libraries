#include <StringBox.h>
#include <StringBuffer.h>

void setup() {

    Serial.begin(9600);
    Serial.print(F("StringBuffer\r\n\r\n"));

    StringBox box(128);
    box.init();
    StringBuffer buffer(&box);

    buffer.appendString("first string");
    //~ box.showMemory();
    buffer.appendString(" second string");
	//~ box.showMemory();
	
    Serial.println(buffer.toString());
    
}

void loop() {}

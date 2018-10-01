#include <StringBox.h>

void setup() {

    Serial.begin(9600);
    Serial.print(F("StringBox\r\n\r\n"));

    StringBox box(128);
    box.init();


	int ticket = box.getTicket(12);
	char *str = box.getStringByTicket(ticket);
	
	strcpy(str, "first string");
	Serial.println(str);
    box.showMemory();


	box.resizeTicket(&ticket, 26);
	strcat(str, " second string");
    Serial.println(str);
    box.showMemory();


    box.returnTicket(ticket);
    box.showMemory();
    
}

void loop() {}

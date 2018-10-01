#include <SimpleTimer.h>

SimpleTimer timer0(1000);
SimpleTimer timer1(2000);
SimpleTimer timer2(5000, false); // interval - false
SimpleTimer timer3(500, true, false); // interval - true, start - false

void setup() {

    Serial.begin(9600);
    Serial.print(F("SimpleTimer\r\n\r\ntimer0\ttimer1\ttimer2\ttimer3\r\n\r\n"));
}

void loop() {


    if(timer0.event()) {
        Serial.println(F("blink"));
    }

    if(timer1.event()) {
        Serial.println(F("\tblink"));
    }

    if(timer2.event()) {
        Serial.println(F("\t\tblink"));

        timer0.stop();
        timer1.stop();
        timer3.start();
    }

    if(timer3.event()) {
        Serial.println(F("\t\t\tblink"));
    }


}

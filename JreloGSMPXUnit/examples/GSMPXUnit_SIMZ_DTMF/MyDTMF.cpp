#include <DTMFActions.h>

class MyDTMF : public DTMFActions {

    public :

        void zero() {
            Serial.println(F(">> 0"));
        }

        void one() {
            Serial.println(F(">> 1"));
        }

        void two() {
            Serial.println(F(">> 2"));
        }

        void three() {
            Serial.println(F(">> 3"));
        }

        void four() {
            Serial.println(F(">> 4"));
        }

        void five() {
            Serial.println(F(">> 5"));
        }

        void six() {
            Serial.println(F(">> 6"));
        }

        void seven() {
            Serial.println(F(">> 7"));
        }

        void eight() {
            Serial.println(F(">> 8"));
        }

        void nine() {
            Serial.println(F(">> 9"));
        }

};

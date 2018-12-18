/*
 * AUTHOR  : vladyslav.hubin.1989@gmail.com
 * VERSION : 1.0.1
 * */

#pragma once
#include <Arduino.h>

class TypeConverter {

    public :

        static void longToCharArray(char *str, long l);
        static void unsignedLongToCharArray(char *str, unsigned long ul);
        static void intToCharArray(char *str, int i);
        static void boolToCharArray(char *str, bool b);
        static void floatToCharArray(char *str, float f, int length, int lengthAfterPoint);
        
		static int charArrayToInt(const char *str);
		static long charArrayToLong(const char *str);
		static bool charArrayToBool(const char *str);
		static float charArrayToFloat(const char *str);
		static unsigned long charArrayToUnsignedLong(const char *str);

};

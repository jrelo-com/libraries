#pragma once
#include <Arduino.h>


class TypeConverter {

    public :

        static void longToCharArray(char *str, long l);
        static void unsignedLongToCharArray(char *str, unsigned long ul);
        static void intToCharArray(char *str, int i);
        static void boolToCharArray(char *str, bool b);
        static void floatToCharArray(char *str, float f, int length, int lengthAfterPoint);
		static int charArrayToInt(char *str);
		static long charArrayToLong(char *str);
		static bool charArrayToBool(char *str);
		static float charArrayToFloat(char *str);
		static unsigned long charArrayToUnsignedLong(char *str);

};

#include <TypeConverter.h>


static void TypeConverter::longToCharArray(char *str, long l) {
    sprintf(str, "%ld", l);
}

static void TypeConverter::unsignedLongToCharArray(char *str, unsigned long ul) {
    sprintf(str, "%lu", ul);
}

static void TypeConverter::intToCharArray(char *str, int i) {
    sprintf(str, "%d", i);
}

static void TypeConverter::boolToCharArray(char *str, bool b) {
    if(b)
        strcpy(str, "true");
    else
        strcpy(str, "false");
}

static void TypeConverter::floatToCharArray(char *str, float f, int length, int lengthAfterPoint) {
    dtostrf(f, length, lengthAfterPoint, str);
}

static int TypeConverter::charArrayToInt(char *str) {
    return atoi(str);
}

static long TypeConverter::charArrayToLong(char *str) {
    return atol(str);
}

static bool TypeConverter::charArrayToBool(char *str) {
    if(strcmp(str, "true") == 0)
        return true;
    else
        return false;
}

static float TypeConverter::charArrayToFloat(char *str) {
    return atof(str);
}

static unsigned long TypeConverter::charArrayToUnsignedLong(char *str) {
    return strtoul(str, NULL, 0);
}

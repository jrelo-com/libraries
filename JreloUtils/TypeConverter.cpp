#include <TypeConverter.h>


void TypeConverter::longToCharArray(char *str, long l) {
    sprintf(str, "%ld", l);
}

void TypeConverter::unsignedLongToCharArray(char *str, unsigned long ul) {
    sprintf(str, "%lu", ul);
}

void TypeConverter::intToCharArray(char *str, int i) {
    sprintf(str, "%d", i);
}

void TypeConverter::boolToCharArray(char *str, bool b) {
    if(b)
        strcpy(str, "true");
    else
        strcpy(str, "false");
}

void TypeConverter::floatToCharArray(char *str, float f, int length, int lengthAfterPoint) {
    dtostrf(f, length, lengthAfterPoint, str);
}



int TypeConverter::charArrayToInt(const char *str) {
    return atoi(str);
}

long TypeConverter::charArrayToLong(const char *str) {
    return atol(str);
}

bool TypeConverter::charArrayToBool(const char *str) {
    if(strcmp(str, "true") == 0)
        return true;
    else
        return false;
}

float TypeConverter::charArrayToFloat(const char *str) {
    return atof(str);
}

unsigned long TypeConverter::charArrayToUnsignedLong(const char *str) {
    return strtoul(str, NULL, 0);
}

#include <RAM.h>

int RAM::free() {
    extern int __heap_start, *__brkval;
    int v;
    int fr = (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
    return fr;
}

#include <WDT.h>

bool WDT::flag = false;

void WDT::reset() {
    if(flag)
        wdt_reset();
}

void WDT::start() {
    if(flag)
        wdt_enable(WDTO_8S);
}

void WDT::stop() {
    if(flag)
        wdt_disable();
}

void WDT::use(bool flag) {
    WDT::flag = flag;
}

bool WDT::isUsed() {
    return flag;
}

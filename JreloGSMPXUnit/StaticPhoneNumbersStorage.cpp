#include <StaticPhoneNumbersStorage.h>

StaticPhoneNumbersStorage::StaticPhoneNumbersStorage(const char *phoneNumbers) {
    this->phoneNumbers = phoneNumbers;
}

StaticPhoneNumbersStorage::~StaticPhoneNumbersStorage() {}

void StaticPhoneNumbersStorage::getPhoneNumbers(StringBuffer *stringBuffer) {
    stringBuffer->appendString(phoneNumbers);
}


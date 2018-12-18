#include <StringBox.h>


StringBox::StringBox(int length) {
    this->memoryLength = length;
}
/*
 *
 *
 *
 * */
StringBox::StringBox() {
    this->memoryLength = 512;
}
/*
 *
 *
 *
 * */
StringBox::~StringBox() {
    free(this->memory);
}
/*
 *
 *
 *
 * */
void StringBox::init(int memoryLength) {
    this->memoryLength = memoryLength;
    init();
}
/*
 *
 *
 *
 * */
int StringBox::getMemoryLength() {
    return this->memoryLength;
}
/*
 *
 *
 *
 * */
void StringBox::init() {
    if(this->memory != NULL) {
        Serial.println(F("\r\nStringBox. Already initialized !"));
        return;
    }

    this->memory = (char*)malloc(memoryLength);
    memset(this->memory, '\0', memoryLength);
}
/*
 *
 *
 *
 * */
int StringBox::getTicket(int size) {

    if(this->memory == NULL) {
        Serial.println(F("\r\nStringBox. Not initialized !"));
        return 0;
    }

    if(size == 0) {
        return 0;
    }

#ifdef DEBUG
    Serial.print(F("\r\nStringBox. New ticket ... "));
    Serial.print(F("Requests "));
    Serial.print(size);
    Serial.print(F(" characters"));
#endif

    int ticketNumber = 0;
    for(int i = 1; i < 128; i++) {
        if(!tickets[i]) {
            tickets[i] = true;
            ticketNumber = i;
            break;
        }
    }

    if(ticketNumber == 0) {
        Serial.println(F("\r\nStringBox. No tickets available ! "));
        delay(10000);
        return 0;
    }

    ticketNumber *= -1;
    size += 3;

    bool x = false;
    int begin = -1;
    int end = -1;
    bool result = false;

    bool defragmentationFlag = false;

    while(true) {
        for(int i = 0, c = 0; i < memoryLength; i++, c++) {

            if(begin != -1 && c == size) {

                end = i - 1;
                result = true;
                break;
            }

            if(!x && memory[i] < 0) {
                begin = -1;

                x = true;
                continue;
            }

            if(x && memory[i] < 0) {
                x = false;
                begin = -1;

                continue;
            }

            if(x) {
                continue;
            }

            if(begin == -1 && !x) {
                begin = i;

                c = 0 ;
                continue;
            }
        }

        if(result) {
            break;
        } else {
            if(!defragmentationFlag) {
                defragmentationFlag = true;
                defragmentation();
            } else {
                Serial.println(F("\r\nStringBox. Defragmentation did not help! "));
                showMemory();
                return 0;
            }
        }

    }

    memory[begin] = ticketNumber;
    memory[end] = ticketNumber;
    memory[end-1] = '\0';
    memset(&memory[begin+1], '\0', end - begin - 1);
    countOfTickets++;

#ifdef DEBUG
    Serial.print(F("\r\nStringBox. New ticket => "));
    Serial.println(ticketNumber);
#endif

    return ticketNumber;
}
/*
 *
 *
 * */
void StringBox::defragmentation() {

    if(countOfTickets == 0)
        return;

#ifdef DEBUG
    showMemory();
    Serial.print(F("\r\nStringBox. Defragmentation. Tickets => "));
    Serial.println(countOfTickets);
#endif

    Item items[countOfTickets];
    int index = 0;

    bool x = false;

    for(int i = 0; i < memoryLength; i++) {

        if(!x && memory[i] < 0) {
            x = true;
            items[index].address = i;
            continue;
        }

        if(x && memory[i] < 0) {
            x = false;
            items[index].length = i - items[index].address + 1;
            index++;

            continue;
        }

        if(x)
            continue;
    }

    int lastAddress = 0;
    for(int i=0; i<countOfTickets; i++) {

        Item item = items[i];

        if(lastAddress == item.address)
            continue;

        for(int j=lastAddress, k = item.address, m = 0; m < item.length; j++, k++, m++) {
            memory[j] = memory[k];
            memory[k] = '\0';
        }
        lastAddress = lastAddress + item.length;
    }


#ifdef DEBUG
    showMemory();
#endif

}
/*
 *
 *
 * */
char* StringBox::getStringByTicket(int ticket) {

    if(ticket == 0)
        return NULL;

    for(int i = 0; i < memoryLength; i++) {
        if(memory[i] == ticket) {
            return &memory[i+1];
        }
    }

    Serial.print(F("\r\nStringBox. Ticket not found ! => "));
    Serial.println(ticket);

    return NULL;
}
/*
 *
 *
 * */
void StringBox::returnTicket(int ticket) {

#ifdef DEBUG
    Serial.print(F("\r\nStringBox. Return ticket => "));
    Serial.println(ticket);
#endif

    if(ticket >= 0)
        return;

    int begin = -1;
    int end = -1;

    for(int i = 0; i < memoryLength; i++) {
        if(memory[i] == ticket) {
            begin = i;
            break;
        }
    }

    if(begin == -1 ) {
		Serial.print(F("\r\nStringBox. Returned ticket not found"));
        return;
    }

    tickets[ticket*-1] = false;

    for(int i = begin + 1; i < memoryLength; i++) {
        if(memory[i] == ticket) {
            end = i;
            break;
        }
    }

    int len = end - begin;
    countOfTickets--;

    memset(&memory[begin], '\0', len + 1);

#ifdef DEBUG
    Serial.println(F("\r\nStringBox. Return ticket => OK"));
#endif
}
/*
 *
 *
 * */
void StringBox::showMemory() {

    Serial.println(F("\r\nStringBox. Memery status."));
    Serial.print(F("\r\nStringBox. Available memory = "));
    Serial.print(availableMemory());
    Serial.println(F(" bytes"));

    int rows = memoryLength / 16;
    int index = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < 16; j++) {
            int x = (int)memory[index];
			if(x > 33 && x < 127)
				Serial.print((char)x);
			else	
				Serial.print(x);
            Serial.print('\t');

            index++;

        }
        Serial.println();
    }
}
/*
 *
 *
 *
 * */
void StringBox::update() {
    if(defragmentationTimer.event()) {
        defragmentation();
    }
}
/*
 *
 *
 * */
int StringBox::availableMemory() {
    for(int i = memoryLength - 1; i >= 0; i--) {
        if(memory[i] < 0 ) {
            return memoryLength - i - 1;
        }
    }
    return memoryLength;
}
/*
 *
 *
 *
 * */
bool StringBox::resizeTicket(int *ticket, int newSize) {
    if(*ticket == 0 || newSize >= (memoryLength - 3) || newSize < 1)
        return false;

    newSize += 3;
    int oldSize = 1;
    bool find = false;
    int lastAddress = -1; // end (index)

    for(int i = 0; i < memoryLength; i++) {
        if(memory[i] == *ticket) {
            if(!find) {
                find = !find;
            } else {
                lastAddress = i;
                break;
            }
        }

        if(find)
            oldSize++;
    }

    if(oldSize == newSize)
        return false;

    if(oldSize > newSize) {

        int x = newSize - oldSize;
        for(int i = lastAddress+x; i <= lastAddress ; i++) {
            memory[i] = 0;
        }
        memory[lastAddress+x-1] = 0;
        memory[lastAddress+x] = *ticket;


        return true;
    }

    if(oldSize < newSize) {

        int x = newSize - oldSize;
        int availableSize = 0;
        int prolong = false;

        for(int i=lastAddress + 1; i < memoryLength; i++) {
            if(memory[i] == 0) {
                availableSize++;
                if(availableSize == x) {
                    prolong = true;
                    break;
                }
            } else {
                break;
            }
        }

        if(prolong) {
            for(int i = lastAddress; i < lastAddress + x; i++) {
                memory[i] = 0;
            }
            
            memory[lastAddress + x] = *ticket; 

        } else {

            int newTicket = getTicket(newSize - 3);
            if(newTicket == 0){
                return false;
			}

            char *newPartOfMemory = getStringByTicket(newTicket);
            char *oldPartMemory = getStringByTicket(*ticket);
            strcpy(newPartOfMemory, oldPartMemory);

            returnTicket(*ticket);
            *ticket = newTicket; 
        }

    }

    return true;
}


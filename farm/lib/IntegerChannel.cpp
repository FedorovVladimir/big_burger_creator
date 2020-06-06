//
// Created by vladimir on 20.05.2020.
//

#include "IntegerChannel.h"

IntegerChannel::IntegerChannel(const char *name) {
    char nameSemAvailable[20] = "semAvailable_";
    strcat(nameSemAvailable, name);
    this->semAvailable = new BinarySemaphore(nameSemAvailable, 1);

    this->fileMem = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, name);
    if (this->fileMem == nullptr) {
        this->fileMem = CreateFileMapping((HANDLE) 0xFFFFFFFFF, nullptr, PAGE_READWRITE, 0, 4096, name);
    }

    if (this->fileMem != nullptr) {
        this->buffer = (int *) (MapViewOfFile(this->fileMem, FILE_MAP_ALL_ACCESS, 0, 0, 4096));
    }

    *(this->buffer) = 0;
}

IntegerChannel::~IntegerChannel() {
    delete semAvailable;
    CloseHandle(this->fileMem);
}

void IntegerChannel::setData(int n) {
    this->semAvailable->Down();
    *(this->buffer) = n;
    this->semAvailable->Up();
}

int IntegerChannel::getData() const {
    this->semAvailable->Down();
    int n = *(this->buffer);
    *(this->buffer) = 0;
    this->semAvailable->Up();
    return n;
}

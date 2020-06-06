//
// Created by vladimir on 20.05.2020.
//

#include "BinarySemaphore.h"

BinarySemaphore::BinarySemaphore(const char *name, int startState) {
    sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, name);
    int s = (startState > 0);
    if (sem == nullptr) {
        sem = CreateSemaphore(nullptr, s, 1, name);
    }
}

BinarySemaphore::~BinarySemaphore() {
    CloseHandle(sem);
}

bool BinarySemaphore::Up() {
    LONG prev;
    ReleaseSemaphore(sem, 1, &prev);
    return prev == 0;
}

bool BinarySemaphore::Down(DWORD milliseconds) {
    DWORD result = WaitForSingleObject(sem, milliseconds);
    return result != WAIT_TIMEOUT;
}

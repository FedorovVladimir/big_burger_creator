//
// Created by vladimir on 21.05.2020.
//

#include "IntegerSemaphore.h"

IntegerSemaphore::IntegerSemaphore(const char *name, int startState, int maxState) {
    sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, name);
    if (sem == nullptr) {
        sem = CreateSemaphore(nullptr, startState, maxState, name);
    }
}

IntegerSemaphore::~IntegerSemaphore() {
    CloseHandle(sem);
}

void IntegerSemaphore::Up(int n) {
    ReleaseSemaphore(sem, n, nullptr);
}

bool IntegerSemaphore::Down(DWORD milliseconds) {
    DWORD result = WaitForSingleObject(sem, milliseconds);
    return result != WAIT_TIMEOUT;
}

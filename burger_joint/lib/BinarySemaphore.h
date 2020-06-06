//
// Created by vladimir on 20.05.2020.
//

#ifndef PARALLEL_5_THREADS_BINARYSEMAPHORE_H
#define PARALLEL_5_THREADS_BINARYSEMAPHORE_H

#include <windows.h>

class BinarySemaphore {
private:
    HANDLE sem;
public:
    explicit BinarySemaphore(const char *name, int startState = 0);

    ~BinarySemaphore();

    bool Up();

    bool Down(DWORD milliseconds = INFINITE);
};


#endif //PARALLEL_5_THREADS_BINARYSEMAPHORE_H

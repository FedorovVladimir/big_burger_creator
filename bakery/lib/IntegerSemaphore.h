//
// Created by vladimir on 21.05.2020.
//

#ifndef PARALLEL_5_THREADS_INTEGERSEMAPHORE_H
#define PARALLEL_5_THREADS_INTEGERSEMAPHORE_H

#include <windows.h>

class IntegerSemaphore {
private:
    HANDLE sem;
public:
    explicit IntegerSemaphore(const char *name, int startState = 0, int maxState = 6);

    ~IntegerSemaphore();

    void Up(int n);

    bool Down(DWORD milliseconds = INFINITE);
};


#endif //PARALLEL_5_THREADS_INTEGERSEMAPHORE_H

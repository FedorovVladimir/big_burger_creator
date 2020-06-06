//
// Created by vladimir on 20.05.2020.
//

#ifndef PARALLEL_5_THREADS_INTEGERCHANNEL_H
#define PARALLEL_5_THREADS_INTEGERCHANNEL_H


#include "BinarySemaphore.h"

class IntegerChannel {
private:
    BinarySemaphore *semAvailable;
    HANDLE fileMem;
    int *buffer;
public:
    explicit IntegerChannel(const char *name);

    void setData(int n);

    int getData() const;

    ~IntegerChannel();
};


#endif //PARALLEL_5_THREADS_INTEGERCHANNEL_H

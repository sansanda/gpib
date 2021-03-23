#ifndef CALLBACKFUNCTIONS_H
#define CALLBACKFUNCTIONS_H

#include "iostream"

inline int __stdcall cb(int ud, int LocalIbsta, int LocalIberr, long LocalIbcntl,void *RefData)
{
    std::cout<<"Sfdsfdfdsds";
    return 0;
}

#endif // CALLBACKFUNCTIONS_H

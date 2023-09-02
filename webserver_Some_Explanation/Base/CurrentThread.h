#pragma once
#include <stdint.h>

namespace CurrentThread {
    // internal
    extern __thread int t_cachedTid;  // __thread 是一种线程局部存储（Thread Local Storage，TLS）的关键字，表示该变量在每个线程中都有一个独立的副本。
    extern __thread char t_tidString[32];
    extern __thread int t_tidStringLength;
    extern __thread const char* t_threadName;
    void cacheTid();
    inline int tid()
    {
        if (__builtin_expect(t_cachedTid == 0, 0)) 
        {
                cacheTid();
        }
        return t_cachedTid;
    }

    inline const char* tidString()
    {
        return t_tidString;
    }

    inline int tidStringLength()
    {
        return t_tidStringLength;
    }

    inline const char* name()
    {
        return t_threadName;
    } 
}
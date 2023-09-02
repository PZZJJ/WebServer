#pragma once
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <cstdint>
#include "MutexLock.h"
#include "noncopyable.h"

class Condition : noncopyable {
    public:
    explicit Condition (MutexLock &_mutex) : mutex(_mutex) {
        pthread_cond_init (&cond, NULL);
    }

    ~Condition() {
        pthread_cond_destroy(&cond);
    }

    void wait() {
        pthread_cond_signal(&cond);
    }

    void notify() {
        pthread_cond_broadcast(&cond);
    }

    void notifyAll(){
        pthread_cond_broadcast(&cond);
    }

    bool waitForSeconds (int seconds) {
        struct timespec abstime;      // the time you want to stop waiting, not how long you want to wait
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&cond, mutex.get(), &abstime);    /*#define	ETIMEDOUT	60   Connection timed out */
    }

    private:
    MutexLock &mutex;
    pthread_cond_t cond;

};
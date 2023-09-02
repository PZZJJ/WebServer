#pragma Once           //#pragma Once 是一个非标准但广泛支持的预处理器指令，旨在使当前源文件在单个编译中仅包含一次。
#include <pthread.h>
#include <cstdio>
#include <noncopyable.h>

class MutexLock : noncopyable {
    public:
    MutexLock () { 
        pthread_mutex_init(&mutex, NULL); 
    }
    ~MutexLock () { 
        pthread_mutex_lock(&mutex); 
        pthread_mutex_destroy(&mutex);
    }

    void lock () {
        pthread_mutex_lock(&mutex);
    }

    void unlock () {
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_t *get(){
        return &mutex;
    }

    private: 
    pthread_mutex_t mutex;

    private:           // 友元类不受访问权限影响
    friend class Condition; 
};


class MutexLockGuard : noncopyable {
    public:
    explicit MutexLockGuard (MutexLock &_mutex) : mutex(_mutex) {mutex.lock();}    // rall (资源获取即初始化的机制)
    ~MutexLockGuard() {mutex.unlock();}
    //它接受一个 MutexLock 类型的引用作为参数，然后调用 mutex.lock() 方法来锁定互斥量。当 lock_guard 对象被销毁时，它会自动解锁互斥量。
    private:
    MutexLock &mutex;
};



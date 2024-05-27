#ifndef _START_MUTEX_H_
#define _START_MUTEX_H_

#include <pthread.h>

namespace start {
// 互斥量
class Mutex{
public:
    Mutex() {
        pthread_mutex_init(&m_mutex, nullptr);
    }

    ~Mutex() {
        pthread_mutex_destroy(&m_mutex);
    }

    void lock() {
        pthread_mutex_lock(&m_mutex);
    }

    void unlock() {
        pthread_mutex_unlock(&m_mutex);
    }

    pthread_mutex_t* get() { return &m_mutex; }

private:
    pthread_mutex_t m_mutex;
};

// 读写锁
class RWMutex {
public:
    RWMutex() {
        pthread_rwlock_init(&m_lock, nullptr);
    }

    ~RWMutex() {
        pthread_rwlock_destroy(&m_lock);
    }

    void rdlock() {
        pthread_rwlock_rdlock(&m_lock);
    }

    void wrlock() {
        pthread_rwlock_wrlock(&m_lock);
    }

    void unlock() {
        pthread_rwlock_unlock(&m_lock);
    }

    pthread_rwlock_t* get() { return &m_lock; }

private:
    pthread_rwlock_t m_lock;
};

// 自动加锁
class MutexGuard {
public:
    MutexGuard(Mutex &mutex)
        : m_mutex(mutex) {
        m_mutex.lock();
        m_locked = true;
    }

    ~MutexGuard() {
        unlock();
    }

    void unlock() {
        if(m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }

private:
    Mutex &m_mutex;
    bool m_locked;
};

// 自动读锁
class RWMutexReadGuard {
public:
    RWMutexReadGuard(RWMutex &mutex)
        : m_mutex(mutex) {
        m_mutex.rdlock();
        m_locked = true;
    }

    ~RWMutexReadGuard() {
        unlock();
    }

    void unlock() {
        if(m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }

private:
    RWMutex &m_mutex;
    bool m_locked;
};

// 自动写锁
class RWMutexWriteGuard {
public:
    RWMutexWriteGuard(RWMutex &mutex)
        : m_mutex(mutex) {
        m_mutex.wrlock();
        m_locked = true;
    }

    ~RWMutexWriteGuard() {
        unlock();
    }

    void unlock() {
        if(m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }

private:
    RWMutex &m_mutex;
    bool m_locked;
};


}

#endif // _START_MUTEX_H_
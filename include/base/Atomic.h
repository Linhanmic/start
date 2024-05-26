#ifndef _START_ATOMIC_H_
#define _START_ATOMIC_H_

#include "Noncopyable.h"

namespace start {
template <typename T>
class Atomic : Noncopyable
{
public:
    Atomic() : m_value(0) {}
    Atomic(T value) : m_value(value) {}
    ~Atomic() {}

    T get() { return __sync_val_compare_and_swap(&m_value, 0, 0); }
    T getAndAdd(T x) { return __sync_fetch_and_add(&m_value, x); }
    T addAndGet(T x) { return getAndAdd(x) + x; }
    T incrementAndGet() { return addAndGet(1); }
    T decrementAndGet() { return addAndGet(-1); }
    void add(T x) { getAndAdd(x); }
    void increment() { incrementAndGet(); }
    void decrement() { decrementAndGet(); }
    T getAndSet(T newValue) { return __sync_lock_test_and_set(&m_value, newValue); }

private:
    volatile T m_value;
};
}


#endif // _START_ATOMIC_H_
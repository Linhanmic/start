#include "../../include/base/Thread.h"
#include "../../include/base/Mutex.h"
#include <stdexcept> // std::logic_error
#include <cstdio> // snprintf

namespace start {

// 线程计数器
Atomic<int> Thread::m_threadCount(0);
// 记录当前线程
thread_local Thread* Thread::m_currentThread = nullptr;

Thread::Thread(const std::string &name, const ThreadFunc &func)
    : m_name(name),
      m_id(m_threadCount.incrementAndGet()),
      m_func(std::move(func)),
      m_thread(0),
      m_started(false),
      m_joined(false),
      m_parentThread(m_currentThread){   
    setName();
    start();
}

Thread::~Thread() {
    if(m_thread) {
        pthread_detach(m_thread);
        m_threadCount.decrementAndGet();
    }
}

void* Thread::runThread(void *arg) {
    Thread *thread = static_cast<Thread*>(arg);
    m_currentThread = thread;
    thread->m_semaphore.notify();// 通知线程已经开始
    thread->m_func();
    m_currentThread = thread->m_parentThread;
    return nullptr;
}

void Thread::start() {
    if(!m_started) {
        m_started = true;
        int ret = pthread_create(&m_thread, nullptr, runThread, this);
        if(ret) {
            m_started = false;
            throw std::logic_error("pthread_create error");
        }else {
            m_semaphore.wait();// 等待线程真正开始
        }
    }
}

void Thread::join() {
    if(m_started && !m_joined) {
        m_joined = true;
        pthread_join(m_thread, nullptr);
    }
}

void Thread::setName() {
    int num = m_threadCount.get();
    if(m_name.empty()) {
        m_name = "start::Thread_" + std::to_string(num);
    }
}

Thread* Thread::getThis() {
    if (m_currentThread == nullptr) {
        m_currentThread = new Thread("main", [](){});
    }
    return m_currentThread;
}

bool Thread::isMainThread() {
    return m_currentThread == nullptr;
}

} // namespace start
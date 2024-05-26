#ifndef _START_THREAD_H_
#define _START_THREAD_H_

#include "Noncopyable.h"
#include "Semaphore.h"
#include "Atomic.h"
#include <pthread.h>
#include <functional>
#include <memory> // std::shared_ptr
#include <string>


namespace start {
class Thread : Noncopyable
{
public:
    // 线程函数, 通过bind可以实现带参数的线程函数
    typedef std::function<void()> ThreadFunc;
    // 智能指针, 用于管理Thread对象, 避免内存泄漏（动态分配的内存没有释放）
    typedef std::shared_ptr<Thread> ThreadPtr;

    Thread(const std::string &name, const ThreadFunc &func);
    ~Thread();

    // 开始线程
    void start();
    // 等待线程结束
    void join();
    // 获取当前线程指针
    static Thread* getThis();
    static int getThreadCount() { return m_threadCount.get(); }
    static void* runThread(void *arg);
    static bool isMainThread();

    // 获取和设置线程属性
    const std::string &getName() const { return m_name; }
    void setName(const std::string &name) { m_name = name; }
    pid_t getId() const { return m_id; }

    // 线程是否开始和加入
    bool started() const { return m_started; }
    bool joined() const { return m_joined; }

private:
    void setName();

    // 线程名称
    std::string m_name;
    // 线程ID
    pid_t m_id;
    // 线程函数
    ThreadFunc m_func;
    // 线程结构体
    pthread_t m_thread;
    // 线程是否开始
    bool m_started;
    // 线程是否加入
    bool m_joined;
    // 信号量
    Semaphore m_semaphore;

    Thread *m_parentThread;
    static thread_local Thread *m_currentThread;
    static Atomic<int> m_threadCount;
};
}



#endif
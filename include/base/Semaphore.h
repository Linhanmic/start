#ifndef _START_SEMAPHORE_H_
#define _START_SEMAPHORE_H_

#include "Noncopyable.h"

#include <semaphore.h>
#include <stdint.h> // uint32_t

namespace start {
class Semaphore : Noncopyable {
public:
    /**
     * @brief 构造函数
     * @param[in] count 信号量值的大小
     */
    Semaphore(uint32_t count = 0);

    /**
     * @brief 析构函数
     */
    ~Semaphore();

    /**
     * @brief 获取信号量
     */
    void wait();

    /**
     * @brief 释放信号量
     */
    void notify();
private:
    sem_t m_semaphore;
};
}
#endif // _START_SEMAPHORE_H_

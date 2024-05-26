#ifndef _START_NONCOPYABLE_H_
#define _START_NONCOPYABLE_H_
namespace start {
class Noncopyable
{
public:
	// 禁止拷贝构造函数和赋值运算符
    Noncopyable(const Noncopyable &) = delete;
    void operator=(const Noncopyable &) = delete;
protected:
	// 因为不希望用户自己创建对象，所以将构造函数和析构函数设为私有
	Noncopyable() = default;
	~Noncopyable() = default;
};
}
#endif
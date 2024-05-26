#include "../include/base/Thread.h"
#include <iostream>

using namespace std;
using namespace start;

void sing(string name) {
    cout << "I am singing " << name << endl;
    Thread *thread = Thread::getThis();
    cout << "thread name: " << thread->getName() << endl;
    cout << "thread id: " << thread->getId() << endl;
}


void hello() {
    cout << "Hello, world!" << endl;
    Thread *thread = Thread::getThis();
    cout << "thread name: " << thread->getName() << endl;
    cout << "thread id: " << thread->getId() << endl;
 
}


int main() {
    Thread *threadMain = Thread::getThis();
    cout << "thread name: " << threadMain->getName() << endl;
    cout << "thread id: " << threadMain->getId() << endl;
    Thread::ThreadPtr thread(new Thread("hello", hello));
    thread->start();
    thread->join();
    Thread::ThreadPtr thread2(new Thread("sing", bind(sing, "music")));
    thread2->start();
    thread2->join();
    Thread::ThreadPtr thread3(new Thread("sing", bind(sing, "song")));
    thread3->start();
    thread3->join();

 
    return 0;
}
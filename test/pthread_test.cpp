#include <iostream>
#include <pthread.h>
#include "../include/base/Semaphore.h"
using namespace std;
start::Semaphore s(0);
void hello() {
    s.wait();
    cout << "Hello, world!" << endl;
    
}

int main() {

    pthread_t tid;
    pthread_create(&tid, nullptr, (void*(*)(void*))hello, nullptr);
    pthread_join(tid, nullptr);
    return 0;
}
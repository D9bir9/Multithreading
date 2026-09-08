// TOPIC: lock_guard in C++ (std::lock_guard<mutex> lock(m1))

// Notes:
// 0. It is very light weight wrapper for owning mutex on scoped basis.
// 1. It aquires mutex lock the moment you create the object of lock_guard.
// 2. It automatically removes the lock when out of scope.
// 3. You can not explicitely unlock the lock_guard.
// 4. You can not copy lock_guard.

#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1;
int buffer{};

void task(const char* threadNumber, int loopFor){
    std::lock_guard<std::mutex> lock(m1);
    for (int i{}; i < loopFor; ++i){
        buffer++;
        std::cout << threadNumber << ": "<< buffer << std::endl;
    }
}

int main(){
    std::thread t1(task, "T0", 10);
    std::thread t2(task, "T1", 10);

    t1.join();
    t2.join();

    return 0;

}
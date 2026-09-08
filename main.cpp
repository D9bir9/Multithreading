// TOPIC: unique_lock in C++ (std::unique_lock<mutex> lock(m1))

// Notes:
// 1. The class unique_lock is a mutex ownersiop wrapper.
// 2. It allows:
//    a. having different locking strategies
//    b. time-constrained attepts at locking (try_lock_for, try_lock_until)
//    c. recursive lock
//    d. transfer of lock ownership (move not copy)
//    e. condition variables.

// Locking Strategies
//    Type               Effects
// 1. defer_lock         do not acquire ownership of the mutex
// 2. try_to_lock        try to acquire ownership of the mutex without blocking.
// 3. adopt_lock         assumes the calling thread already has ownership of the mutex.


#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1;
int buffer{};

void task(const char* threadNumber, int loopFor){
    std::unique_lock<std::mutex> lock(m1); // Automatically calls lock on mutex m1
    // std::unique_lock<std::mutex> lock(m1, std::defer_lock); // Does not lock automatically
    // lock.lock();
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
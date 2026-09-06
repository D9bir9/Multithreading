#include <iostream>
#include <mutex>
#include <thread>
// TOPIC: Mutex in C++ Threading | Why use Mutex | What is Race condition and How to solve it? | What is Critical Section

// Mutex: Mutual Exclusion
// Race condition is a situation where two or more threads/process happened to change a common data at the same time.
// If there is a race condition then we have to protect it and the protected section is called critical section/region.

// MUTEX:
// Mutex is used to avoid race condition.
// We use lock(), unlock() on mutex to avoid race condition.

int myAmount{};
std::mutex m;

void addMoney(){
    m.lock();
    ++myAmount; // Critical region
    m.unlock();
}

int main(){
    std::thread t1(addMoney);
    std::thread t2(addMoney);

    t1.join();
    t2.join();

    std::cout << myAmount << "\n";
    return 0;
}
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

// std::mutex::try_lock() on Mutex in Threading

// try_lock() Tries to lock the mutex. Returns immediately. On successful lock acquisition returns true otherwise returns false.
// If try_lock() is not able to lock mutex, then it doesn't get blocked that's why it is called non-blocking.
// If try_lock() is called again by the same thread which owns the mutex, the behaviour is undefined.
// It is a dead lock situation with undefined behaviour. (if you want to be able to lock the same mutex by the same thread
// more than one time then go for recursive mutex)

int counter{};
int thread1{};
int thread2{};
std::mutex mtx;
void increaseTheCounterFor100000Time1(){
    for (int i{}; i < 100000; ++i){
        if (mtx.try_lock()){
            ++thread1;
            ++counter;
            mtx.unlock();
        }
    }
}
void increaseTheCounterFor100000Time2(){
    for (int i{}; i < 100000; ++i){
        if (mtx.try_lock()){
            ++thread2;
            ++counter;
            mtx.unlock();
        }
    }
}


int main(){
    std::thread t1(increaseTheCounterFor100000Time1);
    std::thread t2(increaseTheCounterFor100000Time2);

    t1.join();
    t2.join();

    std::cout << "thread1: " << thread1 << std::endl;
    std::cout << "thread2: " << thread2 << std::endl;
    std::cout << "counter could increase upto: " << counter << "\n";
    return 0;
}
// There are so many try_lock function
//1. std::try_lock
//2. std::mutex::try_lock
//3. std::shared_lock::try_lock
//4. std::timed_mutex::try_lock
//5. std::unique_lock::try_lock
//6. std::shared_mutex::try_lock
//7. std::recursive_mutex::try_lock
//8. std::shared_timed_mutex::try_lock
//9. std::recursive_timed_mutex::try_lock
// TOPIC: Recursive Mutex in C++ (std::recursive_mutex);

// Notes:
// 0. It is same as mutex, but same thread can lock mutex multiple times using recursive mutex.
// 1. If thread T1 first call lock/try_lock on recursive mutex m1, then m1 is locked by T1, now
//    as T1 is running in recursion T1 cn call lock/try_lock any number of times.
// 2. But if T1 have aquired 10 times lock/try_lock on mutex m1, then thread T1 will have to unlock
//    it 10 times otherwise no other thread will be able to lock mutex m1.
//    It means recursive_mutex keeps count how many times it was locked, so it should be unlocked the
//    same amount of time.
// 3. The maximum number of times we can lock a recursive_mutex is not defined, but when that reaches,
//    if we call lock it will return std::system_error OR if we call try_lock() then it will return false.

// BOTTOM LINE;
// 0. It is similar to mutex but have extra facility that it can be locked multiple times by the same thread
// 1. If we can avoid recursive mutex then we should because it brings overhead to the system.
// 2. It can be used in loops also.

#include <iostream>
#include <thread>
#include <mutex>

// Example: with recursion

std::recursive_mutex m1;
int buffer = 0;

void recursion(char c, int loopFor){
    if (loopFor < 0) return;

    m1.lock();
    std::cout << c << " " << buffer++ << std::endl;
    recursion(c, --loopFor);
    m1.unlock();
}

int main(){
    std::thread t1(recursion, '0', 10);
    std::thread t2(recursion, '1', 10);
    t1.join();
    t2.join();

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
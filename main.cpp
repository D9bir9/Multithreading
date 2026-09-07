//Topic: Timed Mutex In C++ Threading (std::timed_mutex)
// We have learneed Mutex, Race Condition, Critical Section
// Notes:
// std::timed_mutex is blocked till timeout_time or the lock is aquired and returns true if success
// otherwise false.
// Member Function:
// a. lock
// b. try_lock
// c. try_lock_for   ---\ These two functions makes it different for mutex.
// d. try_lock_until ---/
// e. unlock

// Examples: try_lock_for();
// Waits until specific timeout_duration has elapsed or the lock is aquired, whichever comes first.
// On successful lock acquisition returns true, otherwise returns false.

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int myAmount{};
std::timed_mutex m;

void increment(int id){
    if (m.try_lock_for(std::chrono::seconds(2))){
        ++myAmount;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Thread " << id << " Entered\n";
        m.unlock();
    }
    else{
        std::cout << "Thread " << id << " Couldn't Enter\n";
    }
}

int main(){

    std::thread t1(increment, 1);
    std::thread t2(increment, 2);

    t1.join();
    t2.join();


    std::cout << "Amount: " << myAmount << "\n";
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
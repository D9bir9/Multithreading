#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

// std::try_lock() in c++20 Threading
// std::try_lock() tries to lock all the lockable objects passed in it one by one in given order.
// Syntax: std::try_lock(m1, m2, m3, m4, m5, ..., mn);

// On success this function returns -1 otherwise it will return 0-based mutex index number which it could not lock.
// If it fails to lock any of the mutex then it will release all the mutex it locked before.
// If a call to try_lcok results in an exception, unlock is called for any locked objects before rethrowing

int x{}, y{};
std::mutex m1, m2;

void seconds_work(int seconds){
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void xy_increment(int& x_y, std::mutex& m, const char* desc){
    for (int i{}; i < 5; ++i){
        m.lock();
        ++x_y;
        std::cout << desc << " " << x_y << "\n";
        m.unlock();
        seconds_work(1);
    }
}

void consume_xy(){
    int useCount{5};
    int x_y_sum{};
    while(useCount){
        int lockResult = std::try_lock(m1, m2);
        if (lockResult == -1){
            if (x && y){
                --useCount;
                x_y_sum += x + y;
                x = y = 0;
                std::cout <<  "x + y : " << x_y_sum << "\n";
            }
            m1.unlock();
            m2.unlock();
        }
    }
}


int main(){
    std::thread t1(xy_increment, std::ref(x), std::ref(m1), "x");
    std::thread t2(xy_increment, std::ref(y), std::ref(m2), "y");
    std::thread t3(consume_xy);

    t1.join();
    t2.join();
    t3.join();
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
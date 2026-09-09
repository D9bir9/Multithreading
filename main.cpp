// TOPIC: Condition Variable In C++ Threading

// IMPORTANT POINT: CV are used for two purposes
// A. Notify other threads
// B. Waiting for some conditions

// 1. Condition Variable allows running threads to wait on some conditions, and once those conditions are met, the waiting thread 
//    is notified using:
//      a. notify_one();
//      b. notify_all();
// 2. You need mutex to use condition variable.
// 3. If some thread want to wait on some condition, then it has to do these things:
//      a. Acquire the mutex lock using std::uniqui_lock<std::mutex> lock(m);.
//      b. Execute wait, wait_for, or wait_until. The wait operation atomically release the mutex
//         and suspend the execution of the thread.
//      c. When the condition variable is notified, the thread is awakened, and the mutex is atomically reacquired.
//         The thread should then check the condition and release waiting if the wakeup was spurious

// NOTE:
// 1. Condition variables are used to synchronize two or more threads.
// 2. Best use case of condition variable is Producer/Consumer problem. 

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable cv;
std::mutex m;
long balance = 0;

void addMoney(int amount){
    std::lock_guard<std::mutex> lg(m);
    if (amount > 0) {
        balance += amount;
        std::cout << amount 
        << " deposited successfully!\nCurrent Balance : " 
        << balance << std::endl;
        cv.notify_one();
    }
    else{
        std::cout << "Amount Must be greater than 0\n";
    }
}

void withdrawMoney(int amount){
    std::unique_lock<std::mutex> ul(m);
    cv.wait(ul, []{return (balance!=0)? true : false;});
    if (balance >= amount){
        balance -= amount;
        std::cout << amount 
        << " withdrawn successfully!\n";
    }
    else{
        std::cout << "Insufficient balance\n";
    }
    std::cout << "Current Balance : " 
        << balance << std::endl;
}

int main(){
    std::thread t1(withdrawMoney, 500);
    std::thread t2(addMoney, 500);
    t1.join();
    t2.join();

    return 0;
}
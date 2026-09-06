#include <iostream>
#include <chrono>
#include <thread>

//JOIN
// Once a thread is started, we call join to wait for it to finish.
// DETACH
// This is used to detach newly created thread from the parent thread
void run(int count){
    while (count-- > 0){
        std::cout << count << " Arch btw!\n";
    }
    std::this_thread::sleep_for((std::chrono::seconds(5)));
    std::cout << "thread finished\n";
}
int main(){

    std::thread t1(run, 10);
    std::cout << "main()\n";
    t1.detach();
    std::cout << "main() after\n";
    return 0;
}
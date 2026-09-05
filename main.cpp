#include <iostream>
#include <thread>
#include <chrono>

class Base{
    public:
        void run(int x){
            while (x-- > 0){
                std::cout << x << "\n";
            }
        }
};



int main(int argc, char *argv[]){
    auto start_time = std::chrono::high_resolution_clock::now();
    Base b;
    std::thread t(&Base::run, &b, 1000000);
    t.join();
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);

    std::cout << "s: " << duration.count()/1000 << std::endl;

    return 0;
}
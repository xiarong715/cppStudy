#include <iostream>
#include <thread>
#include <mutex>

void t1() {
    for (int i = 0; i < 10; i++) {
        std::cout << "t1" << std::endl;
    }
}

void t2() {
    for (int i = 0; i < 10; i++) {
        std::cout << "t2" << std::endl;
    }
}

int main() {
    std::thread th1(t1);
    std::thread th2(t2);

    th1.join();
    th2.join();

    std::cout << "main() end" << std::endl;
    return 0;
}
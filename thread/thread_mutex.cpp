#include <iostream>
#include <mutex>
#include <thread>

int cnt = 100000;
std::mutex mtx;

void t1() {
    while (cnt > 0) {
        mtx.lock();
        if (cnt > 0) {
            cnt--;
            std::cout << cnt << std::endl;
        }
        mtx.unlock();
    }
}

int main() {
    std::thread th1(t1);
    std::thread th2(t1);
    std::thread th3(t1);
    std::thread th4(t1);
    std::thread th5(t1);

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();

    std::cout << "main() end" << std::endl;
    return 0;
}
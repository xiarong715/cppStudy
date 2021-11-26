#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <assert.h>

// producer and consumer mode
// share data

// max = 10
int data = 0;
const int max = 10;
std::mutex mtx;
std::condition_variable cv;

// produce data
void producerPost() {
    std::unique_lock<std::mutex> lock(mtx);
    assert(data < max);
    data++;
    lock.unlock();
    cv.notify_one();
}

// consume data
void consumerPost() {
    std::unique_lock<std::mutex> lock(mtx);
    assert(data > 0);
    data--;
    lock.unlock();
    cv.notify_one();
}

int main() {
    std::thread th1(producerPost);
    std::thread th2(consumerPost);

    th1.join();
    th2.join();
    
    std::cout << "main() end" << std::endl;
    return 0;
}
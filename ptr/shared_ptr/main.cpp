#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

void thr_fun(std::shared_ptr<int> p) {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    std::shared_ptr<int> lp = std::move(p); // move 不增加引用计数
    std::cout << "thr_fun lp.get() = " << lp.get() << "\t" << "lp.use_count() = " << lp.use_count() << std::endl;
    std::cout << "thr_fun p.get() = " << p.get() << "\t" << "p.use_count() = " << p.use_count() << std::endl;
}

int main() {
    std::shared_ptr<int> p; // 0
    std::cout << "main p.get() = " << p.get() << "\t" << "p.use_count() = " << p.use_count() << std::endl;
    p = std::make_shared<int>(int(3)); // 1
    std::cout << "main p.get() = " << p.get() << "\t" << "p.use_count() = " << p.use_count() << std::endl;
    std::thread t1(thr_fun, p); // 2， 传递参数，会发生拷贝，增加引用计数
    std::cout << "main p.get() = " << p.get() << "\t" << "p.use_count() = " << p.use_count() << std::endl;
    std::shared_ptr<int> p1; // 0
    p1 = std::move(p); // 2， move 不增加引用计数， move(p)后，p不再托管对象
    std::cout << "main p.get() = " << p.get() << "\t" << "p.use_count() = " << p.use_count() << std::endl;
    std::cout << "main p1.get() = " << p1.get() << "\t" << "p1.use_count() = " << p1.use_count() << std::endl;
    t1.join();
    std::cout << "main p.get() = " << p.get() << "\t" << "p.use_count() = " << p.use_count() << std::endl;
    std::cout << "main p1.get() = " << p1.get() << "\t" << "p1.use_count() = " << p1.use_count() << std::endl;

    std::shared_ptr<int> test = std::make_shared<int>(2);
    std::cout << "main test.get() = " << test.get() << "\t" << "test.use_count() = " << test.use_count() << std::endl;
    test = nullptr;
    std::cout << "main test.get() = " << test.get() << "\t" << "test.use_count() = " << test.use_count() << std::endl;

    // 当释放p1对象时，会释放其指向的int(3)对象
}
#include <iostream>

class Base {
   public:
    Base() { std::cout << "the Base construct called." << std::endl; }
    virtual ~Base() { std::cout << "the Base deconstruct called." << std::endl; }  // base virtual deconstruct
};

class Derived : public Base {
   public:
    Derived() { std::cout << "the Derived construct called." << std::endl; }
    ~Derived() { std::cout << "the Derived deconstruct called." << std::endl; }
};

int main(int argc, char *argv[]) {
    std::cout << "virtual decontruct" << std::endl;
    Base *p = new Derived();
    delete p;
    return 0;
}

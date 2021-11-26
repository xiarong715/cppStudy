#include <iostream>
#include <memory>

class Person {
    std::string name;
    short age;

   public:
    Person() : name(""), age(0) {}
    Person(std::string name, short age) : name(name), age(age) {}
    ~Person() { std::cout << "Person::~Person()" << std::endl; }
    static std::shared_ptr<Person> getInstance() {
        // static std::shared_ptr<Person> inst = std::make_shared<Person>();
        std::shared_ptr<Person> inst = std::make_shared<Person>();
        return inst;
    }
};

int main(int argc, char *argv[]) {
    std::cout << "test static shared_ptr" << std::endl;
    std::shared_ptr<Person> per = Person::getInstance();
    per = nullptr;

    for(;;);
    return 0;
}
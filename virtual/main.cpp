#include "main.h"

int main(int argc, char *argv[]) {
    std::shared_ptr<Teacher> teacher = std::make_shared<Teacher>();
    teacher->print();

    std::shared_ptr<Person> per = std::make_shared<Teacher>();
    per->print(); // 形成多态

    return 0;
}
#include "main.h"

void Person::setName(std::string name) { this->name = name; }
void Person::test(std::string t, const std::shared_ptr<Teacher> &th) {
    th->name = "fwefw";
}
std::string Person::getName() { return this->name; }

int main(int argc, char *argv[]) {
    std::shared_ptr<Teacher> t = std::make_shared<Teacher>();
    t->setName("teacher");
    Person::test("good", t);
    std::cout << t->getName() << std::endl;

    return 0;
}
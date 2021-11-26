#include <iostream>
#include "person.h"

int main(int argc, char *argv[]) {
    std::cout << "test protected" << std::endl;
    Teacher teacher("zhangsan", 20);
    Teacher::print(teacher);

    return 0;
}
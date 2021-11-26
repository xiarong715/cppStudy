#ifndef __MAIN_H___
#define __MAIN_H___

#include <iostream>
#include <memory>
#include <string>

class Person {
   private:
    std::string name;
    int age;

   public:
    virtual void print() { std::cout << "I'm a person." << std::endl; }
};

class Teacher : public Person {
   public:
    void print() { std::cout << "I'm a teacher." << std::endl; }
};

#endif
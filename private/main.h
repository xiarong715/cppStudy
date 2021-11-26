#ifndef ___MAIN_H___
#define ___MAIN_H___

#include <string>
#include <memory>
#include <iostream>

class Teacher;
class Person {
   private:
    std::string name;
   public:
    void setName(std::string name);
    static void test(std::string t, const std::shared_ptr<Teacher> &th);
    std::string getName();
};

class Teacher : public Person {

};

#endif
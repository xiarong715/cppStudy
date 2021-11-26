class Person {
   protected:
    std::string name;
    unsigned char age;

   public:
    Person() {}
    Person(const std::string &name, const unsigned char age) {
        this->name = name;
        this->age = age;
    }
    void setName(const std::string &name) {
        this->name = name;
    }
    std::string getName() {
        return name;
    }
    void setAge(const unsigned char age) {
        this->age = age;
    }
    unsigned char getAge() {
        return age;
    }
};

class Teacher : public Person {
   public:
    Teacher() {}
    Teacher(const std::string &name, const unsigned char age) : Person(name, age) {}
    void testSetName(const std::string &name) {
        this->name = name;      // 派生类中访问基类中的protected成员；
    }
    static void print(Teacher &t) {
        std::cout << t.name << std::endl;   // 在派生类中访问基类的protected成员；
    }
}; // 只有在派生类中才可以通过派生类对象访问基类的protected成员；
#include <iostream>
#include "RefBase.h"

class lightClass : public lightBase<lightClass> {
   private:
    int m_nTest;

   public:
    lightClass() : m_nTest(0) {}
    int getValue() { return m_nTest; }
    void setValue(int value) { m_nTest = value; }
    ~lightClass() {}
};

int main(int argc, char *argv[]) {
    lightClass *obj = new lightClass();
    sp<lightClass> spObj = obj;  // call copy constructor, add reference
    // sp<lightClass> sp1 = obj;
    sp<lightClass> sp1;  // call default constructor
    sp1 = obj;           // call assignment operator, add reference
    spObj->setValue(34);
    sp1->setValue(36);
    std::cout << spObj->getValue() << std::endl;
    std::cout << sp1->getValue() << std::endl;

    std::cout << "sp1->getCount() = " << sp1->getCount() << std::endl;
    sp1 = nullptr;

    return 0;
}
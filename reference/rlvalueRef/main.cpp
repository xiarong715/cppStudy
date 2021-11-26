#include <iostream>

int foo() {
    return 1;
}

int main(int argc, char *argv[]) {
    std::cout << "loactor value reference and read value reference" << std::endl;

    // 左值：有名称，可读其值，可取其地址；(lvalue)
    int n = 2;
    int j = n; // 取值， n is lvalue
    int *p = &n; // 取地址, n is lvalue
    
    // 左值引用：一个左值引用类型与一个左值关联；
    int a = 2;          
    int &b = a;         // ok, a is lvalue
    
    //int &c = 10;      // error, 10 is not lvalue
    const int &c = 10;  // ok, 强制对右值左引用？？？; 10没地址，不能对其修改，刚好可用const修饰

    // 右值：只能读其值，不可取其址地；(value)
    // 右值引用：对一个右值进行引用
    // note: 在使用右值引用时，和声明左值引用一样，右值引用也必须被初始化，且右值引用只能使用右值初始化
    int &&d = 10;       // ok, 10 is rvalue, c is rvalue reference type; 
    d = 100;            // modify d
    int e = 2;
    //int &&f = e;      // error, e is not rvalue
    int &&f = foo();    // ok, foo() is rvalue

    return 0;
}

int foo();
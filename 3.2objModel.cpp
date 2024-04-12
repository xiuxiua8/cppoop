/*3.2 实验： 研究C++的对象模型
1、定义一个类，其中有静态数据成员、各种类型非静态数据成员（含字符指针），甚至包括引用（可选），静态和非静态成员函数（含分配空间的构造函数、析构函数）。
2、定义全局对象、main函数中局部对象、另一个被main调用的外部函数func中定义局部对象（可以是形参）、main函数中动态创建对象，每种对象至少2个。观察、分析各种对象地址。
3、输出对象中各个静态与非静态数据成员的值、地址、对象的存储空间大小等信息。由此理解对象的本质、静态数据成员是本类对象共享一份拷贝等问题。此外，应观察对齐现象。
4、（可选）输出对象的每个字节，以揭示引用的实现方法。
5、对于上述各种对象，输出静态、非静态成员函数地址，以及main、func等外部函数的地址，并分析。要求采用合理方法，避免编译器提出警告。  */
#include <iostream>
#include <cstring>

class MyClass {
public:
    static int staticDataMember;
    int nonStaticDataMember;
    char* charPointer;
    int& referenceMember;

    MyClass(int value) : referenceMember(nonStaticDataMember) {
        nonStaticDataMember = value;
        charPointer = new char[10];
        strcpy(charPointer, "123456789");
        staticDataMember++;
    }

    ~MyClass() {
        delete[] charPointer;
    }

    static void staticMemberFunction() {
        std::cout << "Static member function called" << std::endl;
    }

    void nonStaticMemberFunction() {
        std::cout << "Non-static member function called" << std::endl;
    }
};

typedef void (MyClass::*Func)();

int MyClass::staticDataMember = 0;
MyClass globalObject1(1);
MyClass globalObject2(1);

// Output values and addresses of members
void addrMember(MyClass &obj,std::string name) {
    std::cout << "________________________________________________________" << std::endl;
    std::cout << "Name of Object:                 " << name << std::endl;
    std::cout << "staticDataMember: " << std::endl;
    std::cout << "    Value: " << MyClass::staticDataMember << std::endl;
    std::cout << "    Address: " << &MyClass::staticDataMember << std::endl;
    std::cout << "nonStaticDataMember: "<< std::endl;
    std::cout << "    Value: " << obj.nonStaticDataMember << std::endl;
    std::cout << "    Address: " << &obj.nonStaticDataMember << std::endl;
    std::cout << "charPointer: " << std::endl;
    std::cout << "    Value: " << obj.charPointer << std::endl;
    std::cout << "    Address: " << (void*)&obj.charPointer << std::endl;
    std::cout << "referenceMember: " << std::endl;
    std::cout << "    Value: " << obj.referenceMember<< std::endl;
    std::cout << "    Address: " << (void*)&obj.referenceMember<< std::endl;
    std::cout << "Size of " << name << " " << sizeof(obj) << std::endl;
}

union {
    Func f;	        //f是Func类型的函数指针
    void *addr;  //f也可看成void*，其值为函数地址
} noStatic;


void func() {
    std::cout << "Inside func()" << std::endl;
    MyClass localFuncObject1(1);
    MyClass localFuncObject2(2);
    addrMember(localFuncObject1,"localFuncObject1");
    addrMember(localFuncObject2,"localFuncObject2");
    std::cout << "Address of localFuncObject1: " << &localFuncObject1 << std::endl;
    std::cout << "Address of localFuncObject2: " << &localFuncObject2 << std::endl;
}


int main() {
    MyClass localMainObject1(1);
    MyClass localMainObject2(2);
    MyClass* dynamicObject1 = new MyClass(3);
    MyClass* dynamicObject2 = new MyClass(3);

    // Output addresses of objects
    std::cout << "Address of globalObject1: " << &globalObject1 << std::endl;
    std::cout << "Address of globalObject2: " << &globalObject2 << std::endl;
    std::cout << "Address of localMainObject1: " << &localMainObject1 << std::endl;
    std::cout << "Address of localMainObject2: " << &localMainObject2 << std::endl;
    std::cout << "Address of dynamicObject1: " << dynamicObject1 << std::endl;
    std::cout << "Address of dynamicObject2: " << dynamicObject2 << std::endl;

    // Output values and addresses of members
    addrMember(globalObject1,"globalObject1");
    addrMember(globalObject2,"globalObject2");
    addrMember(localMainObject1,"localMainObject1");
    addrMember(localMainObject2,"localMainObject2");
    addrMember(*dynamicObject1,"dynamicObject1");
    addrMember(*dynamicObject2,"dynamicObject2");
    func();


    // Call member functions
    MyClass::staticMemberFunction();
    std::cout << "Address of staticMemberFunction: " << (void*)&MyClass::staticMemberFunction << std::endl;

    noStatic.f = &MyClass::nonStaticMemberFunction;
    std::cout  << "Address of nonStaticMemberFunction: " << &std::hex << std::noshowbase<<noStatic.addr << std::endl;

    // Output addresses of member functions

    // Output addresses of external functions
    std::cout << "Address of main: " << (void*)&main << std::endl;
    std::cout << "Address of func: " << (void*)&func << std::endl;

    delete dynamicObject1;
    delete dynamicObject2;

    return 0;
}

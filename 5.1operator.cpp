/*
 *1、定义String类，用于存放字符串并实现有关操作，其中有：
数据成员array，类型为char* 。
构造函数String(const char* p)、析构函数~String()。
根据以下main函数及运行结果，实现必要的运算符重载，使得输出符合指定结果。
其中string1[index]表示取字符串中某个字符，因此index的取值范围为0到字符串不算结束符的长度减一，
否则显示“Index out of range.”。而string3+3表示将字符串不算结束符的长度与3相加，且要求不能通过重载+运算符实现。
2、主函数定义如下（不能修改）：
3、无输入，输出信息为：
mystring
mystrinn
Index out of range.
mystrinnyourstringherstring
mystrinnyourstringherstring
yourstringab
yourstring
12
herstring
 * */
#include <iostream>
#include <cstring>

using namespace std;

class String {
    private:
        char * array;
    public:
        String(const char* p) {
            array = new char[strlen(p) + 1];
            strcpy(array, p);
        }

        ~String() {
            delete[] array;
        }

        String(const String& other) {
            array = new char[strlen(other.array) + 1];
            strcpy(array, other.array);
        }

        String& operator=(const String& other) {
            if (this == &other) {
                return *this;
            }
            delete[] array;
            array = new char[strlen(other.array) + 1];
            strcpy(array, other.array);
            return *this;
        }

        friend ostream& operator<<(ostream& os, const String& str) {  //实参常量，形参可变，内存上不可变，不允许
            os << str.array;
            return os;
        }

        char& operator [](int index) const { //字符变量，&，
            if (index < strlen(array) && index >= 0) {
                return array[index];
            }
            throw "Index out of range.\n"; //返回无关紧要的变量，new global static ...
                                           //使用异常处理机制，越界时不必返回
        }


        String& operator+(String& other) { //string1.+(string2)
                                         //若不写copy constructor, remove & lead to 浅拷贝，导致string1 被误删，第二次delete出现异常
                                         //可去掉参数中的const，虽然不改other，但可写可不写
                                         //other 在使用中是
             /*
            char* new_array = new char[strlen(array) + 1];
            strcpy(array, new_array);
            if (array) delete[] array;
            char* array = new char[strlen(other.array) + strlen(new_array) + 1];
            strcpy(array, new_array);
            delete[] new_array;
            strcat(array, other.array);
            */
            char* new_array = new char[strlen(other.array) + strlen(array) + 1];
            strcpy(new_array, array);
            strcat(new_array, other.array);
            if (array) delete[] array;
            array = new_array;
            return *this;
        }

        String operator+(const char* other) const { //参数 常量字符串必写 第一个const
            char* new_array = new char[strlen(other) + strlen(array) + 1];
            strcpy(new_array, array);
            strcat(new_array, other);
            String result(new_array); //创建临时对象
            delete[] new_array; //p local 释放随函数，new的空间没有释放 内存泄漏
            return result; //copy constructor
        }

        /*
        //2 修改返回类型
        char* operator+(const char* other) const { //参数 常量字符串必写 第一个const
            char* new_array = new char[strlen(other) + strlen(array) + 1];
            strcpy(new_array, array);
            strcat(new_array, other);
            //delete[] new_array; //p local 释放随函数，new的空间没有释放 内存泄漏
            return new_array; //copy constructor
        }

        //3 类型转换 隐含转换
        //functions that differ only in their return type cannot be overloaded (char * and const String& other) with (char * and const String& other)
        //const string & other 常量对象用const修饰，是类型转换得来的，不能做左值
        //(char * and const String& other) with (string* and String& other)
        char* operator+(const String& other) { //string1.+(string2)
                                                 //remove 第二 & lead to 浅拷贝，导致string1 被误删，第二次delete出现异常
            char* new_array = new char[strlen(array) + 1];
            strcpy(new_array, array);
            strcpy(new_array, other.array);
            //if (array) delete[] array;
            return new_array;
        }
        */



        //不能重载——————》类型转换
        //string3 to int
        //对
        //3 to String
        //错
        /*
        int addLength(int num) const {
            return strlen(array) + num;
        }

        int operator+(int num) const {
            return addLength(num);
        }


        String(int i) {
            ...
        }
        */
        operator int() { //类型转换函数int
            return strlen(array);
        }
};

int main (){
	String string1("mystring"),string2("yourstring"),string3("herstring");
	cout<<string1<<endl;
    try {
        string1[7]='n';
        cout<<string1<<endl;
        string1[8]='n';
    }
    catch (const char *ptr) {cout << ptr <<endl;}
	cout<<string1+string2+string3<<endl;
	cout<<string1<<endl;
	cout<<string2+"ab"<<endl;
	cout<<string2<<endl;
	cout<<string3+3<<endl;
	cout<<string3<<endl;
	return 0;
}

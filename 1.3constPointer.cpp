/* 1、定义常量字符串"abc"，并用指针p指向它，然后输出该常量字符串。
 * 2、动态创建一个字符数组，并用常变量字符指针q指向它。
 * 要求在创建该数组的同时将数组初始化为字符串"def"，
 * 即不允许创建后再用赋值语句对其初始化。
 * 还要求该数组长度能恰好再额外存放一个字符。
 * 然后输出该字符串，以及数组长度。
 * 3、把p指向字符串复制到该数组中，再键盘输入一个字符，
 * 追加到字符串尾部，最后输出该字符串。
 * 实例：
 * 输入 z
 * 输出 
 * abc
 * def 5
 * abcz  */
#include <iostream>
#include <string>

int main(){
    const char* p = "abc";
    std::cout << p << std::endl;
    char* q = new char[4]{'d', 'e', 'f', '\0'};
    std::cout << q << " "<< std::string(q).length() << std::endl;
    for (int i = 0; i < 3; i++) {
        q[i] = p[i];
    }
    std::cin >> q[4];
    std::cout << q << " "<< std::string(q).length() << std::endl;

    return 0;
}

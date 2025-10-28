#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
//#define OVERFLOW -2

typedef int Status;

#define MAX_SIZE 255
typedef struct {
    char ch[MAX_SIZE];
    int length;
}SString;

Status StrAssign(SString &T, char *chars);
Status StrCopy(SString &T, SString S);
Status StrEmpty(SString S);
Status StrCompare(SString S, SString T);
int StrLength(SString S);
Status SubString(SString &Sub, SString S, int pos, int len);
Status Concat(SString &T, SString S1, SString S2);
int Index(SString S, SString T);
Status ClearString(SString &S);
Status DestroyString(SString &S);

Status StrAssign(SString &T, char *chars) {
    if (strlen(chars) > MAX_SIZE)
        return ERROR;
    T.length = strlen(chars);
    for (int i = 1; i <= T.length; i++) {
        T.ch[i] = chars[i - 1];
    }
    return OK;
}

Status StrCopy(SString &T, SString S) {
    for (int i = 1; i <= S.length; i++) {
        T.ch[i] = S.ch[i];
    }
    T.length = S.length;
    return OK;
}

int StrLength(SString S) {
    return S.length;
}

Status SubString(SString &Sub, SString S, int pos, int len) {
    if (pos < 1 || pos > S.length || len < 0 || len > S.length - pos + 1) {
        return ERROR;
    }
    for (int i = 1; i <= len; i++)
        Sub.ch[i] = S.ch[pos + i - 1];
    Sub.length = len;

    return OK;
}

Status Compare(SString S, SString T) {
    for (int i = 1; i <= S.length && i <= T.length; i++) {
        if (S.ch[i] != T.ch[i])
            return S.ch[i] - T.ch[i];
    }
    return S.length - T.length;
}

int Index(SString S, SString T) {
    int i = 1; 
    int n = StrLength(S); 
    int m = StrLength(T);
    SString sub;
    while (i <= n - m + 1) {
        SubString(sub, S, i, m);
        if (Compare(sub, T) != 0)
            i++;
        else
            return i;
    }
    return 0;
}

int Index2(SString S, SString T) {
    int i = 1, j = 1;
    while (i <= S.length && j <= T.length) {
        if (S.ch[i] == T.ch[j]) {
            i++;
            j++;
        } else {
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > T.length)
        return i - T.length;
    else
        return 0;
}

int main() {
    SString s1, s2, sub;
    char str1[] = "Hello, World!";
    char str2[] = "World";

    // 测试字符串赋值
    if (StrAssign(s1, str1) == OK) {
        std::cout << "s1: " << s1.ch << ", length: " << s1.length << std::endl;
    } else {
        std::cout << "Failed to assign string to s1." << std::endl;
    }

    // 测试字符串复制
    if (StrCopy(s2, s1) == OK) {
        std::cout << "s2: " << s2.ch << ", length: " << s2.length << std::endl;
    } else {
        std::cout << "Failed to copy string from s1 to s2." << std::endl;
    }

    // 测试字符串比较
    int cmpResult = Compare(s1, s2);
    std::cout << "Compare s1 and s2: " << cmpResult << std::endl;

    // 测试子串提取
    if (SubString(sub, s1, 8, 5) == OK) {
        std::cout << "SubString: " << sub.ch << ", length: " << sub.length << std::endl;
    } else {
        std::cout << "Failed to extract substring from s1." << std::endl;
    }

    // 测试字符串索引
    int index = Index(s1, s2);
    std::cout << "Index of s2 in s1: " << index << std::endl;

    return 0;
}
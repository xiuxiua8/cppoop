
#include <iostream>
using namespace std;

typedef int ElemType;

#define MaxSize 50
typedef struct 
{
    ElemType data[MaxSize];
    int top;
}SqStack;

void InitStack(SqStack &S);
bool StackEmpty(SqStack S);
bool Push(SqStack &S, ElemType x);
bool Pop(SqStack &S, ElemType &x);
bool GetTop(SqStack S, ElemType &x);
void DestroyStack(SqStack &S);

void InitStack(SqStack &S)
{
    S.top = -1;
}

bool StackEmpty(SqStack S) {
    return S.top == -1;
}

bool Push(SqStack &S, ElemType x) {
    if (S.top == MaxSize - 1)
        return false;
    S.data[++S.top] = x;
    return true;
}

bool Pop(SqStack &S, ElemType &x) {
    if (S.top == -1)
        return false;
    x = S.data[S.top--];
    return true;
}

bool GetTop(SqStack S, ElemType &x) {
    if (S.top == -1)
        return false;
    x = S.data[S.top];
    return true;
}

void DestroyStack(SqStack &S) {
    S.top = -1;// duima
}

typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
}LiStack;
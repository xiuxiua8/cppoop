#include <iostream>
using namespace std;

typedef int ElemType;

#define MaxSize 50
typedef struct {
    ElemType data[MaxSize];
    int length;
}SqList;

void InitList(SqList &L) {
    L.length = 0;
}

bool ListInsert(SqList &L, int i, ElemType e) {
    if (i < 1 || i > L.length + 1) 
        return false;
    if (L.length >= MaxSize)
        return false;
    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j-1];
    L.data[i-1] = e;
    L.length++;
    return true;    
}

bool ListDelete(SqList &L, int i, ElemType &e) {
    if (i < 1 || i > L.length)
        return false;
    e = L.data[i-1];
    for (int j = i; j < L.length; j++)
        L.data[j-1] = L.data[j];
    L.length--;
    return true;
}

int LocateElem(SqList L, ElemType e) {
    for (int i = 0; i < L.length; i++)
        if (L.data[i] == e) 
            return i+1; //返回位序
    return 0; //返回0表示未找到
}
    
void printList(SqList L) {
    for (int i = 0; i < L.length; i++)
        cout << L.data[i] << " ";
    cout << endl;
}

int main() {
    SqList L;
    // L.data = (ElemType*)malloc(sizeof(ElemType)*InitSize); //C语言
    // L.data = new ElemType[InitSize]; // C++语言
    InitList(L);
    ListInsert(L, 1, 1);
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    printList(L);
    cout << LocateElem(L, 2) << endl;
    return 0;
}
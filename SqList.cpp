#include <iostream>
using namespace std;

typedef int ElemType;

#define MaxSize 50
typedef struct {
    ElemType data[MaxSize];
    int length;
}SqList;

void InitList(SqList &L);
bool ListInsert(SqList &L, int i, ElemType e);
bool ListDelete(SqList &L, int i, ElemType &e);
int LocateElem(SqList L, ElemType e);
void printList(SqList L);
bool DeleteMin(SqList &L, ElemType &e);

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

bool DeleteMin(SqList &L, ElemType &e) {
    if (L.length == 0)
        return false;
    int min = 0;
    for (int i = 1; i < L.length; i++) {
        if (L.data[i] < L.data[min]) {
            min = i;
        }
    }
    e = L.data[min];
    L.data[min] = L.data[L.length-1];
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
    
    cout << "===== 顺序表测试 =====" << endl;
    
    // 测试空表
    cout << "1. 初始化空表：" << endl;
    cout << "   表长度: " << L.length << endl;
    
    // 测试插入操作
    cout << "\n2. 测试插入操作：" << endl;
    if(ListInsert(L, 1, 10))
        cout << "   成功插入10到位置1" << endl;
    if(ListInsert(L, 2, 20))
        cout << "   成功插入20到位置2" << endl;
    if(ListInsert(L, 3, 30))
        cout << "   成功插入30到位置3" << endl;
    if(ListInsert(L, 2, 15))
        cout << "   成功插入15到位置2" << endl;
    cout << "   插入后的顺序表：";
    printList(L);
    
    // 测试查找操作
    cout << "\n3. 测试查找操作：" << endl;
    cout << "   元素20的位置：" << LocateElem(L, 20) << endl;
    cout << "   元素100的位置：" << LocateElem(L, 100) << endl;
    
    // 测试删除操作
    cout << "\n4. 测试删除操作：" << endl;
    ElemType e;
    if(ListDelete(L, 2, e))
        cout << "   删除位置2的元素成功，删除的元素值为：" << e << endl;
    else
        cout << "   删除位置2的元素失败" << endl;
    cout << "   删除后的顺序表：";
    printList(L);
    
    // 测试DeleteMin函数
    cout << "\n5. 测试删除最小值：" << endl;
    // 插入一些额外的值以测试DeleteMin
    ListInsert(L, L.length + 1, 5); // 插入较小的值
    cout << "   插入新值后的顺序表：";
    printList(L);
    
    if(DeleteMin(L, e))
        cout << "   删除最小元素成功，最小元素值为：" << e << endl;
    else
        cout << "   删除最小元素失败" << endl;
    cout << "   删除最小值后的顺序表：";
    printList(L);
    
    // 测试边界情况
    cout << "\n6. 测试边界情况：" << endl;
    // 删除所有元素
    while(L.length > 0) {
        ListDelete(L, 1, e);
    }
    cout << "   删除所有元素后的顺序表：";
    printList(L);
    
    // 尝试从空表中删除最小值
    if(DeleteMin(L, e))
        cout << "   从空表删除最小元素成功，最小元素值为：" << e << endl;
    else
        cout << "   从空表删除最小元素失败（预期结果）" << endl;
    
    return 0;
}
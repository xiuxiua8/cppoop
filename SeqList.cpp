#define InitSize 50
#define MaxSize 50
typedef int ElemType;
typedef struct {
    ElemType data[MaxSize];
    int length;
}SeqList;

void InitList(SeqList &L) {
    L.length = 0;
}

SeqList L;
//L.data = (ElemType*)malloc(sizeof(ElemType)*InitSize); //C语言
L.data = new ElemType[InitSize]; //C++语言


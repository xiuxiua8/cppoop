#include <iostream>
#include <stdlib.h>

using namespace std;


typedef int ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

bool InitList(LinkList &L);
LNode *GetElem(LinkList L, int i);
LNode *LocateElem(LinkList L, ElemType e);
bool ListInsert(LinkList &L, int i, ElemType e);
bool ListDelete(LinkList &L, int i, ElemType &e);
void PrintList(LinkList L);
int Length(LinkList L);


bool InitList(LinkList &L) {
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    return true;
}

LNode *GetElem(LinkList L, int i) {
    LNode *p = L;
    int j = 0;
    while (p->next!=NULL && j<i) {
        p = p->next;
        j++;
    }
    return p;
}

LNode *LocateElem(LinkList L, ElemType e) {
    LNode *p = L->next;
    while (p!=NULL && p->data!=e) {
        p = p->next;
    }
    return p;
}

bool ListInsert(LinkList &L, int i, ElemType e) {

    LNode *p = L;
    int j = 0;
    while (p->next!=NULL && j < i-1) {
        p = p->next;
        j++;
    }
    if (p==NULL)
        return false;
    // LNode *p = GetElem(L, i-1);

    LNode *s = (LNode*)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

bool ListDelete(LinkList &L, int i, ElemType &e) {
    LNode *p = L;
    int j = 0;
    while (p->next!=NULL && j<i-1) {
        p = p->next;
        j++;
    }
    if(p==NULL || j>i-1)
        return false;
    LNode *q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return true;
}

void PrintList(LinkList L) {
    LNode *p = L->next;
    while (p!=NULL) {
        cout << p->data << " ";
        p = p->next;    
    }
    cout << endl;
}   

int Length(LinkList L) {
    int len = 0;
    LNode *p = L;
    while (p->next != NULL) {
        p = p->next;
        len++;
    }
    return len;
}
int main() {
    LinkList L;
    ElemType e;
    InitList(L);
    cout << "Length(L) = " << Length(L) << endl;
    ListInsert(L, 1, 1);
    ListInsert(L, 2, 2);
    ListInsert(L, 3, 3);
    cout << "Length(L) = " << Length(L) << endl;
    ListDelete(L, 2, e);
    cout << "e = " << e << endl;
    cout << "Length(L) = " << Length(L) << endl;
    PrintList(L);   
    return 0;
} 
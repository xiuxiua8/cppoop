#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

#define MaxSize 50

typedef int ElemType;

typedef struct
{
    ElemType data[MaxSize];
    int size;
} PriorityQueue;

bool isEmpty(PriorityQueue &Q);

/*
bool EnQueue(SqQueue &Q, ElemType x);
bool DeQueue(SqQueue &Q, ElemType &x);
bool GetHead(SqQueue Q, ElemType &x);
void DestroyQueue(SqQueue &Q);
*/

void InitQueue(PriorityQueue &Q);
void add(PriorityQueue &Q);
ElemType getSmallest(PriorityQueue &Q);
ElemType removeSmallest(PriorityQueue &Q);
int size(PriorityQueue &Q);

void initQueue(PriorityQueue &Q)
{
    Q.size = 0;
}

bool isEmpty(PriorityQueue &Q)
{
    return Q.size == 0;
}

/** place the new employee in the last position, and promote as high as possible.
 */
void add(PriorityQueue &Q, int item)
{
    Q.data[Q.size + 1] = item;
    Q.size++;
}

/** leave spot 0 empty */
int parent(int k)
{
    return k / 2;
}
int leftChild(int k)
{
    return 2 * k;
}
int rightChild(int k)
{
    return 2 * k + 1;
}

void swap(PriorityQueue &Q, int a, int b)
{
    if (a > Q.size || b > Q.size)
        return;
    int temp = Q.data[a];
    Q.data[a] = Q.data[b];
    Q.data[b] = temp;
}

void swim(PriorityQueue &Q, int k)
{
    if (Q.data[parent(k) > Q.data[k]])
        swap(Q, k, parent(k));
    swim(Q, parent(k));
}

/** return the item in the root node */
ElemType getSmallest(PriorityQueue &Q)
{
    return Q.data[1];
}

/** assassinate the president, promote the rightmost person in the company to president, then demote repeatedly, always taking the better successor */
ElemType removeSmallest(PriorityQueue &Q)
{
    int smallest = Q.data[1];
    swap(Q, 1, Q.size);
    Q.size--;
    return smallest;
}

void printList(ElemType A[], int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main()
{
    PriorityQueue A;
    InitQueue(A);
}

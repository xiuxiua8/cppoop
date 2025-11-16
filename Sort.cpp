#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#define main PQ_demo_main
#include "PriorityQueue.cpp"
#undef main

using namespace std;

#define MaxSize 50

typedef int ElemType;


void swap(ElemType A[], int a, int b) {
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

void printList(ElemType A[], int len) {
    for (int i=0; i<len; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}


void SelectionSort(ElemType A[], int len) {
    cout << "Selection sort!!" << endl;
    for (int i=0; i<len-1; i++) {
        int min = i;
        for (int j=i + 1; j<len; j++) {
            if (A[j] < A[min])
                min = j;
        }
        if (min != i)
            swap(A, min, i);
    }
}

void HeapSort(ElemType A[], int len) {
    cout << "Heap sort!!" << endl;
    PriorityQueue Queue;
    InitQueue(Queue);
    for (int i=0; i<len; i++) {
        add(Queue, A[i]);
    }
    for (int i=0; i<len; i++) {
        int min = removeSmallest(Queue);
        A[i] = min;
    }
}

int main() {
    ElemType A[] = {9, 2, 8, 4, 5};
    int sizeofA = 5;
    cout << "unsorted array:" << endl;
    printList(A, sizeofA);
    //SelectionSort(A, sizeofA);
    HeapSort(A, sizeofA);
    cout << "sorted array:" << endl;
    printList(A, sizeofA);
    

}
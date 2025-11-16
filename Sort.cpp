#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
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

void sink(ElemType A[], int k, int len) {
    if ()
    
}

void BottomUpHeapify(ElemType A[], int len) {
    for (int i=len-1; i > 0; i--) {
        
    }
}

void BuildMaxHeap(ElemType A[], int len) {
}

void HeadAdjust(ElemType A[], int k, int len) {

}

int main() {
    ElemType A[] = {9, 2, 8, 4, 5};
    int sizeofA = 5;
    printList(A, sizeofA);
    SelectionSort(A, sizeofA);
    printList(A, sizeofA);

}
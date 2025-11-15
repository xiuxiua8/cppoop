#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#define MaxSize 50

using namespace std;

typedef int ElemType;


void swap(ElemType A[], int a, int b) {
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

void printList(ElemType A[], int n) {
    for (int i=0; i<n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}


void SelectionSort(ElemType A[], int n) {
    for (int i=0; i<n; i++) {
        int min = i;
        for (int j=i; j<n; j++) {
            if (A[j] < A[min])
                min = j;
        }
        swap(A, min, i);
    }
}


int main() {
    ElemType A[] = {9, 2, 8, 4, 5};
    int sizeofA = 5;
    printList(A, sizeofA);
    SelectionSort(A, sizeofA);
    printList(A, sizeofA);

}
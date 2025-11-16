#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#define main PQ_demo_main
#include "PriorityQueue.cpp"
#undef main
#define main search_demo_main
#include "Search.cpp"
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


void InsertionSort(ElemType A[], int len) {
    cout << "Insertion sort!!" << endl;
    int i, j, k;
    for (int i=1; i<len; i++) {
        k=A[i];
        j=i-1;
        while((j>=0) && (A[j]>k)) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = k;
        //printList(A, len);
    }
}


void BinaryInsertionSort(ElemType A[], int len) {
    cout << "BinaryInsertion sort!!" << endl;
    int i, j, k;
    for (int i=1; i<len; i++) {
        k=A[i];
        j=i-1;
        int min = - BinarySearch(A, i, A[i]);
        while(j>min) {
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = k;
        printList(A, len);
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


ElemType *B= (ElemType *)malloc((MaxSize+1)*sizeof (ElemType));

void Merge(ElemType A[], int l, int m, int h) {
    int i, j, k;
    for (k = l; k <=h; k++)
        B[k] = A[k];
    for (i=l, j=m+1, k=i; i<=m&&j<=h; k++) {
        if (B[i]<=B[j]) 
            A[k] = B[i++];
        else 
            A[k] = B[j++];
    }
    while (i<=m) A[k++] = B[i++];
    while (j<=h) A[k++] = B[j++];
    //printList(A, 5);
}

void MergeSort(ElemType A[], int l, int h) {
    if (l < h){
        int m = (h + l)/2;
        MergeSort(A, l, m);
        MergeSort(A, m + 1, h);
        Merge(A, l, m, h);
    }
}


int Partition(ElemType A[], int l, int h) {
    // Hoare-style: pivot at l, scan inward and fill the “hole” left by pivot
    int pivot = l;
    ElemType key = A[pivot];
    while (l < h) {
        while (l < h && A[h] >= key)
            h--;
        if (l < h)
            A[l] = A[h];
        while (l < h && A[l] <= key)
            l++;
        if (l < h)
            A[h] = A[l];
    }
    A[l] = key;
    printList(A, 25);
    return l;
}



void QuickSort(ElemType A[], int l, int h) {
    if (l >= h) return;
    int pivot = Partition(A, l, h);
    QuickSort(A, l, pivot-1);
    QuickSort(A, pivot+1, h);
}


int main() {
    /*
    ElemType A[] = {9, 2, 8, 5, 4};
    int sizeofA = 5;
    */
    ElemType A[] = {42, 17, 89, 3, 56, 23, 91, 8, 34, 67, 12, 45, 78, 29, 61, 5, 38, 84, 19, 72, 15, 53, 96, 27, 64};
    int sizeofA = 25;
    cout << "unsorted array:" << endl;
    printList(A, sizeofA);
    //SelectionSort(A, sizeofA);
    //InsertionSort(A, sizeofA);
    //BinaryInsertionSort(A, sizeofA);
    //HeapSort(A, sizeofA);
    //MergeSort(A, 0, sizeofA - 1);
    QuickSort(A, 0, sizeofA - 1);
    cout << "sorted array:" << endl;
    printList(A, sizeofA);
}

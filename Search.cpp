#include <iostream>
#include <stdlib.h>

using namespace std;

typedef int ElemType;

typedef struct {
    ElemType *elem;
    int TableLen;
} SSTable;

/**
 * Searches for the specified key in the specified array using sequential search with sentinel.
 *
 * @param  ST the array of integers to search in
 * @param  key the search key
 * @return index of key in array {@code ST} if present; {@code 0} otherwise (sentinel position)
 */
int Search_seq(SSTable ST, ElemType key)
{
    ST.elem[0] = key;
    int i;
    for (i = ST.TableLen; ST.elem[i] != key; --i);
    return i;
}

/**
 * Searches for the specified key in the specified array using sequential search with early termination.
 * If the array is sorted in ascending order, the search terminates early when encountering an element greater than the key.
 *
 * @param  ST the array of integers to search in
 * @param  key the search key
 * @return index of key in array {@code ST} if present; {@code -1} otherwise
 */
int Search_seq2(SSTable ST, ElemType key) {
    int pos = 0;
    bool found = false;

    while (pos <= ST.TableLen && !found) {
        if (ST.elem[pos] == key) {
            found = true;
        } else if (ST.elem[pos] < key && ST.elem[pos+1] > key) {
            cout << "quit!" << endl;
            return -1;
        } else 
            pos++;
    }
    return (pos <= ST.TableLen) ? pos : -1;
}

/**
 * Binary search on a 0-based sorted array.
 *
 * @param  A   sorted array of integers (0-based indexing)
 * @param  len number of valid elements in {@code A}
 * @param  key search target
 * @return index of {@code key} if found; otherwise {@code -hi}, where {@code -returnValue}
 *         marks the insertion position that keeps the array sorted
 */
int BinarySearch(ElemType *A, int len, ElemType key) {
    int lo = 0;
    int hi = len - 1;

    /* 哨兵
    int lo = 1;
    int hi = len;
    */
    int mid;
    while (lo <= hi) {
        // Key is in a[lo..hi] or not present.
        mid = lo + (hi - lo) / 2;
        //cout << lo << ' ' << mid << ' '<< hi << endl;
        if (key < A[mid]) hi = mid -1;
        else if (key > A[mid]) lo = mid + 1;
        else return mid;
        
    }
    return -hi;
}


int main() {
    
    SSTable ST;
    ST.TableLen = 10;
    ST.elem = (ElemType*)malloc(sizeof(ElemType) * (ST.TableLen + 1));
    ST.elem[0] = 0;
    for (int i = 1; i <= ST.TableLen; i++) {
        ST.elem[i] = 2*i;
        cout << ST.elem[i] << " " ;
    }
    cout << endl;
    
    /*test 1*/
    int ans2 = Search_seq2(ST, 3);
    int ans3 = BinarySearch(ST.elem, ST.TableLen, 2);
    int ans1 = Search_seq(ST, 3);
    cout << "ans1: " << ans1 << endl;
    cout << "ans2: " << ans2 << endl;
    cout << "ans3: " << ans3 << endl;

    /*test 2*/
    int ans2 = Search_seq2(ST, 3);
    cout << "------" << endl;
    for (int i = 1; i < 10; i++) {
        cout << "searching for: " << 2 * i - 1 << endl;
        ans3 = BinarySearch(ST.elem, ST.TableLen, 2*i -1);
        cout << "ans3: " << ans3 << endl;
    }

    free(ST.elem);
    return 0;
}

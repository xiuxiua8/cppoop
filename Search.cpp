#include <iostream>
#include <stdlib.h>

using namespace std;

typedef int ElemType;

typedef struct {
    ElemType *elem;
    int TableLen;
} SSTable;

int Search_seq(SSTable ST, ElemType key)
{
    ST.elem[0] = key;
    int i;
    for (i = ST.TableLen; ST.elem[i] != key; --i);
    return i;
}

int Search_seq2(SSTable ST, ElemType key) {
    int pos = 0;
    bool found = false;

    while (pos <= ST.TableLen && !found) {
        if (ST.elem[pos] == key)
            found = true;
        else 
            pos++;
    }
    return (pos <= ST.TableLen) ? pos : -1;
}

/**
 * Returns the index of the specified key in the specified array.
 *
 * @param  ST the array of integers, must be sorted in ascending order
 * @param  key the search key
 * @return index of key in array {@code ST} if present; {@code -1} otherwise
 */
int BinarySearch(SSTable ST, ElemType key) {
    /* 无哨兵
    int lo = 0;
    int hi = ST.TableLen - 1;
    */

    int lo = 1;
    int hi = ST.TableLen;
    while (lo <= hi) {
        // Key is in a[lo..hi] or not present.
        int mid = lo + (hi - lo) / 2;
        //cout << lo << ' ' << mid << ' '<< hi << endl;
        if (key < ST.elem[mid]) hi = mid -1;
        else if (key > ST.elem[mid]) lo = mid + 1;
        else return mid;
    }
    return -1;
}


int main() {
    
    SSTable ST;
    ST.TableLen = 10;
    ST.elem = (ElemType*)malloc(sizeof(ElemType) * (ST.TableLen + 1));
    ST.elem[0] = 0;
    for (int i = 1; i <= ST.TableLen; i++)
        ST.elem[i] = i;
    int ans2 = Search_seq2(ST, 3);
    int ans3 = BinarySearch(ST, 3);
    int ans = Search_seq(ST, 3);
    cout << ans << endl;
    cout << ans2 << endl;
    cout << ans3 << endl;
    

    free(ST.elem);
    return 0;
}

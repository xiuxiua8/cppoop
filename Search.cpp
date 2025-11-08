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


int main() {
    
    SSTable ST;
    ST.TableLen = 10;
    ST.elem = (ElemType*)malloc(sizeof(ElemType) * (ST.TableLen + 1));
    for (int i = 1; i < ST.TableLen; i++)
        ST.elem[i] = i;
    int ans = Search_seq(ST, 3);
    //cout << ans << endl;
    cout << ans;
    
    return 0;
}
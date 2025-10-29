#include <iostream>
using namespace std;


#define SIZE 10
int UFSets[SIZE];

void Initial(int S[])
{
    for (int i = 0; i < SIZE; i++)
        S[i] = -1;
}

//return index of the root of a set i ,while S[i] equals to the negative of size
int Find1(int S[], int x)
{
    while (S[x] >= 0)
        x = S[x];
    return x;
}

//Better approach using Path Compression
int Find(int S[], int x)
{
    int root = x;
    while (S[root] >= 0)
        root = S[root];
    while (x != root) {
        int next = S[x];
        S[x] = root;
        x = next;
    }
    return root;
}

int Size(int S[], int x)
{
    while (S[x] >= 0)
        x = S[x];
    return -S[x];
}

void print(int S[]) {
    for (int i = 0; i < SIZE; i++)
        cout << S[i] << " ";
    cout << endl;
}

void Union(int S[], int Root1, int Root2)
{
    if (Root1 == Root2)
        return;
    if (Find(S, Root1) == Find(S, Root2))
        return;
    if (S[Root1]<0) {
        cout << Root1 << "->" << Root2 <<endl;
        S[Root1] = Find(S,Root2);
        S[Find(S,Root2)]--;
    } else {
        cout << Root2 << "->" << Root1 <<endl;
        S[Root2] = Find(S, Root1);
        S[Find(S,Root1)]--;
    }
    print(S);
}

void intuitiveUnion(int S[], int Root1, int Root2)
{
    if (Root1 == Root2)
        return;
    S[Root2] = Root1;
}

void BetterUnion(int S[], int Root1, int Root2)
{
    if (Root1 == Root2)
        return;
    if (Find(S, Root1) == Find(S, Root2))
        return;
    if (Size(S, Root2) > Size(S, Root1)) {
        cout << Find(S, Root1) << "->" << Find(S, Root2) <<endl;
        S[Find(S, Root2)] += S[Find(S, Root1)];
        S[Find(S, Root1)] = Find(S,Root2);
    } else {
        cout << Find(S, Root2) << "->" << Find(S, Root1) <<endl;
        S[Find(S, Root1)] += S[Find(S, Root2)];
        S[Find(S, Root2)] = Find(S, Root1);
    }
    print(S);
}





int main()
{
    int set[SIZE];
    Initial(set);
    /*
    Union(set, 2, 3);
    Union(set, 5, 3);
    Union(set, 3, 5);
    Union(set, 2, 4);
    Union(set, 6, 1);
    Union(set, 5, 1);
    */
    BetterUnion(set, 2, 3);
    BetterUnion(set, 5, 3);
    BetterUnion(set, 3, 5);
    BetterUnion(set, 2, 4);
    BetterUnion(set, 6, 1);
    BetterUnion(set, 5, 1);
    cout << "size of the set: " << Size(set, 1) << endl;
    cout << "find the set of 1: " << Find(set, 1) << endl;
    cout << "find the size of set of 3: " << Size(set, 3) << endl;
    
    cout << "the final array" << endl;
    print(set);
}
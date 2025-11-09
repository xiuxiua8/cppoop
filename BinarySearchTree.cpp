#include <iostream> 
#include <stdlib.h>

using namespace std;


typedef struct BSTNode {
    int key;
    int size;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;


int size(BSTree T) {
    if (T == nullptr)
        return 0;
    return T->size;
}

BSTNode* search(BSTree T, int key) {
    while (T != nullptr && key != T->key) {
        if (key < T->key) T= T->lchild;
        else T= T->rchild;
    }
    return T;
}

BSTNode* Research(BSTree T,int key) {
    if (T == nullptr)
        return nullptr;
    if (key == T->key)
        return T;
    else if (key > T->key)
        return Research(T->rchild, key);
    else 
        return Research(T->lchild, key);
}

// 创建一个新节点
BSTNode* createNode(int key) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = key;
    node->lchild = nullptr;
    node->rchild = nullptr;
    node->size = 1;
    return node;
}

BSTNode* deleteMin(BSTree T, bool freeRemoved);

BSTNode* insert(BSTree T,int key) {
    if (T == nullptr)
        return createNode(key);
    if (key == T->key)
        return T;
    else if (key > T->key)
        T->rchild = insert(T->rchild, key);
    else 
        T->lchild = insert(T->lchild, key);
    T->size = 1 + size(T->lchild)+ size(T->rchild); 
    return T;
}

int compareTo(int key1, int key2) { 
    if (key1 < key2)
        return -1;
    else if (key1 > key2)
        return 1;
    else 
        return 0;
}

BSTNode* min(BSTree T) {
    if (T == nullptr)
        return nullptr;
    if (T->lchild != nullptr)
        return min(T->lchild);
    else 
        return T;
}

BSTNode* deleteMin(BSTree T, bool freeRemoved) {
    if (T == nullptr) return nullptr;
    if (T->lchild == nullptr) {
        BSTNode* right = T->rchild;
        if (freeRemoved) free(T);  // free when caller wants to actually delete the node's memory
        return right;
    }
    T->lchild = deleteMin(T->lchild, freeRemoved);
    T->size = 1 + size(T->lchild) + size(T->rchild);
    return T;
}
/**
 * deleting a node by swapping it with its successor.
 * inspired by https://math.oxford.emory.edu/site/cs171/hibbardDeletion/
 */
BSTNode* Delete(BSTree T, int key) {
    if (T == nullptr) 
        return nullptr;
    
    int cmp = compareTo(key, T->key);

    if (cmp < 0)
        T->lchild= Delete(T->lchild, key);
    else if (cmp > 0)
        T->rchild= Delete(T->rchild, key);
    else {
        if (T->rchild == nullptr) {
            BSTNode* temp = T->lchild;
            free(T);
            return temp;
        }

        BSTNode* t = T;
        
        T = min(T->rchild);
        T->rchild = deleteMin(t->rchild, false);
        T->lchild = t->lchild;
        free(t);
    }
    T->size = 1 + size(T->lchild)+ size(T->rchild);
    return T;
}

// 释放整棵树的内存
void freeTree(BSTree T) {
    if (T == nullptr)
        return;
    freeTree(T->lchild);
    freeTree(T->rchild);
    free(T);
}




int main() {
    // 构建一个简单的二叉搜索树
    //       5
    //      / \
    //     3   7
    //    / \   \
    //   2   4   9
    /*
    BSTNode* root = createNode(5);
    root->lchild = createNode(3);
    root->rchild = createNode(7);
    root->lchild->lchild = createNode(2);
    root->lchild->rchild = createNode(4);
    root->rchild->rchild = createNode(9);
    */

    cout << "测试二叉搜索树搜索功能" << endl;
    cout << "====================" << endl;
    
    BSTree root = nullptr;
    cout << "size of the tree is " << size(root) << endl;
    root = insert(root, 5);   // 保存返回值
    root = insert(root, 3);
    root = insert(root, 7);
    cout << "size of the tree is " << size(root) << endl;
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 9);

    cout << "size of the tree is " << size(root) << endl;
    cout << "size of right part of the tree is " << size(root->rchild) << endl;

    // 测试迭代搜索
    int testKeys[] = {5, 3, 7, 2, 4, 9, 1, 10};
    int n = sizeof(testKeys) / sizeof(testKeys[0]);
    
    for (int i = 0; i < n; i++) {
        int key = testKeys[i];
        BSTNode* result1 = search(root, key);
        BSTNode* result2 = Research(root, key);
        
        if (result1 != nullptr && result2 != nullptr) {
            cout << "找到键值 " << key << " (迭代和递归都成功)" << endl;
        } else {
            cout << "未找到键值 " << key << endl;
        }
    }

    cout << "found min node " << min(root)->key << endl;
    cout << "found min node " << min(root->rchild->rchild)->key << endl;

    root = deleteMin(root, true);
    cout << "delete the min of the tree" << endl;
    
    cout << "size of the tree is " << size(root) << endl;
    root = Delete(root, 7);
    cout << "delete the node of 7" << endl;
    cout << "size of the tree is " << size(root) << endl;

    for (int i = 0; i < n; i++) {
        int key = testKeys[i];
        BSTNode* result1 = search(root, key);
        BSTNode* result2 = Research(root, key);
        
        if (result1 != nullptr && result2 != nullptr) {
            cout << "找到键值 " << key << " (迭代和递归都成功)" << endl;
        } else {
            cout << "未找到键值 " << key << endl;
        }
    }

    // 清理内存
    freeTree(root);

    
    return 0;
}

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    int ltag, rtag;

    Node(int val) : data(val), left(NULL), right(NULL), ltag(0), rtag(0) {}
};

void InOrderThread(Node* root, Node*& pre) {

    if (root == nullptr) return;

    InOrderThread(root->left, pre);

    if (root->left == nullptr) {
        root->ltag = 1;
        root->left = pre;
    }

    if (pre && pre->right == nullptr) {
        pre->rtag = 1;
        pre->right = root;
    }

    pre = root;
    
    InOrderThread(root->right, pre);

}

void CreateInOrderThread(Node* root) {
    Node* pre = nullptr;
    InOrderThread(root, pre);
}

void InOrderTraverse1(Node* root) {
    Node* curr = root;

    while (curr && curr->ltag == 0) {
        curr = curr->left;
    }

    while (curr) {
        cout << curr->data << endl;
        if (curr->rtag == 1) {
            curr = curr->right;
        } else {
            curr = curr->right;
            while (curr && curr->ltag == 0) {
                curr = curr->left;
            }
        }
    }
}

Node *Firstnode(Node *root) {
    while (root->ltag == 0) {
        root = root->left;
    }
    return root;
}

Node *Nextnode(Node *p) {
    if (p->rtag == 0) {
        return Firstnode(p->right);
    } else {
        return p->right;
    }
}

void InOrderTraverse(Node *root) {
    for (Node *p = Firstnode(root); p != nullptr; p = Nextnode(p)) {
        cout << p->data << " ";
        cout << endl;
    }
}




int main() {
    /*
           1
          / \
         2   3
        / \
       4   5
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    CreateInOrderThread(root);

    cout << "中序遍历线索二叉树结果：";
    cout << endl;
    InOrderTraverse1(root);
    cout << endl;

    return 0;
}

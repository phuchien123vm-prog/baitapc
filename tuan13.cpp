#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

// Tao nut moi
Node* createNode(int x) {
    Node* p = new Node;
    p->data = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

// Them vao BST
Node* insert(Node* root, int x) {
    if (root == NULL)
        return createNode(x);

    if (x < root->data)
        root->left = insert(root->left, x);
    else
        root->right = insert(root->right, x);

    return root;
}

// Duyet Inorder de sap xep
void inorder(Node* root) {
    if (root == NULL)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Tim kiem trong BST
bool search(Node* root, int x) {
    if (root == NULL)
        return false;

    if (root->data == x)
        return true;

    if (x < root->data)
        return search(root->left, x);

    return search(root->right, x);
}

int main() {

    vector<int> years = {
        2001, 2002, 2006, 2007, 2003,
        2004, 2005, 2001, 1999, 2004
    };

    Node* root = NULL;

    // B1 + B2: Dung cay va them nut
    for (int x : years)
        root = insert(root, x);

    cout << "Du lieu sau khi sap xep:\n";
    inorder(root);

    cout << "\n\n";

    // B3: Tim kiem
    int key = 2004;

    if (search(root, key))
        cout << "Tim thay sinh vien co nam sinh "
             << key;
    else
        cout << "Khong tim thay sinh vien co nam sinh "
             << key;

    return 0;
}
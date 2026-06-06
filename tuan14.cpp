#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

struct Node {
    int key;
    int height;
    Node *left, *right;

    Node(int x) {
        key = x;
        height = 1;
        left = right = nullptr;
    }
};

//==================================================
// CÁC HÀM AVL
//==================================================

int getHeight(Node* node) {
    return (node == nullptr) ? 0 : node->height;
}

int getBalance(Node* node) {
    return (node == nullptr) ? 0 :
           getHeight(node->left) - getHeight(node->right);
}

void updateHeight(Node* node) {
    if (node)
        node->height =
            1 + max(getHeight(node->left),
                    getHeight(node->right));
}

// Xoay phải (LL)
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// Xoay trái (RR)
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

//==================================================
// CHÈN AVL
//==================================================

Node* insert(Node* root, int key) {

    if (root == nullptr)
        return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; // không cho trùng

    updateHeight(root);

    int balance = getBalance(root);

    // LL
    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    // RR
    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    // LR
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // RL
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

//==================================================
// CÁC PHÉP DUYỆT
//==================================================

void preorder(Node* root) {
    if (!root) return;

    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {
    if (!root) return;

    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;

    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

void levelorder(Node* root) {

    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {

        Node* cur = q.front();
        q.pop();

        cout << cur->key << " ";

        if (cur->left)
            q.push(cur->left);

        if (cur->right)
            q.push(cur->right);
    }
}

//==================================================
// IN CÂY
//==================================================

void printTree(Node* root, const string &prefix = "", bool isLeft = true) {
    if (root == nullptr)
        return;

    if (root->right)
        printTree(root->right, prefix + (isLeft ? "│   " : "    "), false);

    if (prefix.empty())
        cout << root->key << "\n";
    else
        cout << prefix << (isLeft ? "└── " : "┌── ") << root->key << "\n";

    if (root->left)
        printTree(root->left, prefix + (isLeft ? "    " : "│   "), true);
}

//==================================================
// MAIN
//==================================================

int main() {

    vector<int> a = {
        32, 51, 27, 83, 96,
        11, 45, 75, 66
    };

    Node* root = nullptr;

    cout << "=== QUA TRINH CHEN AVL ===\n\n";

    for (int x : a) {

        cout << "Chen " << x << ":\n";

        root = insert(root, x);

        printTree(root);

        cout << "\n------------------------\n";
    }

    cout << "\n=== KET QUA CUOI CUNG ===\n\n";

    cout << "Preorder  : ";
    preorder(root);

    cout << "\n";

    cout << "Inorder   : ";
    inorder(root);

    cout << "\n";

    cout << "Postorder : ";
    postorder(root);

    cout << "\n";

    cout << "Levelorder: ";
    levelorder(root);

    cout << "\n";

    return 0;
}
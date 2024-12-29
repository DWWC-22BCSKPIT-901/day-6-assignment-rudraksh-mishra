#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int   data;
    Node* left;
    Node* right;

    Node(int data) {
        this->data = data;
        this->left = nullptr;
        this->right = nullptr;
    }
};

vector<int> res;

vector<int> Inorder_Traversal(Node* root) {
    if (root == nullptr) { return {}; }

    Inorder_Traversal(root->left);
    res.push_back(root->data);
    Inorder_Traversal(root->right);

    return res;
}

int main(int argc, char* argv[]) {
    Node Root(1);
    Root.left  = new Node(2);
    Root.right = new Node(3);
    
    Root.left->left = new Node(4);
    Root.left->right = new Node(5);
    
    Root.left->right->left = new Node(6);
    Root.left->right->right = new Node(7);

    Root.right->right = new Node(8);

    Root.right->right->left = new Node(9);
    Root.right->right->right = new Node(10);

    vector<int> res = Inorder_Traversal(&Root);

    for (int i = 0; i < res.size(); i++) { cout << res[i] << " "; }
    
    return 0;
}
#include <iostream>

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

bool Is_Same_Tree(Node* Tree_1, Node* Tree_2) {
    if (Tree_1 == nullptr && Tree_2 == nullptr) { return true;}
    
    if (
        Tree_1 == nullptr && Tree_2 != nullptr ||
        Tree_1 != nullptr && Tree_2 == nullptr
    ) { return false; }

    if (Tree_1->data == Tree_2->data) {
        return (
            Is_Same_Tree(Tree_1->left,  Tree_2->left) && 
            Is_Same_Tree(Tree_1->right, Tree_2->right)
        );
    } 
    
    return false;
}

int main(int argc, char* argv[]) {
    Node Root_T1(1);
    Root_T1.left  = new Node(2);
    Root_T1.right = new Node(3);
    
    Node Root_T2(1);
    Root_T2.left  = new Node(2);
    Root_T2.right = new Node(3);

    cout << Is_Same_Tree(&Root_T1, &Root_T2);

    return 0;
}
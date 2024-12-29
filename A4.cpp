#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    int max_path_sum;
    
    int find_max_path(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        
        int left_max = max(0, find_max_path(node->left));
        int right_max = max(0, find_max_path(node->right));
        
        int current_path_sum = left_max + node->val + right_max;
        
        max_path_sum = max(max_path_sum, current_path_sum);
        
        return max(left_max, right_max) + node->val;
    }
    
public:
    int max_path_sum_f(TreeNode* root) {
        this->max_path_sum = INT_MIN;
        find_max_path(root);
        return this->max_path_sum;
    }
};

TreeNode* create_node(int value) {
    return new TreeNode(value);
}

void delete_tree(TreeNode* root) {
    if (root == nullptr) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

int main() {
    TreeNode* root1 = create_node(1);
    root1->left = create_node(2);
    root1->right = create_node(3);
    
    Solution solution;
    cout << "Test Case 1 Maximum Path Sum: " << solution.max_path_sum_f(root1) << endl;
    
    TreeNode* root2 = create_node(-10);
    root2->left = create_node(9);
    root2->right = create_node(20);
    root2->right->left = create_node(15);
    root2->right->right = create_node(7);
    
    cout << "Test Case 2 Maximum Path Sum: " << solution.max_path_sum_f(root2) << endl;
    
    delete_tree(root1);
    delete_tree(root2);
    
    return 0;
}

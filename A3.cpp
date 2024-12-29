#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    private:
        unordered_map<int, int> value_to_index;
        
        TreeNode* build_tree_helper(
            vector<int>& preorder, 
            vector<int>& inorder,
            int preorder_start, 
            int preorder_end,
            int inorder_start, 
            int inorder_end
        ) {
            if (preorder_start > preorder_end) { return nullptr; }
            
            TreeNode* root = new TreeNode(preorder[preorder_start]);
            
            int root_index = value_to_index[preorder[preorder_start]];
            
            int left_subtree_size = root_index - inorder_start;
            
            root->left = build_tree_helper(
                preorder, inorder,
                preorder_start + 1,
                preorder_start + left_subtree_size,
                inorder_start,
                root_index - 1
            );
            
            root->right = build_tree_helper(
                preorder, inorder,
                preorder_start + left_subtree_size + 1,
                preorder_end,
                root_index + 1,
                inorder_end
            );
            
            return root;
        }
        
    public:
        TreeNode* build_tree(vector<int>& preorder, vector<int>& inorder) {
            int n = preorder.size();
            
            for (int i = 0; i < n; i++) { value_to_index[inorder[i]] = i; }
            
            return build_tree_helper(preorder, inorder, 0, n - 1, 0, n - 1);
        }
};

void print_tree(TreeNode* root, string prefix = "", bool is_left = false) {
    if (root == nullptr) return;
    
    cout << prefix;
    cout << (is_left ? "+-- " : "+-- ");  
    cout << root->val << endl;
    
    print_tree(root->left, prefix + "    ", true);
    print_tree(root->right, prefix + "    ", false);
}

void delete_tree(TreeNode* root) {
    if (root == nullptr) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

int main() {
    vector<int> preorder = {3, 9, 20, 15, 7};  
    vector<int> inorder = {9, 3, 15, 20, 7};   
    
    Solution solution;
    TreeNode* root = solution.build_tree(preorder, inorder);
    
    cout << "Constructed Binary Tree:" << endl;
    print_tree(root);
    
    delete_tree(root);
    
    return 0;
}
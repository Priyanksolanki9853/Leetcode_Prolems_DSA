/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int count = 0;

    // returns {sum of subtree, number of nodes in subtree}
    pair<int,int> dfs(TreeNode* node) {
        if (!node) return {0, 0};

        auto left = dfs(node->left);
        auto right = dfs(node->right);

        int sum = left.first + right.first + node->val;
        int nodes = left.second + right.second + 1;

        if (node->val == sum / nodes) {
            count++;
        }

        return {sum, nodes};
    }

    int averageOfSubtree(TreeNode* root) {
        dfs(root);
        return count;
    }
};
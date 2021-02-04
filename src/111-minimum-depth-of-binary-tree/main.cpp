// https://leetcode.com/problems/minimum-depth-of-binary-tree/
// 111. Minimum Depth of Binary Tree

// Given a binary tree, find its minimum depth.
// The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
// Note: A leaf is a node with no children.
//
// Example 1:
//    Input: root = [3, 9, 20, null, null, 15, 7]
//    Output : 2
// Example 2:
//    Input : root = [2, null, 3, null, 4, null, 5, null, 6]
//    Output : 5
// Constraints:
//    The number of nodes in the tree is in the range[0, 105].
//    - 1000 <= Node.val <= 1000

// Time:  O(n)
// Space: O(1)
// Pattern: Tree breadth-first search

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int minDepth(TreeNode* root) {
    int minimumTreeDepth = 0;
    if (!root)
        return minimumTreeDepth;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        ++minimumTreeDepth;
        int levelSize = q.size();
        while (levelSize--) {
            TreeNode* n = q.front();
            q.pop();

            if (!n->left && !n->right)
                return minimumTreeDepth;

            if (n->left)
                q.push(n->left);
            if (n->right)
                q.push(n->right);
        }
    }
    return minimumTreeDepth;
}

void testMinDepth() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    assert(2 == minDepth(root));

    TreeNode* root2 = new TreeNode(2);
    root2->left = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->left->left = new TreeNode(5);
    root2->left->left->left->left = new TreeNode(6);
    assert(5 == minDepth(root2));
}

int main() {

    testMinDepth();

    return 0;
}

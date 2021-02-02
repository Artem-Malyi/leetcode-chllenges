// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
// 107. Binary Tree Level Order Traversal II

// Given a binary tree, return the bottom-up level order traversal of its nodes' values. 
// (i.e. from left to right, level by level from leaf to root).
//
// For example :
//    Given binary tree [3, 9, 20, null, null, 15, 7],
//           3
//          / \
//         9  20
//            / \
//           15   7
//    return its bottom - up level order traversal as :
//    [
//        [15, 7],
//        [9, 20],
//        [3]
//    ]

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
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        vector<int> levelValues;
        int levelSize = q.size();
        while (levelSize--) {
            TreeNode* n = q.front();
            if (n) {
                levelValues.push_back(n->val);
                q.push(n->left);
                q.push(n->right);
            }
            q.pop();
        }
        if (!levelValues.empty())
            result.insert(result.begin(), levelValues);
    }
    return result;
}

void testLevelOrderBottom() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    vector<vector<int>> exp1 = { {15,7}, {9,20}, {3} };
    vector<vector<int>> res1 = levelOrderBottom(root);
    assert(equal(res1.begin(), res1.end(), exp1.begin()));

    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(5);
    root2->right->left = new TreeNode(6);
    root2->right->right = new TreeNode(7);
    vector<vector<int>> exp2 = { {4,5,6,7}, {2,3}, {1} };
    vector<vector<int>> res2 = levelOrderBottom(root2);
    assert(equal(res2.begin(), res2.end(), exp2.begin()));
}

int main() {

    testLevelOrderBottom();

    return 0;
}

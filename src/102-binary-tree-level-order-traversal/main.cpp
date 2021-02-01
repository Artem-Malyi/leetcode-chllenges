// https://leetcode.com/problems/binary-tree-level-order-traversal/
// 102. Binary Tree Level Order Traversal

// Given a binary tree, return the level order traversal of its nodes' values. (i.e. from left to right, level by level).
//
// For example :
// Given binary tree[3, 9, 20, null, null, 15, 7],
//       3
//      / \
//     9  20
//        / \
//      15   7
// return its level order traversal as :
// [
//    [3],
//    [9, 20],
//    [15, 7]
// ]

// Time:  O(n)
// Space: O(n)
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

//      12
//     /  \
//   7      1
//    \    / \
//     9  10  5
//
// result:    [[12]]
// queue:              [1, null, 9]
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;

    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        vector<int> levelValues; // [7]
        int levelSize = q.size(); // 2
        while (levelSize--) { // 1
            TreeNode* n = q.front();
            if (n) {
                levelValues.push_back(n->val);
                q.push(n->left);
                q.push(n->right);
            }
            q.pop();
        }
        if (!levelValues.empty())
            result.push_back(levelValues);
    }

    return result;
}

void testLevelOrder() {
    //        12
    //      /   \
    //     7     1
    //      \   / \
    //       9 10  5
    TreeNode* root1 = new TreeNode(12);
    root1->left = new TreeNode(7);
    root1->right = new TreeNode(1);
    root1->left->left = new TreeNode(9);
    root1->right->left = new TreeNode(10);
    root1->right->right = new TreeNode(5);
    vector<vector<int>> res1 = levelOrder(root1);
    vector<vector<int>> exp1 = { {12}, {7,1}, {9,10,5} };
    assert(equal(exp1.begin(), exp1.end(), res1.begin()));

    //       3
    //      / \
    //     9  20
    //        / \
    //      15   7
    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(9);
    root2->right = new TreeNode(20);
    root2->right->left = new TreeNode(15);
    root2->right->right = new TreeNode(7);
    vector<vector<int>> res2 = levelOrder(root2);
    vector<vector<int>> exp2 = { {3}, {9,20}, {15,7} };
    assert(equal(exp2.begin(), exp2.end(), res2.begin()));
}

int main() {

    testLevelOrder();

    return 0;
}

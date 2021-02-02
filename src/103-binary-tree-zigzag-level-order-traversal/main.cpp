// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
// 103. Binary Tree Zigzag Level Order Traversal

// Given a binary tree, return the zigzag level order traversal of its nodes' values. 
// (i.e., from left to right, then right to left for the next level and alternate between).
//
// For example :
//    Given binary tree[3, 9, 20, null, null, 15, 7],
//         3
//        / \
//       9  20
//          / \
//        15   7
//    return its zigzag level order traversal as :
//    [
//        [3],
//        [20, 9],
//        [15, 7]
//    ]
// Example 2:
//         12
//        /  \
//       7    1
//      /    / \
//     9    10  5
//         /  \
//        20  17
//    return its zigzag level order traversal as :
//    [
//        [12],
//        [1, 7],
//        [9, 10, 5],
//        [17, 20]
//    ]

// Time:  O(n)
// Space: O(n)
// Pattern: 

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

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);
    bool reverse = false;
    while (!q.empty()) {
        vector<int> levelValues;
        int levelSize = q.size();
        while (levelSize--) {
            TreeNode* n = q.front();
            if (n) {
                levelValues.insert(reverse ? levelValues.begin() : levelValues.end(), n->val);
                q.push(n->left);
                q.push(n->right);
            }
            q.pop();
        }
        reverse = !reverse;
        if (!levelValues.empty())
            result.push_back(levelValues);
    }
    return result;
}

void testZigzagLevelOrder() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    vector<vector<int>> exp1 = { {3}, {20,9}, {15,7} };
    vector<vector<int>> res1 = zigzagLevelOrder(root);
    assert(equal(res1.begin(), res1.end(), exp1.begin()));

    TreeNode* root2 = new TreeNode(12);
    root2->left = new TreeNode(7);
    root2->right = new TreeNode(1);
    root2->left->left = new TreeNode(9);
    root2->right->left = new TreeNode(10);
    root2->right->right = new TreeNode(5);
    root2->right->left->left = new TreeNode(20);
    root2->right->left->right = new TreeNode(17);
    vector<vector<int>> exp2 = { {12}, {1,7}, {9,10,5}, {17,20} };
    vector<vector<int>> res2 = zigzagLevelOrder(root2);
    assert(equal(res2.begin(), res2.end(), exp2.begin()));
}

int main() {

    testZigzagLevelOrder();

    return 0;
}

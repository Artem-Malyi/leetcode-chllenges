// https://leetcode.com/problems/average-of-levels-in-binary-tree/
// 637. Average of Levels in Binary Tree

// Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
// Example 1:
//    Input:
//     3
//    / \
//   9  20
//      / \
//    15   7
// Output: [3, 14.5, 11]
// Explanation :
//    The average value of nodes on level 0 is 3, on level 1 is 14.5, and on level 2 is 11. Hence return[3, 14.5, 11].
// Note:
//    The range of node's value is in the range of 32-bit signed integer.

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

vector<double> averageOfLevels(TreeNode* root) {
    if (!root)
        return {};
    vector<double> result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        double levelSize = q.size(), levelSum = 0;
        for (int i = 0; i < levelSize; i++) {
            TreeNode* n = q.front();
            q.pop();
            levelSum += n->val;
            if (n->left)
                q.push(n->left);
            if (n->right)
                q.push(n->right);
        }
        result.push_back(levelSum / levelSize);
    }
    return result;
}

void testAverageOfLevels() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    vector<double> exp1 = { 3, 14.5, 11 };
    vector<double> res1 = averageOfLevels(root);
    assert(equal(res1.begin(), res1.end(), exp1.begin()));

    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(5);
    root2->right->left = new TreeNode(6);
    root2->right->right = new TreeNode(7);
    vector<double> exp2 = { 1, 2.5, 5.5 };
    vector<double> res2 = averageOfLevels(root2);
    assert(equal(res2.begin(), res2.end(), exp2.begin()));

    TreeNode* root3 = new TreeNode(12);
    root3->left = new TreeNode(7);
    root3->right = new TreeNode(1);
    root3->left->left = new TreeNode(9);
    root3->left->right = new TreeNode(2);
    root3->right->left = new TreeNode(10);
    root3->right->right = new TreeNode(5);
    vector<double> exp3 = { 12.0, 4.0, 6.5 };
    vector<double> res3 = averageOfLevels(root3);
    assert(equal(res3.begin(), res3.end(), exp3.begin()));
}

int main() {

    testAverageOfLevels();

    return 0;
}

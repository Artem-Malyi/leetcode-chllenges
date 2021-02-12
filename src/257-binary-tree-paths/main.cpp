// https://leetcode.com/problems/binary-tree-paths/
// 257. Binary Tree Paths

// Given a binary tree, return all root-to-leaf paths.
// Note: A leaf is a node with no children.
//
// Example:
//    Input :
//
//       1
//     /   \
//    2     3
//     \
//      5
//
//    Output: ["1->2->5", "1->3"]
//    Explanation : All root-to-leaf paths are: 1->2->5, 1->3

// Time:  O(n)
// Space: O(n)
// Pattern: Tree depth-first search

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <stack>
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

// s: 
// p:
// current: 3
// path: "1->3"
// res: "1->2->5", "1->3"
vector<string> binaryTreePaths(TreeNode* root) {
    if (!root)
        return {};
    vector<string> res;
    stack<TreeNode*> s;
    stack<string> p;
    s.push(root);
    p.push(to_string(root->val));
    while (!s.empty()) {
        TreeNode* current = s.top();
        s.pop();
        string path = p.top();
        p.pop();
        if (current->right) {
            s.push(current->right);
            p.push(path + "->" + to_string(current->right->val));
        }
        if (current->left) {
            s.push(current->left);
            p.push(path + "->" + to_string(current->left->val));
        }
        if (!current->left && !current->right) {
            res.push_back(path);
        }
    }
    return res;
}

void testBinaryTreePaths() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    vector<string> exp = { "1->2->5", "1->3" };
    vector<string> res = binaryTreePaths(root);
    assert(equal(res.begin(), res.end(), exp.begin()));
}

int main() {

    testBinaryTreePaths();

    return 0;
}

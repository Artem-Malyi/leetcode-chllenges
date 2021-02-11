// https://leetcode.com/problems/binary-tree-right-side-view/
// 199. Binary Tree Right Side View

// Given a binary tree, imagine yourself standing on the right side of it, 
// return the values of the nodes you can see ordered from top to bottom.
//
// Example 1:
//              1 <--
//            /   \
//          2       3 <--
//         / \     / \
//        4   5   6   7 <--
//     Input:  [1, 2, 3, 4, 5, 6, 7]
//     Output: [1, 3, 7]
//
// Example 2:
//             12 <--
//            /   \
//          7       1 <--
//         /       / \
//        9       10  5 <--
//         \
//          3 <--
//     Input:  [12, 7, 1, 9, null, 10, 5, null, 3]
//     Output: [12, 1, 5, 3]

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
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

vector<int> rightSideView(TreeNode* root) {
    vector<int> result;
    if (!root)
        return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size();
        TreeNode* previous = nullptr;
        while (levelSize--) {
            TreeNode* current = q.front();
            q.pop();
            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
            previous = current;
        }
        result.push_back(previous->val);
    }
    return result;
}

void testRightSideView() {
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);
    root1->right->left = new TreeNode(6);
    root1->right->right = new TreeNode(7);
    vector<int> exp1 = { 1, 3, 7 };
    vector<int> res1 = rightSideView(root1);
    assert(equal(res1.begin(), res1.end(), exp1.begin()));

    TreeNode* root2 = new TreeNode(12);
    root2->left = new TreeNode(7);
    root2->right = new TreeNode(1);
    root2->left->left = new TreeNode(9);
    root2->right->left = new TreeNode(10);
    root2->right->right = new TreeNode(5);
    root2->left->left->right = new TreeNode(3);
    vector<int> exp2 = { 12, 1, 5, 3 };
    vector<int> res2 = rightSideView(root2);
    assert(equal(res2.begin(), res2.end(), exp2.begin()));
}

int main() {

    testRightSideView();

    return 0;
}

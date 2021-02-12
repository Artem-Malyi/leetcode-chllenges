// https://leetcode.com/problems/path-sum/
// 112. Path Sum

// Given a binary tree and a number 'S', find if the tree has a path from root-to-leaf such
// that the sum of all the node values of that path equals 'S'.
//
// Example 1:
//              1 <--
//            /   \
//          2       3 <--
//         / \     / \
//        4   5   6   7 
//                ^
//     Input:  [1, 2, 3, 4, 5, 6, 7], S = 10
//     Output: true
//     Explanation: The path with sum '10' is highlighted with arrows [1, 3, 6]
//
// Example 2:
//             12 <--
//            /   \
//          7       1 <--
//         /       / \
//        9       10  5
//                 ^
//     Input:  [12, 7, 1, 9, null, 10, 5], S = 23
//     Output: true
//     Explanation: The path with sum '23' is highlighted with arrows [12, 1, 10]
//
//     Input:  [12, 7, 1, 9, null, 10, 5], S = 16
//     Output: false
//     Explanation: There is no root-to-leaf path with sum '16'.

// Time:  O(n)
// Space: O(n)
// Pattern: Tree depth-first search

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

//     12      
//    /  \
//   7    1
//  /    / \
// 9    10  5

                                               //  v 
bool hasPath(TreeNode* root, int sum) { // [12, 7, 1, 9, null, 10, 5], 23
    if (!root)
        return false;

    // if the current node is a leaf and its value is equal to the sum, we've found a path
    if (!root->left && !root->right && root->val == sum) // 10 == 10
        return true;

    // recursively call to traverse the left and right sub-tree
    // return true if any of the two recursive call return true
    return hasPath(root->left, sum - root->val) || hasPath(root->right, sum - root->val);
}

void testHasPath() {
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);
    root1->right->left = new TreeNode(6);
    root1->right->right = new TreeNode(7);
    assert(true == hasPath(root1, 10));

    TreeNode* root2 = new TreeNode(12);
    root2->left = new TreeNode(7);
    root2->right = new TreeNode(1);
    root2->left->left = new TreeNode(9);
    root2->right->left = new TreeNode(10);
    root2->right->right = new TreeNode(5);
    assert(true == hasPath(root2, 23));
    assert(false == hasPath(root2, 16));
}

int main() {

    testHasPath();

    return 0;
}

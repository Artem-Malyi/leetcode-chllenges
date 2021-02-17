// Didn't find it on LeetCode
// Tree Path With Given Sequence

// Given a binary treeand a number sequence, find if the sequence is present as a root-to-leaf path in the given tree.
//
// Example 1:
//       1
//      / \
//     7   9
//        / \
//       2   9
//    Sequence: [1, 9, 9] 
//        Output: true 
//        Explanation: The tree has a path 1 -> 9 -> 9.
// Example 2 :
//       1
//      / \
//     0   1
//    /   / \
//   1   6   5
//    Sequence: [1, 0, 7] 
//        Output: false 
//        Explanation: The tree does not have a path 1 -> 0 -> 7.
//    Sequence: [1, 1, 6] 
//        Output: true 
//        Explanation: The tree has a path 1 -> 1 -> 6.

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

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) {
        val = x;
        left = right = nullptr;
    }
};

bool findPathRecursive(TreeNode* root, const vector<int>& sequence, int index);
//     1
//    / \
//   0   1
//  /   / \
// 1   6   5

bool findPath(TreeNode* root, const vector<int>& sequence) {
    if (!root)
        return false;
    return findPathRecursive(root, sequence, 0);
}

// index: 0
//  v
// [1, 0, 1, 1, 6, 5], [1, 1, 6] --> true 
bool findPathRecursive(TreeNode* root, const vector<int>& sequence, int index) {
    if (!root)
        return false;

    if (index < 0 || sequence.size() <= index ||  // 3 <= 2
        sequence[index] != root->val) // 6 != 6
        return false;

    if (!root->left && !root->right && index == sequence.size() - 1) {
        return true;
    }

    return findPathRecursive(root->left, sequence, index + 1) ||
        findPathRecursive(root->right, sequence, index + 1);
}

void testFindPath() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(0);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(1);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(5);

    assert(false == findPath(root, vector<int>{1, 0, 7}));
    assert(true == findPath(root, vector<int>{1, 1, 6}));
}

int main() {

    testFindPath();

    return 0;
}

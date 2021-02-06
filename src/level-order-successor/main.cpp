// Didn't find it on LeetCode
// Level Order Successor

// Given a binary treeand a node, find the level order successor of the given node in the tree.
// The level order successor is the node that appears right after the given node in the level order traversal.
//
// Example 1:
//    Input: root = [1, 2, 3, 4, 5], 3
//         1
//        / \
//       2   3
//      / \
//     4   5
//    Output: 4
// Example 2:
//    Input: root = [12, 7, 1, 9, null, 10, 5], 9
//        12
//        / \
//       7   1
//      /   / \
//     9   10  5
//    Output: 10
// Example 3:
//    Input: root = [12, 7, 1, 9, null, 10, 5], 12
//        12
//        / \
//       7   1
//      /   / \
//     9   10  5
//    Output: 7


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


TreeNode* findSuccessor(TreeNode* root, int key) {
    if (!root)
        return root;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* n = q.front();
        q.pop();
        if (n->left)
            q.push(n->left);
        if (n->right)
            q.push(n->right);
        if (n->val == key && !q.empty()) {
            return q.front();
        }
    }
    return nullptr;
}

void testFindSuccessor() {
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);
    TreeNode* res1 = findSuccessor(root1, 3);
    assert(res1 && res1->val == 4);
    assert(nullptr == findSuccessor(root1, 100));
    assert(nullptr == findSuccessor(root1, 5));

    TreeNode* root2 = new TreeNode(12);
    root2->left = new TreeNode(7);
    root2->right = new TreeNode(1);
    root2->left->left = new TreeNode(9);
    root2->right->left = new TreeNode(10);
    root2->right->right = new TreeNode(5);
    TreeNode* res2 = findSuccessor(root2, 9);
    assert(res2 && res2->val == 10);
    TreeNode* res3 = findSuccessor(root2, 12);
    assert(res3 && res3->val == 7);
}

int main() {

    testFindSuccessor();

    return 0;
}

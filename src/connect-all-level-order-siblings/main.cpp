// Didn't find it on LeetCode
// Connect All Level Order Siblings

// Given a binary tree, connect each node with its level order successor. 
// The last node of each level should point to the first node of the next level.
//
// Example 1:
//              1 ----+
//            /   \   |
//    +---------------+
//    +---> 2   ->  3 ----+
//         / \     / \    |
//    +-------------------+
//    +-> 4 ->5 ->6 ->7 -> null
//
//     Input:  [1, 2, 3, 4, 5, 6, 7]
//     Output: [1, 2, 3, 4, 5, 6, 7]
//
// Example 2:
//             12 ----+
//            /   \   |
//    +---------------+
//    +---> 7   ->  1 ----+
//         /       / \    |
//    +-------------------+
//    +-> 9  ->  10 ->5 -> null
//
//     Input:  [12, 7, 1, 9, null, 10, 5]
//     Output: [12, 7, 1, 9, null, 10, 5]


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
    TreeNode* next;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) { }
};

string toString(TreeNode* n) {
    string s;
    while (n) {
        s.append(to_string(n->val));
        n = n->next;
    }
    return s;
}

void connect(TreeNode* root) {
    if (!root)
        return;
    queue<TreeNode*> q;
    q.push(root);
    TreeNode* previous = nullptr;
    while (!q.empty()) {
        int levelSize = q.size();
        while (levelSize--) {
            TreeNode* current = q.front();
            q.pop();
            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);

            if (previous)
                previous->next = current;
            previous = current;
        }
    }
}

void testConnect() {
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);
    root1->right->left = new TreeNode(6);
    root1->right->right = new TreeNode(7);
    connect(root1);
    assert("1234567" == toString(root1));

    TreeNode* root2 = new TreeNode(12);
    root2->left = new TreeNode(7);
    root2->right = new TreeNode(1);
    root2->left->left = new TreeNode(9);
    root2->right->left = new TreeNode(10);
    root2->right->right = new TreeNode(5);
    connect(root2);
    assert("12719105" == toString(root2));
}


int main() {

    testConnect();

    return 0;
}

// Didn't find it on LeetCode
// Connect Level Order Siblings

// Given a binary tree, connect each node with its level order successor.
// The last node of each level should point to a null node.
//
// Example 1:
//              1 -> null
//            /   \
//          2   ->  3 -> null
//         / \     / \
//        4 ->5 ->6 ->7 -> null
//     Input:  [1, 2, 3, 4, 5, 6, 7]
//     Output: [
//       [1],
//       [2, 3],
//       [4, 5, 6, 7]
//     ]
//
// Example 2:
//             12 -> null
//            /   \
//          7   ->  1 -> null
//         /       / \
//        9  ->  10 ->5 -> null
//     Input:  [12, 7, 1, 9, null, 10, 5]
//     Output: [
//       [12],
//       [7, 1],
//       [9, 10, 5]
//     ]


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

// level order traversal using 'next' pointer
vector<string> printLevelOrder(TreeNode* n) {
    vector<string> res;
    TreeNode* nextLevelRoot = n;
    while (nextLevelRoot != nullptr) {
        string s;
        TreeNode* current = nextLevelRoot;
        nextLevelRoot = nullptr;
        while (current != nullptr) {
            s.append(to_string(current->val));
            if (nextLevelRoot == nullptr) {
                if (current->left != nullptr) {
                    nextLevelRoot = current->left;
                }
                else if (current->right != nullptr) {
                    nextLevelRoot = current->right;
                }
            }
            current = current->next;
        }
        res.push_back(s);
    }
    return res;
}

void connect(TreeNode* root) {
    if (!root)
        return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* previous = nullptr;
        size_t levelSize = q.size();
        while (levelSize--) {
            TreeNode* current = q.front();
            q.pop();
            if (previous)
                previous->next = current;
            previous = current;
            if (current->left)
                q.push(current->left);
            if (current->right)
                q.push(current->right);
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
    vector<string> exp1 = {"1", "23", "4567"};
    connect(root1);
    vector<string> res1 = printLevelOrder(root1);
    assert(equal(res1.begin(), res1.end(), exp1.begin()));

    TreeNode* root2 = new TreeNode(12);
    root2->left = new TreeNode(7);
    root2->right = new TreeNode(1);
    root2->left->left = new TreeNode(9);
    root2->right->left = new TreeNode(10);
    root2->right->right = new TreeNode(5);
    vector<string> exp2 = { "12", "71", "9105" };
    connect(root2);
    vector<string> res2 = printLevelOrder(root2);
    assert(equal(res2.begin(), res2.end(), exp2.begin()));
}

int main() {

    testConnect();

    return 0;
}

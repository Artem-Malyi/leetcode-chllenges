// https://leetcode.com/problems/path-sum-ii/
// 113. Path Sum II

// Given the root of a binary tree and an integer targetSum,
// return all root-to-leaf paths where each path's sum equals targetSum.
// A leaf is a node with no children.
//
// Example 1:
//             5
//          /     \
//        4         8
//       /        /   \
//      11       13    4
//     /  \           / \
//    7    2         5   1
//    Input: root = [5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1], targetSum = 22
//    Output: [[5, 4, 11, 2], [5, 8, 4, 5]]
// Example 2:
//      1
//     / \
//    2   3
//    Input: root = [1, 2, 3], targetSum = 5
//    Output: []
// Example 3:
//      1
//     /
//    2
//    Input: root = [1, 2], targetSum = 0
//    Output: []
// Constraints:
//    The number of nodes in the tree is in the range[0, 5000].
//    - 1000 <= Node.val <= 1000
//    - 1000 <= targetSum <= 1000

// Time:  O(nlogn)
// Space: O(nlogn)
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

// Since, for binary trees, there exists only one path to reach any leaf node, we can easily say that total
// root-to-leaf paths in a binary tree can't be more than the number of leaves. As we know that there can't
// be more than (N + 1) / 2 leaves in a binary tree, therefore the maximum number of elements in allPaths
// will be O((N + 1) / 2) = O(N). Now, each of these paths can have many nodes in them. For a balanced binary
// tree (like above), each leaf node will be at maximum depth. As we know that the depth (or height) of a
// balanced binary tree is O(logN) we can say that, at the most, each path can have logN nodes in it. This
// means that the total size of the allPaths list will be O(N*logN). If the tree is not balanced, we will
// still have the same worst-case space complexity.
//
// From the above discussion, we can conclude that our algorithm's overall space complexity is O(N*logN).
//
// Also, from the above discussion, since for each leaf node, in the worst case, we have to copy log(N) nodes
// to store its path; therefore, the time complexity of our algorithm will also be O(N*logN).

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

vector<vector<int>> pathSumIterative(TreeNode* root, int targetSum) {
    if (!root)
        return {};
    vector<vector<int>> allPaths;
    stack<TreeNode*> nodeStack;
    nodeStack.push(root);
    stack<vector<int>> pathStack;
    pathStack.push({ root->val });
    while (!nodeStack.empty()) {
        TreeNode* node = nodeStack.top();
        nodeStack.pop();
        vector<int> path = pathStack.top();
        pathStack.pop();
        if (node->right) {
            nodeStack.push(node->right);
            vector<int> rightPath = path; rightPath.push_back(node->right->val);
            pathStack.push(rightPath); // 7: [12, 7]
        }
        if (node->left) {
            nodeStack.push(node->left);
            vector<int> leftPath = path; leftPath.push_back(node->left->val);
            pathStack.push(leftPath);
        }
        if (!node->left && !node->right) { // leaf node
            int sum = 0;
            for (auto i : path)
                sum += i;
            if (sum == targetSum)
                allPaths.push_back(path);
        }
    }
    return allPaths; // --> [ [12, 7, 4], [12, 1, 10] ]
}

// allPaths: [[5, 4, 11, 2], [5, 8, 4, 5]]
// targetSum: 22
// currentPath: []
//  v
// [5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1], 22 ---> [[5, 4, 11, 2],[5, 8, 4, 5]]
void pathSumRecursive(TreeNode* node, int targetSum, vector<int>& currentPath, vector<vector<int>>& allPaths) {
    if (!node)
        return;

    currentPath.push_back(node->val);
    if (!node->left && !node->right && targetSum == node->val) { // 5 == 1
        allPaths.push_back(currentPath);
    }

    pathSumRecursive(node->left, targetSum - node->val, currentPath, allPaths);
    pathSumRecursive(node->right, targetSum - node->val, currentPath, allPaths);

    currentPath.pop_back();
}

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> allPaths;
    vector<int> currentPath;
    pathSumRecursive(root, targetSum, currentPath, allPaths);
    return allPaths;
}

void testPathSum() {
    //    Input: root = [5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1], targetSum = 22
    //    Output: [[5, 4, 11, 2], [5, 8, 4, 5]]
    TreeNode* root1 = new TreeNode(5);
    root1->left = new TreeNode(4);
    root1->right = new TreeNode(8);
    root1->left->left = new TreeNode(11);
    root1->right->left = new TreeNode(13);
    root1->right->right = new TreeNode(4);
    root1->left->left->left = new TreeNode(7);
    root1->left->left->right = new TreeNode(2);
    root1->right->right->left = new TreeNode(5);
    root1->right->right->right = new TreeNode(1);
    vector<vector<int>> exp1 = { {5, 4, 11, 2}, {5, 8, 4, 5 } };
    vector<vector<int>> res1 = pathSumIterative(root1, 22);
    assert(equal(res1.begin(), res1.end(), exp1.begin()));

    vector<vector<int>> res12 = pathSum(root1, 22);
    assert(equal(res12.begin(), res12.end(), exp1.begin()));

    //    Input: root = [1, 2, 3], targetSum = 5
    //    Output: []
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    vector<vector<int>> exp2;
    vector<vector<int>> res2 = pathSumIterative(root2, 5);
    assert(equal(res2.begin(), res2.end(), exp2.begin()));

    vector<vector<int>> res22 = pathSum(root2, 5);
    assert(equal(res22.begin(), res22.end(), exp2.begin()));

    //    Input: root = [1, 2], targetSum = 0
    //    Output: []
    TreeNode* root3 = new TreeNode(1);
    root3->left = new TreeNode(2);
    vector<vector<int>> exp3;
    vector<vector<int>> res3 = pathSumIterative(root3, 0);
    assert(equal(res3.begin(), res3.end(), exp3.begin()));

    vector<vector<int>> res32 = pathSumIterative(root3, 0);
    assert(equal(res32.begin(), res32.end(), exp3.begin()));
};

int main() {

    testPathSum();

    return 0;
}

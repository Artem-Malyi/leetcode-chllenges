// https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
// 448. Find All Numbers Disappeared in an Array

// Given an array of integers where 1 <= a[i] <= n(n = size of array), some elements appear twiceand others appear once.
// Find all the elements of [1, n] inclusive that do not appear in this array.
// Could you do it without extra spaceand in O(n) runtime ?
// You may assume the returned list does not count as extra space.
//
// Example:
//    Input:  [4, 3, 2, 7, 8, 2, 3, 1]
//    Output: [5, 6]

// Time:  O(n)
// Space: O(1)
// Pattern: Cyclic sort

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> findDisappearedNumbers(vector<int>& nums) {
    if (nums.size() < 2)
        return nums;
    for (int i = 0; i < nums.size(); i++) { // [1, 2, 3, 1, 5, 3, 2, 8]
        while (nums[i] - 1 != i && nums[i] != nums[nums[i] - 1]) {
            int tmp = nums[nums[i] - 1];
            nums[nums[i] - 1] = nums[i];
            nums[i] = tmp;
        }
    }
    vector<int> missingNumbers;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] - 1 != i)
            missingNumbers.push_back(i + 1);
    }
    return missingNumbers;
}

void testFindDisappearedNumbers() {
    vector<int> exp1 = { 5, 6 };
    vector<int> inp1 = { 4, 3, 2, 7, 8, 2, 3, 1 };
    vector<int> res1 = findDisappearedNumbers(inp1);
    assert(equal(exp1.begin(), exp1.end(), res1.begin()));

    vector<int> exp2 = { 1, 9, 10, 11, 12, 13, 14 };
    vector<int> inp2 = { 4, 4, 5, 6, 3, 3, 2, 3, 4, 5, 6, 7, 8, 5 };
    vector<int> res2 = findDisappearedNumbers(inp2);
    assert(equal(exp2.begin(), exp2.end(), res2.begin()));

    vector<int> exp3 = { 4, 6, 7 };
    vector<int> inp3 = { 2, 3, 1, 8, 2, 3, 5, 1 };
    vector<int> res3 = findDisappearedNumbers(inp3);
    assert(equal(exp3.begin(), exp3.end(), res3.begin()));

    vector<int> exp4 = { 3 };
    vector<int> inp4 = { 2, 4, 1, 2 };
    vector<int> res4 = findDisappearedNumbers(inp4);
    assert(equal(exp4.begin(), exp4.end(), res4.begin()));

    vector<int> exp5 = { 4 };
    vector<int> inp5 = { 2, 3, 2, 1 };
    vector<int> res5 = findDisappearedNumbers(inp5);
    assert(equal(exp5.begin(), exp5.end(), res5.begin()));
}

int main() {

    testFindDisappearedNumbers();

    return 0;
}

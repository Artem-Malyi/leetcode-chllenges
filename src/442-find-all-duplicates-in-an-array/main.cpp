// https://leetcode.com/problems/find-all-duplicates-in-an-array/
// 442. Find All Duplicates in an Array

// Given an array of integers, 1 <= a[i] <= n (n = size of array), some elements appear twice and others appear once.
// Find all the elements that appear twice in this array.
//
// Could you do it without extra spaceand in O(n) runtime ?
//
// Example 1:
//    Input:  [4, 3, 2, 7, 8, 2, 3, 1]
//    Output: [2, 3]
// Example 2:
//    Input:  [3, 4, 4, 5, 5]
//    Output: [4, 5]
// Example 3:
//    Input:  [5, 4, 7, 2, 3, 5, 3]
//    Output: [3, 5]

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

vector<int> findDuplicates(vector<int>&& nums) {
    vector<int> duplicateNumbers;
    for (int i = 0; i < nums.size(); i++) { // 5, 4, 3, 4, 5
        while (nums[i] - 1 != i && nums[nums[i] - 1] != nums[i]) {
            int tmp = nums[nums[i] - 1];
            nums[nums[i] - 1] = nums[i];
            nums[i] = tmp;
        }
    }
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] - 1 != i)
            duplicateNumbers.push_back(nums[i]);
    }
    return duplicateNumbers;
}

void testFindDuplicates() {
    vector<int> exp1 = { 2, 3 };
    vector<int> res1 = findDuplicates({ 4, 3, 2, 7, 8, 2, 3, 1 });
    sort(res1.begin(), res1.end());
    assert(equal(res1.begin(), res1.end(), exp1.begin()));

    vector<int> exp2 = { 4, 5 };
    vector<int> res2 = findDuplicates({ 3, 4, 4, 5, 5 });
    sort(res2.begin(), res2.end());
    assert(equal(res2.begin(), res2.end(), exp2.begin()));

    vector<int> exp3 = { 3, 5 };
    vector<int> res3 = findDuplicates({ 5, 4, 7, 2, 3, 5, 3 });
    sort(res3.begin(), res3.end());
    assert(equal(res3.begin(), res3.end(), exp3.begin()));
}

int main() {

    testFindDuplicates();

    return 0;
}

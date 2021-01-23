// https://leetcode.com/problems/first-missing-positive/
// 41. First Missing Positive

// Given an unsorted integer array nums, find the smallest missing positive integer.
//
// Follow up : Could you implement an algorithm that runs in O(n) time and uses constant extra space?
//
// Example 1:
//    Input : nums = [1, 2, 0]
//    Output : 3
// Example 2:
//    Input : nums = [3, 4, -1, 1]
//    Output : 2
// Example 3:
//    Input : nums = [7, 8, 9, 11, 12]
//    Output : 1
// Constraints :
//    0 <= nums.length <= 300
//    - 231 <= nums[i] <= 231 - 1

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

int firstMissingPositive(vector<int>&& nums) {
    int i = 0;
    while (i < nums.size()) {
        if (nums[i] > 0 && nums[i] <= nums.size() && nums[i] != nums[nums[i] - 1]) {
            int tmp = nums[nums[i] - 1];
            nums[nums[i] - 1] = nums[i];
            nums[i] = tmp;
        }
        else {
            ++i;
        }
    }

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != i + 1)
            return i + 1;
    }

    // no missing positives inside the given array, return the next number after it
    return nums.size() + 1;
}

void testFirstMissingPositive() {
    assert(3 == firstMissingPositive({1, 2, 0}));
    assert(2 == firstMissingPositive({ 3, 4, -1, 1 }));
    assert(1 == firstMissingPositive({ 7, 8, 9, 11, 12 }));
}

int main() {

    testFirstMissingPositive();

    return 0;
}

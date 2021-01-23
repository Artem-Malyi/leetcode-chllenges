// Didn't find it on LeetCode
// Find the Smallest Missing Positive Number

// Given an unsorted array containing numbers, find the smallest missing positive number in it.
//
// Example 1:
//    Input: [-3, 1, 5, 4, 2]
//    Output : 3
//    Explanation : The smallest missing positive number is '3'
// Example 2 :
//    Input : [3, -2, 0, 1, 2]
//    Output : 4
// Example 3 :
//    Input : [3, 2, 5, 1]
//    Output : 4

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

int findNumber(vector<int>&& nums) {
    for (int i = 0; i < nums.size(); i++) {
        while (nums[i] > 0 && nums[i] <= nums.size() && nums[i] != nums[nums[i] - 1]) {
            int tmp = nums[nums[i] - 1];
            nums[nums[i] - 1] = nums[i];
            nums[i] = tmp;
        }
    }

    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != i + 1)
            return i + 1;
    }

    // no missing positives inside the given array, return the next number after it
    return nums.size() + 1;
}

void testFindNumber() {
    assert(3 == findNumber({ -3, 1, 5, 4, 2 }));
    assert(4 == findNumber({ 3, -2, 0, 1, 2 }));
    assert(4 == findNumber({ 3, 2, 5, 1 }));
}

int main() {

    testFindNumber();

    return 0;
}

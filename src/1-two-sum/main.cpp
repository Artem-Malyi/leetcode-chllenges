// https://leetcode.com/problems/two-sum/
// 1. Two Sum

// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
// You can return the answer in any order.

// Time:  O(n)
// Space: O(n)
// Pattern: Two pointers

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// O(n) solution

vector<int> twoSum(vector<int>&& nums, int target) { // [5, 75, 25], 6 -> [0, 1]
    vector<pair<int, int>> indVal; // O(n)
    for (int i = 0; i < nums.size(); ++i) {
        indVal.push_back({ nums[i], i });
    }

    sort(nums.begin(), nums.end()); // O(n * log(n))

    int l = 0, r = nums.size() - 1; // 0, 1
    while (l < r) { // O(n)
        int sum = nums[l] + nums[r]; // 6
        if (sum == target)
            break;
        else if (sum > target)
            --r;
        else
            ++l;
    }

    auto low = find_if(indVal.begin(), indVal.begin() + indVal.size(), [&](pair<int, int> elem) {
        return elem.first == nums[l]; // 3:0
    }); // O(1)
    if (low != indVal.end()) {
        l = low->second;
        indVal.erase(low);
    }

    auto high = find_if(indVal.begin(), indVal.begin() + indVal.size(), [&](pair<int, int> elem) {
        return elem.first == nums[r];
        }); // O(1)
    if (high != indVal.end())
        r = high->second;

    return { l, r };
}

void testTwoSum() {
    vector<int> res1 = { 0, 1 };
    assert(res1 == twoSum({ 2, 7, 11, 15 }, 9));

    vector<int> res2 = { 1, 2 };
    assert(res2 == twoSum({ 3, 2, 4 }, 6));

    vector<int> res3 = { 0, 1 };
    assert(res3 == twoSum({ 3, 3 }, 6));
}

int main() {

    testTwoSum();

    return 0;
}

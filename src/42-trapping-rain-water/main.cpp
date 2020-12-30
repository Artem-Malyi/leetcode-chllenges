// https://leetcode.com/problems/trapping-rain-water/
// 42. Trapping Rain Water

// Given n non-negative integers representing an elevation map where the width of each bar is 1, 
// compute how much water it can trap after raining.
//
// Example 1:
//   Input: height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]
//   Output : 6
//   Explanation : The above elevation map(black section) is represented by array[0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1].
//   In this case, 6 units of rain water(blue section) are being trapped.
// Example 2:
//   Input: height = [4, 2, 0, 3, 2, 5]
//   Output : 9
//
// Constraints:
//   n == height.length
//   0 <= n <= 3 * 104
//   0 <= height[i] <= 105

// Time:  O(n)
// Space: O(1)
// Pattern: Two pointers

#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int trap(vector<int>&& height) {
    int ans = 0;
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax)
                leftMax = height[left];
            else
                ans += leftMax - height[left];
            left++;
        }
        else {
            if (height[right] >= rightMax)
                rightMax = height[right];
            else
                ans += rightMax - height[right];
            right--;
        }
    }
    return ans;
}

void testTrap() {
    assert(6 == trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}));
    assert(9 == trap({4, 2, 0, 3, 2, 5}));
    assert(5471 == trap({ 1, 2, 6, 3, 34, 5, 65, 4, 3, 3, 453, 45, 345, 34, 534, 5, 567, 5678, 6, 45, 54, 34, 53, 45, 435, 74, 567, 54}));
}

int main() {

    testTrap();

    return 0;
}

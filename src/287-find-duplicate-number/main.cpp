// https://leetcode.com/problems/find-the-duplicate-number/
// 287. Find the Duplicate Number

// Given an array of integers nums containing n + 1 integers where each integer is in the range[1, n] inclusive.
// There is only one repeated number in nums, return this repeated number.
//
// Example 1:
//     Input: nums = [1, 3, 4, 2, 2]
//     Output : 2
// Example 2:
//    Input : nums = [3, 1, 3, 4, 2]
//    Output : 3
// Example 3:
//    Input : nums = [1, 1]
//    Output : 1
// Example 4:
//    Input : nums = [1, 1, 2]
//    Output : 1
// Constraints:
//    2 <= n <= 3 * 104
//    nums.length == n + 1
//    1 <= nums[i] <= n
//    All the integers in nums appear only once except for precisely one integer which appears two or more times.
// Follow up:
//    How can we prove that at least one duplicate number must exist in nums ?
//    Can you solve the problem without modifying the array nums ?
//    Can you solve the problem using only constant, O(1) extra space ?
//    Can you solve the problem with runtime complexity less than O(n2) ?

// Time:  O(n)
// Space: O(1), two solutions: with and without input modification
// Pattern: Cyclic sort and Fast & Slow pointers

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Time:  O(n)
// Space: O(1) with input modification (cyclic sort)
int findDuplicate1(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        while (nums[i] - 1 != i) {
            // check for duplicate
            if (nums[i] == nums[nums[i] - 1])
                return nums[i];
            // swap
            int tmp = nums[nums[i] - 1];
            nums[nums[i] - 1] = nums[i];
            nums[i] = tmp;
        }
    }
    return -1;
}


int findStart(const vector<int>& arr, int cycleLength);

// Time: O(n)
// Space: O(1) without input modification (fast & slow pointers)
int findDuplicate2(const vector<int>& arr) {
    int slow = 0, fast = 0;
    do {
        slow = arr[slow];
        fast = arr[arr[fast]];
    } while (slow != fast);

    // find cycle length
    int current = arr[slow];
    int cycleLength = 0;
    do {
        current = arr[current];
        cycleLength++;
    } while (current != arr[slow]);

    return findStart(arr, cycleLength);
}

int findStart(const vector<int>& arr, int cycleLength) {
    int pointer1 = arr[0], pointer2 = arr[0];
    // move pointer2 ahead 'cycleLength' steps
    while (cycleLength > 0) {
        pointer2 = arr[pointer2];
        cycleLength--;
    }

    // increment both pointers until they meet at the start of the cycle
    while (pointer1 != pointer2) {
        pointer1 = arr[pointer1];
        pointer2 = arr[pointer2];
    }

    return pointer1;
}

void testFindDuplicate() {
    // test cyclic sort solution:
    vector<int> inp1 = { 1, 3, 4, 2, 2 };
    assert(2 == findDuplicate1(inp1));

    vector<int> inp2 = { 3, 1, 3, 4, 2 };
    assert(3 == findDuplicate1(inp2));

    vector<int> inp3 = { 1, 1 };
    assert(1 == findDuplicate1(inp3));

    vector<int> inp4 = { 1, 1, 2 };
    assert(1 == findDuplicate1(inp4));

    // test fast & slow pointers solution:
    assert(2 == findDuplicate2(inp1));

    assert(3 == findDuplicate2(inp2));

    assert(1 == findDuplicate2(inp3));

    assert(1 == findDuplicate2(inp4));
}

int main() {

    testFindDuplicate();

    return 0;
}

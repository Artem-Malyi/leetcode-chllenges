// https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/
// 1574. Shortest Subarray to be Removed to Make Array Sorted

// Given an integer array arr, remove a subarray(can be empty) from arr such that the remaining elements in arr are non - decreasing.
// A subarray is a contiguous subsequence of the array.
// Return the length of the shortest subarray to remove.

// Time:  O(n)
// Space: O(1)
// Pattern: Sliding Window

#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

                                               // left:        v
int findLengthOfShortestSubarray(vector<int>&& arr) { // [1,2,3,10,4,2,3,5] -> 3
                                               // right:          ^
    int N = arr.size(), left = 0, right = N - 1;

    // find the first number out of sorting order from the beginning
    while (left + 1 < N && arr[left] <= arr[left + 1])
        ++left;

    if (left == N - 1) // if the array is sorted
        return 0;

    // find the first number out of sorting order from the end
    while (right > left && arr[right - 1] <= arr[right])
        --right;

    // use a sliding window / two pointers to get tighter result
    int ans = min(N - left - 1, right), i = 0, j = right;
    while (i <= left && j < N) {
        if (arr[j] >= arr[i]) {
            // we can delete elements inbetween, and increment i to tighten the window
            ans = min(ans, j - i - 1);
            ++i;
        }
        else
            // we can't delete elements inbetween, so we increment j to loosen the window
            ++j;
    }
    return ans;
}

void testFindLengthOfShortestSubarray() {
    assert(3 == findLengthOfShortestSubarray({ 1, 2, 3, 10, 4, 2, 3, 5 }));
    assert(4 == findLengthOfShortestSubarray({5, 4, 3, 2, 1 }));
    assert(0 == findLengthOfShortestSubarray({ 1, 2, 3}));
    assert(0 == findLengthOfShortestSubarray({ 1 }));
    assert(3 == findLengthOfShortestSubarray({ 2, 2, 2, 1, 1, 1 }));
}

int main() {

    testFindLengthOfShortestSubarray();

    return 0;
}

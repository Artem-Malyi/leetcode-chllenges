// https://leetcode.com/problems/kth-missing-positive-number/
// 1539. Kth Missing Positive Number

// Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.
// Find the kth positive integer that is missing from this array.
//
// Example 1:
//    Input: arr = [2, 3, 4, 7, 11], k = 5
//    Output : 9
//    Explanation : The missing positive integers are[1, 5, 6, 8, 9, 10, 12, 13, ...].The 5th missing positive integer is 9.
// Example 2:
//    Input : arr = [1, 2, 3, 4], k = 2
//    Output : 6
//    Explanation : The missing positive integers are[5, 6, 7, ...].The 2nd missing positive integer is 6.
// Constraints:
//    1 <= arr.length <= 1000
//    1 <= arr[i] <= 1000
//    1 <= k <= 1000
//    arr[i] < arr[j] for 1 <= i < j <= arr.length

// Time:  two solutions - O(n) and O(logn)
// Space: O(1)
// Pattern: Binary search

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Time:  O(N)
// Space: O(1)
int findKthPositive2(vector<int>&& arr, int k) {
    // if the kth missing is less than arr[0]
    if (k <= arr[0] - 1)
        return k;
    k -= arr[0] - 1;

    // search kth missing between the array numbers
    for (int i = 0; i < arr.size() - 1; i++) {
        // missing between arr[i] and arr[i + 1]
        int currMissing = arr[i + 1] - arr[i] - 1;
        // if the kth missing is between
        // arr[i] and arr[i + 1] -> return it
        if (k <= currMissing)
            return arr[i] + k;
        // otherwise, proceed further with scanning the array
        k -= currMissing;
    }

    // we're here because the element to return is greater than the last element of the array
    return arr[arr.size() - 1] + k;
}

// Time:  O(logn)                               //          v
// Space: O(1)                                  //          v
int findKthPositive(vector<int>&& arr, int k) { // [2,3,4,7,11], k = 5  -> 9
    int left = 0, right = arr.size() - 1;       //        ^
    while (left <= right) { // 4 <= 3
        // Note that in C++ and Java we couldn't use straightforward pivot = (left + right) / 2 to avoid the possible overflow. In Python, the integers are not limited, and we're fine to do that.
        int pivot = left + (right - left) / 2; // 2
        // If number of positive integers which are missing before arr[pivot]
        // is less than k --> continue to search on the right.
        if (arr[pivot] - pivot - 1 < k)
            left = pivot + 1; // 4
        else
            right = pivot - 1; // Otherwise, go left.
    }
    // At the end of the loop, left == right + 1,
    // and the kth missing is in-between arr[right] and arr[left].
    // The number of integers missing before arr[right] is
    // arr[right] - right - 1 -->
    // the number to return is
    // arr[right] + k - (arr[right] - right - 1) = k + left
    return left + k;
}

void testFindKthPositive() {
    assert(9 == findKthPositive({ 2,3,4,7,11 }, 5));
    assert(6 == findKthPositive({ 1,2,3,4 }, 2));
    assert(9 == findKthPositive2({ 2,3,4,7,11 }, 5));
    assert(6 == findKthPositive2({ 1,2,3,4 }, 2));
}

int main() {

    testFindKthPositive();

    return 0;
}

// Didn't find it on LeetCode
// Cyclic sort

// We are given an array containing 'n' objects.Each object, when created, was assigned a unique number from 1 to 'n' 
// based on their creation sequence. This means that the object with sequence number '3' was created just before the object
// with sequence number '4'.
// Write a function to sort the objects in-place on their creation sequence number in O(n) and without any extra space.
// For simplicity, let's assume we are passed an integer array containing only the sequence numbers, though each number is
// actually an object.
//
// Example 1:
//    Input: [3, 1, 5, 4, 2]
//    Output : [1, 2, 3, 4, 5]
// Example 2:
//    Input : [2, 6, 4, 3, 1, 5]
//    Output : [1, 2, 3, 4, 5, 6]
// Example 3:
//    Input : [1, 5, 6, 4, 3, 2]
//    Output : [1, 2, 3, 4, 5, 6]

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

static void cyclicSort(vector<int>& nums) { //         v
    for (int i = 0; i < nums.size(); i++) { // 1,2,3,4,5
        while (nums[i] - 1 != i) {       // 4 != 4
            int tmp = nums[nums[i] - 1]; // 
            nums[nums[i] - 1] = nums[i]; // 
            nums[i] = tmp;               // 
        }
    }
}

void testCyclicSort() {
    vector<int> inp1 = { 4,2,3,1 };
    vector<int> exp1 = { 1,2,3,4 };
    cyclicSort(inp1);
    assert(equal(exp1.begin(), exp1.end(), inp1.begin()));

    vector<int> inp2 = { 3,2,5,1,4 };
    vector<int> exp2 = { 1,2,3,4,5 };
    cyclicSort(inp2);
    assert(equal(exp2.begin(), exp2.end(), inp2.begin()));

    vector<int> inp3 = { 1,6,4,5,2,3 };
    vector<int> exp3 = { 1,2,3,4,5,6 };
    cyclicSort(inp3);
    assert(equal(exp3.begin(), exp3.end(), inp3.begin()));
}

int main() {

    testCyclicSort();

    return 0;
}

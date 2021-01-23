// Didn't find it on LeetCode
// Find the Corrupt Pair

// We are given an unsorted array containing 'n' numbers taken from the range 1 to 'n'.
// The array originally contained all the numbers from 1 to 'n', but due to a data error, 
// one of the numbers got duplicated which also resulted in one number going missing.
// Find both these numbers.
//
// Example 1:
//    Input: [3, 1, 2, 5, 2]
//    Output : [2, 4]
//    Explanation : '2' is duplicated and '4' is missing.
// Example 2:
//    Input : [3, 1, 2, 3, 6, 4]
//    Output : [3, 5]
//    Explanation : '3' is duplicated and '5' is missing.

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

static vector<int> findNumbers(vector<int>&& nums) {
    for (int i = 0; i < nums.size(); i++) {
        while (nums[i] - 1 != i && nums[nums[i] - 1] != nums[i]) {
            int tmp = nums[nums[i] - 1];
            nums[nums[i] - 1] = nums[i];
            nums[i] = tmp;
        }
    }
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] - 1 != i)
            return { nums[i], i + 1 };
    }
    return vector<int>{-1, -1};
}

void testFindNumbers() {
    vector<int> exp1 = { 2, 4 };
    vector<int> res1 = findNumbers({ 3, 1, 2, 5, 2 });
    sort(res1.begin(), res1.end());
    assert(equal(res1.begin(), res1.end(), exp1.begin()));

    vector<int> exp2 = { 3, 5 };
    vector<int> res2 = findNumbers({ 3, 1, 2, 3, 6, 4 });
    sort(res2.begin(), res2.end());
    assert(equal(res2.begin(), res2.end(), exp2.begin()));
}

int main() {

    testFindNumbers();

    return 0;
}

// Didn't find it on LeetCode
// Find the First K Missing Positive Numbers

// Given an unsorted array containing numbersand a number 'k', find the first 'k' missing positive numbers in the array.
//
// Example 1:
//    Input: [3, -1, 4, 5, 5] , k = 3
//    Output : [1, 2, 6]
//    Explanation : The smallest missing positive numbers are 1, 2 and 6.
// Example 2:
//    Input : [2, 3, 4] , k = 3
//    Output : [1, 5, 6]
//    Explanation : The smallest missing positive numbers are 1, 5 and 6.
// Example 3:
//    Input : [-2, -3, 4] , k = 2
//    Output : [1, 2]
//    Explanation : The smallest missing positive numbers are 1 and 2.

// Time:  O(n)
// Space: O(1)
// Pattern: Cyclic sort

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> findNumbers(vector<int>&& nums, int k) {
    for (int i = 0; i < nums.size(); i++) {
        while (nums[i] > 0 && nums[i] <= nums.size() && nums[i] != nums[nums[i] - 1]) {
            int tmp = nums[nums[i] - 1];
            nums[nums[i] - 1] = nums[i];
            nums[i] = tmp;
        }
    }

    vector<int> missingNumbers;
    unordered_set<int> extraNumbers;
    for (int i = 0; i < nums.size() && missingNumbers.size() < k; i++) {
        if (nums[i] != i + 1) {
            missingNumbers.push_back(i + 1);
            extraNumbers.insert(nums[i]);
        }
    }

    // add the remaining missing numbers
    for (int i = 1; missingNumbers.size() < k; i++) {
        int candidateNumber = i + nums.size();
        // ignore if the array contains the candidate number
        if (extraNumbers.find(candidateNumber) == extraNumbers.end()) {
            missingNumbers.push_back(candidateNumber);
        }
    }

    return missingNumbers;
}

void testFindNumbers() {
    vector<int> exp1 = { 1, 2, 6 };
    vector<int> res1 = findNumbers({ 3, -1, 4, 5, 5 }, 3);
    assert(equal(res1.begin(), res1.end(), exp1.begin()));

    vector<int> exp2 = { 1, 5, 6 };
    vector<int> res2 = findNumbers({ 2, 3, 4 }, 3);
    assert(equal(res2.begin(), res2.end(), exp2.begin()));

    vector<int> exp3 = { 1, 2 };
    vector<int> res3 = findNumbers({ -2, -3, 4 }, 2);
    assert(equal(res3.begin(), res3.end(), exp3.begin()));
}

int main() {

    testFindNumbers();

    return 0;
}

// https://leetcode.com/problems/top-k-frequent-elements/
// 347. Top K Frequent Elements

// Given a non - empty array of integers, return the k most frequent elements.
// Example 1:
//   Input: nums = [1, 1, 1, 2, 2, 3], k = 2
//   Output : [1, 2]
// 
// Example 2:
//   Input : nums = [1], k = 1
//   Output : [1]
// Note:
//   You may assume k is always valid, 1 <= k <= number of unique elements.
//   Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
//   It's guaranteed that the answer is unique, in other words the set of the top k frequent elements is unique.
//   You can return the answer in any order.

// Time:  O(n)
// Space: O(n)
// Pattern:

#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) { // O(n + 2k)
    map<int, int> freq;
    for (auto n : nums)
        ++freq[n]; // O(n)

    multimap<int, int, greater<int>> freqFirst; 
    for (auto n : freq)
        freqFirst.insert({ n.second, n.first }); // O(k)

    vector<int> res;
    for (auto n : freqFirst) { // O(k)
        if (k--)
            res.push_back(n.second);
        else
            break;
    }

    return res;
}

void testTopKFrequent() {
    vector<int> v = { 1, 1, 1, 2, 2, 3 };
    vector<int> r = { 1, 2 };
    assert(std::equal(r.begin(), r.end(), topKFrequent(v, 2).begin()));
}

int main() {

    testTopKFrequent();

    return 0;
}
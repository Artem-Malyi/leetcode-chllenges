#include <Windows.h>

#include <cassert>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
                                        // windowStart:     v
int longestSubarray(vector<int>&& nums, int limit) {  // 1 2 68, 45
    int maxLength = 0, windowStart = 0; // windowEnd:       ^
    multiset<int> maxs;
    multiset<int, greater<int>> mins;
    unordered_map<int, int> freq;
    for (int windowEnd = 0; windowEnd < nums.size(); ++windowEnd) { // 2
        ++freq[nums[windowEnd]]; // 68:1
        maxs.insert(nums[windowEnd]); // 68
        mins.insert(nums[windowEnd]); // 68
        while (abs(*maxs.begin() - *mins.begin()) > limit) { // 0 > 45
            --freq[nums[windowStart]];
            if (0 == freq[nums[windowStart]]) {
                freq.erase(nums[windowStart]);
                maxs.erase(nums[windowStart]);
                mins.erase(nums[windowStart]);
            }
            ++windowStart; // 2
        }
        maxLength = max(maxLength, windowEnd - windowStart + 1); // 2
    }
    return maxLength;
}

void testLongestSubarray() {
    assert(2 == longestSubarray({ 8,2,4,7 }, 4));
    assert(4 == longestSubarray({ 10,1,2,4,7,2 }, 5));
    assert(3 == longestSubarray({ 4,2,2,2,4,4,2,2 }, 0));
    assert(18 == longestSubarray({ 8,2,4,7,3,4,5,6,7,8,9,5,4,3,2,5,5,7,56,5,34,5,3,2,34 }, 34));
}

int main() {

    testLongestSubarray();

	return 0;
}

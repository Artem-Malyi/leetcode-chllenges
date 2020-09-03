#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

                                     // windowStart:  v
int minSubArrayLen(int s, vector<int>&& nums) { // 15, 1 2 3 4 5 -> 5
    int windowStart = 0;             // windowEnd:            ^
    int windowSum = 0;
    int minLength = nums.empty() ? 0 : nums.size() + 1; // 1
    for (int windowEnd = 0; windowEnd < nums.size(); ++windowEnd) { // 4
        windowSum += nums[windowEnd]; // 15

        if (windowSum >= s) // 15 >= 15
            minLength = min(minLength, windowEnd - windowStart + 1); // min(1, 1) -> 1

        while (windowSum >= s) {
            windowSum -= nums[windowStart]; // 0
            ++windowStart; // 1
            if (windowSum >= s) // 0 >= 0
                minLength = min(minLength, windowEnd - windowStart + 1); // min(4, 3) -> 4
        }
    }
    return minLength == nums.size() + 1 ? 0 : minLength;
}

void testMinSubArrayLen() {
    assert(5 == minSubArrayLen(15, { 1, 2, 3, 4, 5 }));
    assert(2 == minSubArrayLen(7, { 2, 3, 1, 2, 4, 3 }));
}

int main() {

    testMinSubArrayLen();

    return 0;
}

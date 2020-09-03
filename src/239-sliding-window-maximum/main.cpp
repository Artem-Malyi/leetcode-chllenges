#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<int> maxSlidingWindow(vector<int>&& nums, int k) { // -7 -8 7 5 7 1 6 0, 4 -> 7 7 7 7 7
    int windowStart = 0;                       // windowEnd:              ^
    vector<int> ans(nums.size() - k + 1);
    map<int, int, greater<int>> window;
    for (int windowEnd = 0; windowEnd < nums.size(); ++windowEnd) { // 6
        ++window[nums[windowEnd]]; // [7, 6, 5, 1]

        if (windowEnd + 1 > k) { // 6 > 4
            --window[nums[windowStart]];
            if (window[nums[windowStart]] == 0)
                window.erase(nums[windowStart]);
            ++windowStart; // 2
        }

        if (windowEnd - windowStart + 1 == k) // 4 == 4
            ans[windowStart] = (window.begin())->first; // [7, 7, 7, 0, 0]
    }
    return ans;
}

void testMaxSlidingWindow() {
    vector<int> res1 = { 3, 3, 5, 5, 6, 7 };
    assert(res1 == maxSlidingWindow({ 1, 3, -1, -3, 5, 3, 6, 7 }, 3));

    vector<int> res2 = { 7, 7, 7, 7, 7 };
    assert(res2 == maxSlidingWindow({ -7, -8, 7, 5, 7, 1, 6, 0 }, 4));
}

int main() {

    testMaxSlidingWindow();

	return 0;
}

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

void twoSums(vector<int> nums, int targetSum, int left, vector<vector<int>>& threeSums);

vector<vector<int>> threeSums(vector<int>&& nums) {
    vector<vector<int>> threeSums;
    if (nums.size() < 2)
        return threeSums;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size() - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1])
            continue; // skip same elements to avoid 3sum duplicates
        twoSums(nums, -nums[i], i + 1, threeSums);
    }
    return threeSums;
}

void twoSums(vector<int> nums, int targetSum, int left, vector<vector<int>>& threeSums) {
    int right = nums.size() - 1;
    while (left < right) {
        int sum = nums[left] + nums[right];
        if (sum < targetSum)
            left++;
        else if (sum > targetSum)
            right--;
        else {
            threeSums.push_back({ -targetSum, nums[left], nums[right] });
            left++;
            while (left < right && nums[left] == nums[left - 1])
                left++; // skip same elements
            right--;
            while (left < right && nums[right] == nums[right + 1])
                right--;
        }
    }
}

void testThreeSums() {
    vector<vector<int>> res1 = { {-1, -1, 2}, {-1, 0, 1} };
    assert(res1 == threeSums({ -1, 0, 1, 2, -1, -4 }));

    vector<vector<int>> res2 = { {-3, 1, 2}, {-2, 0, 2}, {-2, 1, 1}, {-1, 0, 1} };
    assert(res2 == threeSums({ -3, 0, 1, 2, -1, 1, -2 }));

    vector<vector<int>> res3 = { {-5, 2, 3}, { -2, -1, 3} };
    assert(res3 == threeSums({ -5, 2, -1, -2, 3 }));

    vector<vector<int>> res4;
    assert(res4 == threeSums({ }));

    vector<vector<int>> res5;
    assert(res5 == threeSums({ 0 }));
}

int main() {

    testThreeSums();

	return 0;
}

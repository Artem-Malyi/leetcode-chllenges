#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Time complexity
// Sorting the array will take O(N*logN). Overall fourSum() will take O(N*logN + N^3), which is asymptotically equivalent to O(N^3)

// Space complexity
// The space complexity of the below algorithm will be O(N) which is required for sorting.

void searchPairs(const vector<int>& nums, int first, int second, int left, int targetSum, vector<vector<int>>& res);

// Input: nums = [1,0,-1,0,-2,2], target = 0
// Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
vector<vector<int>> fourSum(vector<int>&& nums, int target) {
    vector<vector<int>> res;
    if (nums.size() < 4)
        return res;
                                  //        v
    sort(begin(nums), end(nums)); // [-2 -1 -1 1 1 2 2]

    for (int first = 0; first < nums.size() - 3; first++) {
        if (first > 0 && nums[first - 1] == nums[first])
            continue;

        for (int second = first + 1; second < nums.size() - 2; second++) {
            if (second > first + 1 && nums[second - 1] == nums[second])
                continue;

            searchPairs(nums, first, second, second + 1, target, res);
        }
    }

    return res;
}

void searchPairs(const vector<int>& nums, int first, int second, int left, int targetSum, vector<vector<int>>& res) {
    int right = nums.size() - 1;
    while (left < right) {
        int sum = nums[first] + nums[second] + nums[left] + nums[right];
        if (sum < targetSum)
            left++;
        else if (sum > targetSum)
            right--;
        else { // found the quadruplet
            res.push_back({ nums[first], nums[second], nums[left], nums[right] });
            left++;
            right--;
            while (left < right && nums[left - 1] == nums[left])
                left++; // skip same element to avoid duplicate quadruplets
            while (left < right && nums[right + 1] == nums[right])
                right--; // skip same element to avoid duplicate quadruplets
        }
    }
}

void testFourSum() {
    vector<vector<int>> expected1 = { {-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1} };
    assert(fourSum({ 1, 0, -1, 0, -2, 2 }, 0) == expected1);

    vector<vector<int>> expected2 = { {-2,-1,1,2 }, { -1,-1,1,1 } };
    assert(fourSum({-2, -1, -1, 1, 1, 2, 2}, 0) == expected2);

    vector<vector<int>> expected3 = { {-3, -2, 2, 3}, {-3, -1, 1, 3}, {-3, 0, 0, 3}, {-3, 0, 1, 2}, {-2, -1, 0, 3}, {-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1} };
    assert(fourSum({ -3, -2, -1, 0, 0, 1, 2, 3 }, 0) == expected3);

    vector<vector<int>> expected4;
    assert(fourSum({ }, 0) == expected4);
}

int main() {

    testFourSum();

	return 0;
}

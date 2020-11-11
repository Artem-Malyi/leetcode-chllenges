#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int numSubarrayProductLessThanK(vector<int>&& nums, int k) { // [1,2,3], 0 -> 0
    int product = 1;
    int windowStart = 0;
    int count = 0;
    for (int windowEnd = 0; windowEnd < nums.size(); windowEnd++) { // 0
        product *= nums[windowEnd];

        while (product >= k && windowStart < nums.size() && windowStart <= windowEnd) { //1 >= 0
            product /= nums[windowStart++];
        }

        count += windowEnd - windowStart + 1;
    }
    return count;
}

void testNumSubarrayProductLessThanK() {
    assert(8 == numSubarrayProductLessThanK({ 10, 5, 2, 6 }, 100));
    assert(465 == numSubarrayProductLessThanK({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 3));
}

int main() {

    testNumSubarrayProductLessThanK();

	return 0;
}

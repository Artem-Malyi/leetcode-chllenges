#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int trap(vector<int>&& height) {
    int ans = 0;
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0;
    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax)
                leftMax = height[left];
            else
                ans += leftMax - height[left];
            left++;
        }
        else {
            if (height[right] >= rightMax)
                rightMax = height[right];
            else
                ans += rightMax - height[right];
            right--;
        }
    }
    return ans;
}

void testTrap() {
    assert(6 == trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}));
    assert(9 == trap({4, 2, 0, 3, 2, 5}));
    assert(5471 == trap({ 1, 2, 6, 3, 34, 5, 65, 4, 3, 3, 453, 45, 345, 34, 534, 5, 567, 5678, 6, 45, 54, 34, 53, 45, 435, 74, 567, 54}));
}

int main() {

    testTrap();

	return 0;
}

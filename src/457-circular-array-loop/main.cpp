#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Time:  O(n^2)
// Space: O(1)

int findNextIndex(const vector<int>& nums, bool isForward, int currentIndex);

bool circularArrayLoop(const vector<int>& nums) { // [-1, 2]
    for (int i = 0; i < nums.size(); i++) {
        bool isForward = nums[i] > 0; // if we are moving forward or not
        int slow = i, fast = i;

        // if slow or fast becomes -1, this means we cannot find cycle for this number
        do {
            slow = findNextIndex(nums, isForward, slow); // move one step for slow pointer
            fast = findNextIndex(nums, isForward, fast); // move one step for fast pointer
            if (fast != -1)
                fast = findNextIndex(nums, isForward, fast); // move another step for fast pointer
        } while (slow != -1 && fast != -1 && slow != fast);

        if (slow != -1 && slow == fast)
            return true;
    }
    return false;
}

int findNextIndex(const vector<int>& nums, bool isForward, int currentIndex) {
    bool direction = nums[currentIndex] > 0;
    if (direction != isForward)
        return -1; // change in direction, no cycle

    // wrap around for negative numbers
    int nextIndex = (currentIndex + nums[currentIndex] + nums.size()) % nums.size();

    if (nextIndex == currentIndex)
        return -1; // one-element cycle, means no cycle

    return nextIndex;
}

// Time Complexity
// The above algorithm will have a time complexity of O(N^2) where 'N' is the number of elements in the array.
// This complexity is due to the fact that we are iterating all elements of the arrayand trying to find a cycle for each element.
//
// Space Complexity
// The algorithm runs in constant space O(1).
//
// An Alternate Approach
// In our algorithm, we don't keep a record of all the numbers that have been evaluated for cycles.
// We know that all such numbers will not produce a cycle for any other instance as well.
// If we can remember all the numbers that have been visited, our algorithm will improve to O(N) as, then,
// each number will be evaluated for cycles only once. We can keep track of this by creating a separate array however the
// space complexity of our algorithm will increase to O(N).

void testCircularArrayLoop() {
    assert(true == circularArrayLoop({ 2, -1, 1, 2, 2 }));
    assert(true == circularArrayLoop({ 2, 2, -1, 2 }));
    assert(false == circularArrayLoop({ 2, 1, -1, -2 }));
    assert(false == circularArrayLoop({ -2, 1, -1, -2, -2, 2, 3, 4, 56, 76, 85, 4, 23, 24 }));
    assert(false == circularArrayLoop({ }));
}

int main() {

    testCircularArrayLoop();

    return 0;
}

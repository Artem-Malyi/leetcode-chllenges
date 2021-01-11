// https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/
// 452. Minimum Number of Arrows to Burst Balloons

// There are some spherical balloons spread in two-dimensional space.For each balloon, provided input is the start and 
// end coordinates of the horizontal diameter. Since it's horizontal, y-coordinates don't matter, and hence the x-coordinates
// of start and end of the diameter suffice. The start is always smaller than the end.
//
// An arrow can be shot up exactly vertically from different points along the x-axis. A balloon with xstart and xend bursts by 
// an arrow shot at x if xstart <= x <= xend. There is no limit to the number of arrows that can be shot. An arrow once shot keeps
// traveling up infinitely.
//
// Given an array points where points[i] = [xstart, xend], return the minimum number of arrows that must be shot to burst all balloons.
//
// Example 1:
//    Input: points = [[10, 16], [2, 8], [1, 6], [7, 12]]
//    Output : 2
//    Explanation : One way is to shoot one arrow for example at x = 6 (bursting the balloons[2, 8] and [1, 6]) and another arrow at x = 11 (bursting the other two balloons).
// Example 2:
//    Input : points = [[1, 2], [3, 4], [5, 6], [7, 8]]
//    Output : 4
// Example 3:
//    Input : points = [[1, 2], [2, 3], [3, 4], [4, 5]]
//    Output : 2
// Example 4:
//    Input : points = [[1, 2]]
//    Output : 1
// Example 5:
//    Input : points = [[2, 3], [2, 3]]
//    Output : 1
// Constraints:
//    0 <= points.length <= 104
//    points[i].length == 2
//    - 231 <= xstart < xend <= 231 - 1

// Time:  O(nlogn)
// Space: O(nlogn)
// Pattern: Merge intervals

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int findMinArrowShots(vector<vector<int>>&& points) {
    if (points.size() == 0)
        return 0;

    // sort by end time
    sort(begin(points), end(points),
        [](const vector<int>& o1, const vector<int>& o2) {
            return (o1[1] < o2[1]);
        });

    int arrows = 1;
    int xStart = 0, xEnd = 0, firstEnd = points[0][1]; // 6
    for (auto p : points) {
        xStart = p[0]; // 10
        xEnd = p[1]; // 16
        // if the current balloon starts after the end of the next one,
        // then we need one more arrow
        if (firstEnd < xStart) { // 12 < 10
            arrows++; // 2
            firstEnd = xEnd; // 12
        }
    }
    return arrows;
}

void testFindMinArrowsShots() {
    assert(2 == findMinArrowShots({ {10, 16}, {2, 8}, {1, 6 }, {7, 12} }));
    assert(4 == findMinArrowShots({ {1, 2}, {3, 4}, {5, 6}, {7, 8} }));
    assert(2 == findMinArrowShots({ {1, 2}, {2, 3}, {3, 4}, {4, 5} }));
    assert(1 == findMinArrowShots({ {1, 2} }));
    assert(1 == findMinArrowShots({ {2, 3}, {2, 3} }));
}

int main() {

    testFindMinArrowsShots();

    return 0;
}

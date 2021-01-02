// https://leetcode.com/problems/merge-intervals/
// 56. Merge Intervals

//Given an array of intervals where intervals[i] = [start[i], end[i]], merge all overlapping intervals, and return an array of the 
// non-overlapping intervals that cover all the intervals in the input.
//
// Example 1:
//    Input: intervals = [[1, 3], [2, 6], [8, 10], [15, 18]]
//    Output : [[1, 6], [8, 10], [15, 18]]
//    Explanation : Since intervals[1, 3] and [2, 6] overlaps, merge them into[1, 6].
// Example 2:
//    Input : intervals = [[1, 4], [4, 5]]
//    Output : [[1, 5]]
//    Explanation : Intervals[1, 4] and [4, 5] are considered overlapping.
//
// Constraints:
//    1 <= intervals.length <= 104
//    intervals[i].length == 2
//    0 <= starti <= endi <= 104

// Time:  O(nlogn)
// Space: O(n)
// Pattern: Merge intervals

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<vector<int>> merge(vector<vector<int>>&& intervals) { // 1,3 2,6 8,10 15,18
    if (intervals.size() < 2)
        return intervals;

    sort(intervals.begin(), intervals.end(),                          // it:                   v
        [](vector<int> lhs, vector<int> rhs) { return lhs[0] < rhs[0]; }); // 1,3 2,6 8,10 15,18

    vector<vector<int>>::const_iterator it = intervals.begin();
    vector<int> interval = *it++; // 1,3
    int start = interval[0], end = interval[1]; // 1, 6

    vector<vector<int>> mergedIntervals;

    while (it != intervals.end()) {
        interval = *it++; // 15,18
        if (interval[0] <= end) { // overlapping intervals, adjust the 'end' // 15 <= 10
            end = max(interval[1], end);
        }
        else { // non-overlapping intervals, add the previous interval and reset
            mergedIntervals.push_back({ start, end }); // 1,6 8,10
            start = interval[0], end = interval[1]; // 15,18
        }
    }

    // add the last interval
    mergedIntervals.push_back({ start, end }); // 1,6 8,10 15,18

    return mergedIntervals;
}

void testMergeIntervals() {
    vector<vector<int>> out1 = merge({ {1, 3}, {2, 5}, {7, 9} });
    vector<vector<int>> res1 = { {1, 5}, {7, 9} };
    assert(std::equal(out1.begin(), out1.end(), res1.begin()));

    vector<vector<int>> out2 = merge({ {6, 7}, {2, 4}, {5, 9} });
    vector<vector<int>> res2 = { {2, 4}, {5, 9} };
    assert(std::equal(out2.begin(), out2.end(), res2.begin()));

    vector<vector<int>> out3 = merge({ {1, 4}, {2, 6}, {3, 5} });
    vector<vector<int>> res3 = { {1, 6} };
    assert(std::equal(out3.begin(), out3.end(), res3.begin()));

    vector<vector<int>> out4 = merge({ {1, 3}, {2, 6}, {8, 10}, {15, 18} });
    vector<vector<int>> res4 = { {1, 6}, {8, 10}, {15, 18} };
    assert(std::equal(out4.begin(), out4.end(), res4.begin()));

    vector<vector<int>> out5 = merge({ {1, 4}, {4, 5} });
    vector<vector<int>> res5 = { {1, 5} };
    assert(std::equal(out5.begin(), out5.end(), res5.begin()));
}

int main() {

    testMergeIntervals();

    return 0;
}

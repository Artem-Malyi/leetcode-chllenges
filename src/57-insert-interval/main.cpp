// https://leetcode.com/problems/insert-interval/
// name of the problem

// Given a set of non - overlapping intervals, insert a new interval into the intervals(merge if necessary).
// You may assume that the intervals were initially sorted according to their start times.
//
// Example 1:
//    Input: intervals = [[1, 3], [6, 9]], newInterval = [2, 5]
//    Output : [[1, 5], [6, 9]]
// Example 2:
//    Input : intervals = [[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]], newInterval = [4, 8]
//    Output : [[1, 2], [3, 10], [12, 16]]
//    Explanation : Because the new interval[4, 8] overlaps with[3, 5], [6, 7], [8, 10].
// Example 3:
//    Input : intervals = [], newInterval = [5, 7]
//    Output : [[5, 7]]
// Example 4:
//    Input : intervals = [[1, 5]], newInterval = [2, 3]
//    Output : [[1, 5]]
// Example 5:
//    Input : intervals = [[1, 5]], newInterval = [2, 7]
//    Output : [[1, 7]]
// Constraints:
//    0 <= intervals.length <= 104
//    intervals[i].length == 2
//    0 <= intervals[i][0] <= intervals[i][1] <= 105
//    intervals is sorted by intervals[i][0] in ascending order.
//    newInterval.length == 2
//    0 <= newInterval[0] <= newInterval[1] <= 105

// Time:  O(n)
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

vector<vector<int>> insert(vector<vector<int>>&& intervals, vector<int> newInterval) {
    int i = 0;
    vector<vector<int>> merged;
    // skip and add the the output the intervals the end before newInterval starts
    while (i < intervals.size() && intervals[i][1] < newInterval[0]) { // 3 < 2
        merged.push_back(intervals[i++]);
    }

    // merge the overlapping intervals
    while (i < intervals.size() && intervals[i][0] <= newInterval[1]) { // 6 <= 5
        newInterval[0] = min(intervals[i][0], newInterval[0]); // min(1, 2) == 1
        newInterval[1] = max(intervals[i][1], newInterval[1]); // max(3, 5) == 5
        i++;
    }

    // add new interval to output
    merged.push_back(newInterval); // 1,5

    // add the remaining intervals to output, if any
    while (i < intervals.size()) {
        merged.push_back(intervals[i++]); // 1,5 6,9
    }

    return merged;
}

void testInsert() {
    vector<vector<int>> out1 = insert({ {1,2} }, { 0,5 });
    vector<vector<int>> res1 = { {0,5} };
    assert(std::equal(out1.begin(), out1.end(), res1.begin()));

    vector<vector<int>> out2 = insert({ {1,3}, {6,9} }, { 2,5 });
    vector<vector<int>> res2 = { {1,5}, {6,9} };
    assert(std::equal(out2.begin(), out2.end(), res2.begin()));

    vector<vector<int>> out3 = insert({ {1,2}, {3,5}, {6,7}, {8,10}, {12,16} }, { 4,8 });
    vector<vector<int>> res3 = { {1,2}, { 3,10 }, { 12,16 } };
    assert(std::equal(out3.begin(), out3.end(), res3.begin()));
}

int main() {

    testInsert();

    return 0;
}

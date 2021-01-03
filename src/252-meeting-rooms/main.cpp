// https://leetcode.com/problems/meeting-rooms/
// 252. Meeting Rooms

// Given an array of meeting time intervals where intervals[i] = [starti, endi], determine if a person could attend all meetings.
//
// Example 1:
//    Input: intervals = [[0, 30], [5, 10], [15, 20]]
//    Output : false
// Example 2:
//    Input : intervals = [[7, 10], [2, 4]]
//    Output : true
//
// Constraints:
//    0 <= intervals.length <= 104
//    intervals[i].length == 2
//    0 <= starti < endi <= 106

// Time:  O(nlogn)
// Space: O(1)
// Pattern: Merge intervals

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool canAttendMeetings(vector<vector<int>>&& intervals) { // 13,15 1,13
    sort(intervals.begin(), intervals.end(),
        [](vector<int> lhs, vector<int> rhs) { return lhs[0] < rhs[0]; });

    for (int i = 1; i < intervals.size(); i++) { // 1,13 13,15
        if (intervals[i][0] < intervals[i - 1][1])
            return false; // found overlapping interval
    }

    return true;
}

void testCanAttendMeetings() {
    assert(false == canAttendMeetings({ {0, 30}, {5, 10}, {15, 20} }));
    assert(true == canAttendMeetings({ {7, 10}, {2, 4}, {15, 20} }));
    assert(true == canAttendMeetings({ }));
}

int main() {

    testCanAttendMeetings();

    return 0;
}

// https://leetcode.com/problems/meeting-rooms-ii/
// 253. Meeting Rooms II

// Given an array of meeting time intervals consisting of startand end times [[s1, e1], [s2, e2], ...] (si < ei), 
// find the minimum number of conference rooms required.
//
// Example 1:
//    Input: [[0, 30], [5, 10], [15, 20]]
//    Output : 2
// Example 2:
//    Input : [[7, 10], [2, 4]]
//    Output : 1

// Time:  O(nlogn)
// Space: O(n)
// Pattern: Merge intervals

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct EndCompare {
    bool operator()(const vector<int>& lhs, const vector<int>& rhs) {
        // note that to get a min heap we need lhs to be bigger than rhs
        return lhs[1] > rhs[1];
    }
};

int minMeetingRooms(vector<vector<int>>&& intervals) {
    if (intervals.empty())
        return 0;
    // sort the meetings by start time
    sort(intervals.begin(), intervals.end(),
        [](const vector<int>& lhs, const vector<int>& rhs) { return lhs[0] < rhs[0]; });
    int numberOfRooms = 0;
    priority_queue<vector<int>, vector<vector<int>>, EndCompare> minHeap;
    for (const auto& interval : intervals) {
        // remove all meetings that have ended
        while (!minHeap.empty() && interval[0] >= minHeap.top()[1]) {
            minHeap.pop();
        }
        // add the current meeting to the minHeap, a.k.a. start the meeting
        minHeap.push(interval);
        // all the active meetings in the minHeap, so wee need rooms for all of them
        numberOfRooms = max(numberOfRooms, static_cast<int>(minHeap.size())); // 2
    }
    return numberOfRooms;
}

void testMinMeetingRooms() {
    assert(2 == minMeetingRooms({ {4, 5}, {2, 3}, {2, 4}, {3, 5} }));
    assert(2 == minMeetingRooms({ {1, 4}, {2, 5}, {7, 9} }));
    assert(1 == minMeetingRooms({ {6, 7}, {2, 4}, {8, 12} }));
    assert(2 == minMeetingRooms({ {1, 4}, {2, 3}, {3, 6} }));
    assert(2 == minMeetingRooms({ {4, 5}, {2, 3}, {2, 4}, {3, 5} }));
}

int main() {

    testMinMeetingRooms();

    return 0;
}

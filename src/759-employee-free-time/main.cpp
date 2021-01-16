// https://leetcode.com/problems/employee-free-time/
// 759. Employee Free Time

// We are given a list schedule of employees, which represents the working time for each employee.
// Each employee has a list of non - overlapping Intervals, and these intervals are in sorted order.
// Return the list of finite intervals representing common, positive - length free time for all employees, also in sorted order.
// (Even though we are representing Intervals in the form[x, y], the objects inside are Intervals, not lists or arrays.
// For example, schedule[0][0].start = 1, schedule[0][0].end = 2, and schedule[0][0][0] is not defined).
// Also, we wouldn't include intervals like [5, 5] in our answer, as they have zero length.
//
// Example 1:
//     Input: schedule = [[[1, 2], [5, 6]], [[1, 3]], [[4, 10]] ]
//     Output : [[3, 4]]
//     Explanation : There are a total of three employees, and all common
//     free time intervals would be[-inf, 1], [3, 4], [10, inf].
//     We discard any intervals that contain inf as they aren't finite.
// Example 2:
//    Input : schedule = [[[1, 3], [6, 7]], [[2, 4]], [[2, 5], [9, 12]] ]
//    Output : [[5, 6], [7, 9]]
// Constraints:
//    1 <= schedule.length, schedule[i].length <= 50
//    0 <= schedule[i].start < schedule[i].end <= 10 ^ 8

// Two solutions: O(nlogn) and O(nlogk), see below

// Time:  O(nlogn), O(nlogk), where n is the total number of intervals, and k is the number of employees
// Space: O(n), O(k)
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

class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }

    bool operator== (const Interval& other) {
        return start == other.start && end == other.end;
    }
};

// Time:  O(N*logN) time, where 'N' is the total number of intervals
// Space: O(N)
struct endCompare {
    bool operator() (const Interval& lhs, const Interval& rhs) {
        return lhs.end > rhs.end; // > for minHeap
    }
};

vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
    vector<Interval> all;
    for (const auto& emp : schedule) {
        for (const auto& i : emp) {
            all.push_back(i);
        }
    }

    sort(begin(all), end(all), [](const Interval& lhs, const Interval& rhs) { return lhs.start < rhs.start; });

    priority_queue<Interval, vector<Interval>, endCompare> minHeap;
    vector<Interval> res;
    for (auto i : all) {
        Interval tmp;
        bool tmpValid = false;
        // if current interval starts after the latest-of-all-met-before ends
        while (!minHeap.empty() && i.start > minHeap.top().end) {
            tmp = minHeap.top();
            tmpValid = true;
            minHeap.pop();
        }

        // if tmp was the latest valid interval, then we can note a gap between it and the current one
        if (minHeap.empty() && tmpValid) {
            res.push_back({ tmp.end, i.start });
        }

        minHeap.push(i);
    }

    return res;
}

// ----------------
// Time complexity:
// The below algorithm's time complexity is O(N* logK), where 'N' is the total number of intervals, 
// and 'K' is the total number of employees. This is because we are iterating through the intervals 
// only once (which will take O(N)), and every time we process an interval, we remove (and can insert) 
// one interval in the Min Heap, (which will take O(logK)). At any time, the heap will not have more than 'K' elements.
//
// Space complexity:
// The space complexity of the below algorithm will be O(K) as at any time, the heap will not have more than 'K' elements.
struct startCompare {
    bool operator()(const pair<Interval, pair<int, int>>& x, const pair<Interval, pair<int, int>>& y) {
        return x.first.start > y.first.start; // > for minHeap
    }
};

vector<Interval> employeeFreeTime2(vector<vector<Interval>> schedule) {
    vector<Interval> result;
    if (schedule.empty()) {
        return result;
    }

    // PriorityQueue to store one interval from each employee
    priority_queue<pair<Interval, pair<int, int>>, vector<pair<Interval, pair<int, int>>>, startCompare> minHeap;

    // insert the first interval of each employee to the queue
    for (int i = 0; i < schedule.size(); i++) {
        minHeap.push(make_pair(schedule[i][0], make_pair(i, 0)));
    }

    Interval previousInterval = minHeap.top().first;
    while (!minHeap.empty()) {
        auto queueTop = minHeap.top();
        minHeap.pop();
        // if previousInterval is not overlapping with the next interval, insert a free interval
        if (previousInterval.end < queueTop.first.start) {
            result.push_back({ previousInterval.end, queueTop.first.start });
            previousInterval = queueTop.first;
        }
        else {  // overlapping intervals, update the previousInterval if needed
            if (previousInterval.end < queueTop.first.end) {
                previousInterval = queueTop.first;
            }
        }

        // if there are more intervals available for the same employee, add their next interval
        vector<Interval> employeeSchedule = schedule[queueTop.second.first];
        if (employeeSchedule.size() > queueTop.second.second + 1) {
            minHeap.push(make_pair(employeeSchedule[queueTop.second.second + 1],
                make_pair(queueTop.second.first, queueTop.second.second + 1)));
        }
    }

    return result;
}

void testemployeeFreeTime() {
    vector<Interval> out1 = employeeFreeTime({ {{1,3},{5,6}}, {{2,3},{6,8}} });
    vector<Interval> exp1 = { {3,5} };
    assert(equal(exp1.begin(), exp1.end(), out1.begin()));

    vector<Interval> out2 = employeeFreeTime({ {{1,3},{9,12}}, {{2,4}}, {{6,8}} });
    vector<Interval> exp2 = { {4,6}, {8,9} };
    assert(equal(exp2.begin(), exp2.end(), out2.begin()));

    vector<Interval> out3 = employeeFreeTime({ {{1,3}}, {{2,4}}, {{3,5},{7,9}} });
    vector<Interval> exp3 = { {5,7} };
    assert(equal(exp3.begin(), exp3.end(), out3.begin()));

    vector<Interval> out4 = employeeFreeTime({ {{7,24},{29,33},{45,57},{66,69},{94,99}}, {{6,24},{43,49},{56,59},{61,75},{80,81}}, {{5,16},{18,26},{33,36},{39,57},{65,74}}, {{9,16},{27,35},{40,55},{68,71},{78,81}}, {{0,25},{29,31},{40,47},{57,87},{91,94}} });
    vector<Interval> exp4 = {{26, 27}, { 36,39}, {87,91}};
    assert(equal(exp4.begin(), exp4.end(), out4.begin()));
}

int main() {

    testemployeeFreeTime();

    return 0;
}

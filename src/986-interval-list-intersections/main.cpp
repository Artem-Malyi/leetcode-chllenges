// https://leetcode.com/problems/interval-list-intersections/
// 986. Interval List Intersections

// Given two lists of closed intervals, each list of intervals is pairwise disjointand in sorted order.
// Return the intersection of these two interval lists.
// (Formally, a closed interval[a, b](with a <= b) denotes the set of real numbers x with a <= x <= b.
// The intersection of two closed intervals is a set of real numbers that is either empty, or can be represented
// as a closed interval. 
// For example, the intersection of[1, 3] and [2, 4] is[2, 3].)
//
// Example 1:
//    Input: A = [[0, 2], [5, 10], [13, 23], [24, 25]], B = [[1, 5], [8, 12], [15, 24], [25, 26]]
//    Output : [[1, 2], [5, 5], [8, 10], [15, 23], [24, 24], [25, 25]]
// Note:
//    0 <= A.length < 1000
//    0 <= B.length < 1000
//    0 <= A[i].start, A[i].end, B[i].start, B[i].end < 10 ^ 9

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

vector<vector<int>> intervalIntersection(vector<vector<int>>&& A, vector<vector<int>>&& B) {
    vector<vector<int>> result;
    int i1 = 0, i2 = 0;
    while (i1 < A.size() && i2 < B.size()) {
        if (A[i1][0] > B[i2][1])
            i2++; // A[i1] is ahead with no intersection
        else if (B[i2][0] > A[i1][1])
            i1++; // B[i2] is ahead with no intersection
        else {
            // intersection, add the interval with minimal of both
            result.push_back({ max(A[i1][0], B[i2][0]), min(A[i1][1], B[i2][1]) });

            // select the next interval after the one, which has the smaller end value
            if (A[i1][1] < B[i2][1])
                i1++;
            else if (B[i2][1] < A[i1][1])
                i2++;
            else
                i1++, i2++;
        }
    }
    return result;
}

void testIntervalIntersection() {
    vector<vector<int>> out1 = intervalIntersection({ {0, 2}, {5, 10}, {13, 23}, {24, 25} }, { {1, 5}, {8, 12}, {15, 24}, {25, 26} });
    vector<vector<int>> res1 = { {1,2}, {5,5}, {8,10}, {15,23}, {24,24}, {25,25} };
    assert(equal(out1.begin(), out1.end(), res1.begin()));

    vector<vector<int>> out2 = intervalIntersection({ {0, 2}, {5, 10}, {13, 23}, {24, 25}, {34, 456} },
        { {1, 5}, {8, 12}, {15, 24}, {25, 26}, {34, 44}, {54, 64}, {74, 84}, {94, 104} });
    vector<vector<int>> res2 = { {1, 2}, {5, 5}, {8, 10}, {15, 23}, {24, 24}, {25, 25}, {34, 44}, {54, 64}, {74, 84}, {94, 104} };
    assert(equal(out2.begin(), out2.end(), res2.begin()));
}

int main() {

    testIntervalIntersection();

    return 0;
}

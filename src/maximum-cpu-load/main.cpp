// Didn't find it on LeetCode
// Maximum CPU Load

// We are given a list of Jobs. Each job has a Start time, an End time, and a CPU load when it is running. 
// Our goal is to find the maximum CPU load at any time if all the jobs are running on the same machine.

// Example 1:
//    Jobs: [[1, 4, 3], [2, 5, 4], [7, 9, 6]]
//    Output : 7
//    Explanation : Since[1, 4, 3] and [2, 5, 4] overlap, their maximum CPU load(3 + 4 = 7) will be when both the
//        jobs are running at the same time i.e., during the time interval(2, 4).
// Example 2:
//    Jobs : [[6, 7, 10], [2, 4, 11], [8, 12, 15]]
//    Output : 15
//    Explanation : None of the jobs overlap, therefore we will take the maximum load of any job which is 15.
// Example 3:
//    Jobs : [[1, 4, 2], [2, 4, 1], [3, 6, 5]]
//    Output : 8
//    Explanation : Maximum CPU load will be 8 as all jobs overlap during the time interval[3, 4].

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

class Job {
public:
    int start = 0;
    int end = 0;
    int cpuLoad = 0;

    Job(int start, int end, int cpuLoad) {
        this->start = start;
        this->end = end;
        this->cpuLoad = cpuLoad;
    }
};

class MaximumCPULoad {
public:
    struct endCompare {
        bool operator()(const Job& x, const Job& y) { return x.end > y.end; }
    };

    static int findMaxCPULoad(vector<Job>& jobs) {
        if (jobs.empty()) {
            return 0;
        }

        // sort the jobs by start time
        sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) { return a.start < b.start; });

        int maxCPULoad = 0;
        int currentCPULoad = 0;
        priority_queue<Job, vector<Job>, endCompare> minHeap;
        for (auto job : jobs) {
            // remove all jobs that have ended
            while (!minHeap.empty() && job.start > minHeap.top().end) {
                currentCPULoad -= minHeap.top().cpuLoad;
                minHeap.pop();
            }

            // add the current job into the minHeap
            minHeap.push(job);
            currentCPULoad += job.cpuLoad;
            maxCPULoad = max(maxCPULoad, currentCPULoad);
        }

        return maxCPULoad;
    }
};

int main() {
    vector<Job> input = { {1, 4, 3}, {7, 9, 6}, {2, 5, 4} };
    assert(7 == MaximumCPULoad::findMaxCPULoad(input));

    input = { {6, 7, 10}, {8, 12, 15}, {2, 4, 11} };
    assert(15 == MaximumCPULoad::findMaxCPULoad(input));

    input = { {1, 4, 2}, {3, 6, 5}, {2, 4, 1} };
    assert(8 == MaximumCPULoad::findMaxCPULoad(input));

    input = { {4, 5, 1}, {2, 3, 2}, {2, 4, 3}, {3, 5, 4} };
    assert(9 == MaximumCPULoad::findMaxCPULoad(input));

    return 0;
}

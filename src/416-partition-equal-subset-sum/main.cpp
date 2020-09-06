#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool canPartitionRecursive(vector<vector<int>>& dp, const vector<int>& num, int sum, int currentIndex) {
    // base check
    if (sum == 0)
        return true;

    if (num.empty() || currentIndex >= num.size())
        return false;

    // if we have not already processed a similar problem
    if (dp[currentIndex][sum] == -1) {
        // recursive call after choosing the number at the currentIndex
        // if the number at currentIndex exceeds the sum, we shouldn't process this
        if (num[currentIndex] <= sum) {
            if (canPartitionRecursive(dp, num, sum - num[currentIndex], currentIndex + 1)) {
                dp[currentIndex][sum] = 1;
                return true;
            }
        }

        // recursive call after excluding the number at the currentIndex
        dp[currentIndex][sum] = canPartitionRecursive(dp, num, sum, currentIndex + 1) ? 1 : 0;
    }

    return dp[currentIndex][sum] == 1 ? true : false;
}

bool canPartition(const vector<int>&& num) {
    int sum = 0;
    for (int i = 0; i < num.size(); i++)
        sum += num[i];

    // if 'sum' is a an odd number, we can't have two subsets with equal sum
    if (sum % 2 != 0)
        return false;

    vector<vector<int>> dp(num.size(), vector<int>(sum / 2 + 1, -1));

    return canPartitionRecursive(dp, num, sum / 2, 0);
}

void testCanPartition() {
    assert(true == canPartition({ 1, 5, 11, 5 }));
    assert(false == canPartition({ 1, 2, 3, 5 }));
}

int main() {

    testCanPartition();

	return 0;
}

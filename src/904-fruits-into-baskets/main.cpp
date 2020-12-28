// https://leetcode.com/problems/fruit-into-baskets/
// 904. Fruit Into Baskets

// In a row of trees, the i-th tree produces fruit with type tree[i].
//
// You start at any tree of your choice, then repeatedly perform the following steps :
//
// Add one piece of fruit from this tree to your baskets.If you cannot, stop.
// Move to the next tree to the right of the current tree.If there is no tree to the right, stop.
// Note that you do not have any choice after the initial choice of starting tree : you must perform step 1,
// then step 2, then back to step 1, then step 2, and so on until you stop.
//
// You have two baskets, and each basket can carry any quantity of fruit, but you want each basket to only carry one type of fruit each.
//
// What is the total amount of fruit you can collect with this procedure ?

// Time:  O(n)
// Space: O(n)
// Pattern: Sliding Window

#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int totalFruit(vector<int>& tree) { // O(n)
    int total = 0;
    int windowStart = 0;
    unordered_map<int, int> freq;
    for (int windowEnd = 0; windowEnd < tree.size(); ++windowEnd) {
        ++freq[tree[windowEnd]];  
        while (freq.size() > 2) { 
            --freq[tree[windowStart]];
            if (!freq[tree[windowStart]])
                freq.erase(tree[windowStart]);
            ++windowStart;
        }
        total = max(total, windowEnd - windowStart + 1);
    }
    return total;
}

void testTotalFruit() {
    vector<int> v1 = { 1, 2, 1 };
    assert(3 == totalFruit(v1));

    vector<int> v2 = { 0, 1, 2, 2 };
    assert(3 == totalFruit(v2));

    vector<int> v3 = { 1, 2, 3, 2, 2 };
    assert(4 == totalFruit(v3));

    vector<int> v4 = { 3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4 };
    assert(5 == totalFruit(v4));
}

int main() {

    testTotalFruit();

	return 0;
}
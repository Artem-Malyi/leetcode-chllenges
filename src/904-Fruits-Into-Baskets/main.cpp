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
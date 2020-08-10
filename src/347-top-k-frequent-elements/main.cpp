#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) { // O(n + 2k)
    map<int, int> freq;
    for (auto n : nums)
        ++freq[n]; // O(n)

    multimap<int, int, greater<int>> freqFirst; 
    for (auto n : freq)
        freqFirst.insert({ n.second, n.first }); // O(k)

    vector<int> res;
    for (auto n : freqFirst) { // O(k)
        if (k--)
            res.push_back(n.second);
        else
            break;
    }

    return res;
}

void testTopKFrequent() {
    vector<int> v = { 1, 1, 1, 2, 2, 3 };
    vector<int> r = { 1, 2 };
    assert(std::equal(r.begin(), r.end(), topKFrequent(v, 2).begin()));
}

int main() {

    testTopKFrequent();

	return 0;
}
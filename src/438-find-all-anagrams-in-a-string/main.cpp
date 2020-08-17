#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

                                  // windowStart: v
vector<int> findAnagrams(string s, string p) { // cbaebabacd, abc
    vector<int> anagramIndices;   // windowEnd:      ^
    unordered_map<char, int> patternFreq, freq;
    for (auto c : p)
        ++patternFreq[c]; // a:1, b:1, c:1
    int windowStart = 0;
    for (int windowEnd = 0; windowEnd < s.size(); ++windowEnd) { // 3
        char c = s[windowEnd]; // e
        ++freq[c]; // c:1, b:1, a:1
        while (freq[c] > patternFreq[c]) { // 1 > 1
            --freq[s[windowStart]];
            if (0 == freq[s[windowStart]])
                freq.erase(s[windowStart]);
            ++windowStart;
        }
        if (freq.size() == patternFreq.size() && windowEnd - windowStart + 1 == p.size()) // 3 == 3 && 3 == 3
            anagramIndices.push_back(windowStart); // 0
    }
    return anagramIndices;
}

void testFindAnagrams() {
    vector<int> ans1 = {0, 6};
    assert(ans1 == findAnagrams("cbaebabacd", "abc"));
    vector<int> ans2 = {0, 1, 2};
    assert(ans2 == findAnagrams("abab", "ab"));
    vector<int> ans3 = {26};
    assert(ans3 == findAnagrams("asldkjfhalksjdhfkajshdlfkjahslkdjfhalkjshdf", "hslk"));
}

int main() {

    testFindAnagrams();

    return 0;
}

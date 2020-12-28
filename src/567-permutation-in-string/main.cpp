// https://leetcode.com/problems/permutation-in-string/
// 567. Permutation in String

// Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1.
// In other words, one of the first string's permutations is the substring of the second string.

// Time:  O(n)
// Space: O(n)
// Pattern: Sliding Window

#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
                               // windowStart:                v
bool checkInclusion(string s1, string s2) { // hello, ooolleooolehl -> true
                                 // windowEnd:                    ^
    unordered_map<char, int> freq;
    for (auto c : s1)
        ++freq[c]; // [h:0, e:0, l:0, o:0]

    int windowStart = 0, matched = 0;
    for (int windowEnd = 0; windowEnd < s2.length(); ++windowEnd) { // 12
        char rightChar = s2[windowEnd]; // l
        if (freq.find(rightChar) != freq.end()) {
            --freq[rightChar];
            if (freq[rightChar] == 0)
                ++matched; // 4
        }

        if (matched == freq.size()) // 4 == 4
            return true;

        if (windowEnd >= s1.length() - 1) { // shrink the window by 1 char each step // 11 >= 4
            char leftChar = s2[windowStart]; // o
            if (freq.find(leftChar) != freq.end()) {
                if (freq[leftChar] == 0)
                    --matched;
                ++freq[leftChar];
            }
            ++windowStart; // 8
        }
    }

    return false;
}

void testCheckInclusion() {
    assert(true == checkInclusion("ab", "eidbaooo"));
    assert(false == checkInclusion("hello", "ooolleoooleh"));
    assert(true == checkInclusion("hello", "ooolleooolehl"));
}

int main() {

    testCheckInclusion();

	return 0;
}

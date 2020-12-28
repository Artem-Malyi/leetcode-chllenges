// https://leetcode.com/problems/minimum-window-substring/
// 76. Minimum Window Substring

// Given two strings s and t, return the minimum window in s which will contain all the characters in t. 
// If there is no such window in s that covers all characters in t, return the empty string "".
//
// Note that If there is such a window, it is guaranteed that there will always be only one unique minimum window in s.

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

#pragma warning(disable: 4267)

string minWindow(string s, string t) {
    // windowStart:          v
    //              adobecodebanc , abc -> banc
    // windowEnd:                ^

    unordered_map<char, int> freq;
    for (auto c : t)
        ++freq[c]; // a:0, b:1, c:0

    int windowStart = 0, matched = 0, minLength = s.size() + 1, subStrStart = 0;
    // try to extend the range [windowStart, windowEnd]
    for (int windowEnd = 0; windowEnd < s.size(); windowEnd++) { // 13
        char rightChar = s[windowEnd]; // c
        if (freq.find(rightChar) != freq.end()) { // true
            --freq[rightChar];
            if (freq[rightChar] >= 0) // count every matching of a character
                ++matched; // 2
        }

        // shrink the window if we can, finish as soon as we remove a matched character
        while (matched == t.size()) { // 2 == 3
            if (minLength > windowEnd - windowStart + 1) { // 5 > 4
                minLength = windowEnd - windowStart + 1; // 4
                subStrStart = windowStart; // 9
            }

            char leftChar = s[windowStart++]; // b, 10
            if (freq.find(leftChar) != freq.end()) { // false
                // note that we could have redundant matching characters, therefore we'll decrement the
                // matched count only when a useful occurrence of a matched character is going out of the
                // window
                if (freq[leftChar] == 0) { // 0 == 0
                    matched--; // 2
                }
                freq[leftChar]++; // b:1
            }
        }
    }

    return minLength > s.size() ? "" : s.substr(subStrStart, minLength); // banc
}

void testMinWindow() {
    assert("banc" == minWindow("adobecodebanc", "abc"));
    assert("" == minWindow("alskjdfhalksjdhfalkjshdlfkjahsdf", "xcvb"));
}

int main() {

    testMinWindow();

	return 0;
}

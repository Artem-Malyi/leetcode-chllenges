// https://leetcode.com/problems/longest-palindromic-substring/
// 5. Longest Palindromic Substring

// Given a string s, return the longest palindromic substring in s.
//
// Example 1:
//   Input: s = "babad"
//   Output : "bab"
//   Note : "aba" is also a valid answer.
// Example 2:
//   Input : s = "cbbd"
//   Output : "bb"
// Example 3:
//   Input : s = "a"
//   Output : "a"
// Example 4:
//   Input : s = "ac"
//   Output : "a"
// Constraints:
//    1 <= s.length <= 1000
//    s consist of only digits and English letters(lower - caseand /or upper - case)

// Time:
// Space:
// Pattern:

#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string longestPalindrome(string&& s) {
    int maxLength = 0;
    int n = s.length();

    string p;
    // handle substrings with odd number of characters
    for (int mid = 0; mid < n; mid++) {
        for (int x = 0; mid - x >= 0 && mid + x < n; x++) {
            if (s[mid - x] != s[mid + x])
                break;
            int length = 2 * x + 1; // if odd
            if (length > maxLength) {
                maxLength = length;
                p = s.substr(mid - x, length);
            }
        }
    }                                                     // mid:  v
    // handle substrings with even number of characters, like in "abba"
    for (int mid = 0; mid < n - 1; mid++) { // 1
        for (int x = 1; mid - x + 1 >= 0 && mid + x < n; x++) { // 1 >= 0 && 2 < 4
            if (s[mid - x + 1] != s[mid + x]) // s[1] != s[2]
                break;
            int length = 2 * x;
            if (length > maxLength) {
                maxLength = length;
                p = s.substr(mid - x + 1, length);
            }
        }
    }
    return p;
}

void testLongestPalindrome() {
    assert("abba" == longestPalindrome("abba"));
    assert("fffffddddddfffff" == longestPalindrome("asdfxfffffddddddfffffcvsh"));
    assert("bab" == longestPalindrome("babad"));
    assert("bb" == longestPalindrome("cbbd"));
}

int main() {

    testLongestPalindrome();

    return 0;
}

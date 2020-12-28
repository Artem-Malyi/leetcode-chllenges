// https://leetcode.com/problems/longest-substring-without-repeating-characters/
// 3. Longest Substring Without Repeating Characters

// Given a string s, find the length of the longest substring without repeating characters.

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

int lengthOfLongestSubstring(string s) {
    int maxLength = 0, windowStart = 0;
    unordered_map<char, int> freq;
    for (int windowEnd = 0; windowEnd < s.size(); ++windowEnd) {
        ++freq[s[windowEnd]];
        while (freq[s[windowEnd]] > 1) {
            --freq[s[windowStart]];
            if (0 == freq[s[windowStart]])
                freq.erase(freq[s[windowStart]]);
            ++windowStart;
        }
        maxLength = max(maxLength, windowEnd - windowStart + 1);
    }
    return maxLength;
}

void testLengthOfLongestSubstring() {
    assert(3 == lengthOfLongestSubstring("abcabcbb"));
    assert(1 == lengthOfLongestSubstring("bbbbb"));
    assert(3 == lengthOfLongestSubstring("pwwkew"));
    assert(10 == lengthOfLongestSubstring("zxlkcvjhslkrhgoshufglaish dflkajhsdlkfjhalskjdhflakjshdf"));
}

int main() {

    testLengthOfLongestSubstring();

	return 0;
}
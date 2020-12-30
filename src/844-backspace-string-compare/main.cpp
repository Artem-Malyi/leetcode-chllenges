// https://leetcode.com/problems/backspace-string-compare/
// 844. Backspace String Compare

// Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.
// Note that after backspacing an empty text, the text will continue empty.
//
// Example 1:
//   Input: S = "ab#c", T = "ad#c"
//   Output : true
//   Explanation : Both S and T become "ac".
// Example 2:
//   Input : S = "ab##", T = "c#d#"
//   Output : true
//   Explanation : Both S and T become "".
// Example 3:
//   Input : S = "a##c", T = "#a#c"
//   Output : true
//   Explanation : Both S and T become "c".
// Example 4:
//   Input : S = "a#c", T = "b"
//   Output : false
//   Explanation : S becomes "c" while T becomes "b".
// Note:
//   1 <= S.length <= 200
//   1 <= T.length <= 200
//   S and T only contain lowercase letters and '#' characters.
// Follow up:
//   Can you solve it in O(N) time and O(1) space ?

// Time:  O(n)
// Space: O(1)
// Pattern: Two pointers

#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int getNextIndex(const string& str, int index);

bool backspaceCompare(string S, string T) {
    int index1 = S.size() - 1, index2 = T.size() - 1;

    while (index1 >= 0 || index2 >= 0) {  //v
        int i1 = getNextIndex(S, index1); // ab## -1
        int i2 = getNextIndex(T, index2); // c#d# -1
                                          //^
        if (i1 < 0 && i2 < 0) // reached the end of both strings
            return true;

        if (i1 < 0 || i2 < 0) // reached the end of one of the strings
            return false;

        if (S[i1] != T[i2]) // check if characters are equal
            return false;

        index1 = i1 - 1;
        index2 = i2 - 1;
    }

    return true; // will never reach here
}

int getNextIndex(const string& str, int index) { // c#d#, -1
    int backspacesCount = 0;
    while (index >= 0) {
        if (str[index] == '#')
            backspacesCount++; // 0
        else if (backspacesCount > 0)
            backspacesCount--;
        else
            break;
        index--;
    }
    return index;
}

void testBackspaceCompare() {
    assert(true == backspaceCompare("abc", "abc"));
    assert(true == backspaceCompare("ab##", "a#c#"));
    assert(true == backspaceCompare("a##c", "#a#c"));
    assert(true == backspaceCompare("##", "###"));
    assert(false == backspaceCompare("a#c", "b"));
}

int main() {

    testBackspaceCompare();

    return 0;
}

// https://leetcode.com/problems/happy-number/
// 202. Happy Number

// Write an algorithm to determine if a number n is happy.
// A happy number is a number defined by the following process :
// Starting with any positive integer, replace the number by the sum of the squares of its digits.
// Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
// Those numbers for which this process ends in 1 are happy.
// Return true if n is a happy number, and false if not.

// Example 1:
//
// Input: n = 19
// Output : true
// Explanation :
//    12 + 92 = 82
//    82 + 22 = 68
//    62 + 82 = 100
//    12 + 02 + 02 = 1

// Time:  
// Space: O(1)
// Pattern: Fast & Slow pointers

#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int findSquareSum(int num);

bool isHappy(int num) {
    int slow = num, fast = num;
    do {
        slow = findSquareSum(slow);                 // move one step
        fast = findSquareSum(findSquareSum(fast));  // move two steps
    } while (slow != fast);                         // found the cycle

    return slow == 1;  // see if the cycle is stuck on the number '1'
}

int findSquareSum(int num) {
    int sum = 0;
    while (num > 0) {
        int digit = num % 10;
        sum += digit * digit;
        num /= 10;
    }
    return sum;
}

void testIsHappy() {
    assert(true == isHappy(23));
    assert(false == isHappy(12));
    assert(false == isHappy(2147483647));
    assert(false == isHappy(0));
    assert(true == isHappy(1));
}

int main() {

    testIsHappy();

    return 0;
}

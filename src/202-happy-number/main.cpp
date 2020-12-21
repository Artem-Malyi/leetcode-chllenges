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

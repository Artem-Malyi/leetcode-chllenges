// https://leetcode.com/problems/powx-n/
// 50. Pow(x, n)

// Implement pow(x, n), which calculates x raised to the power n (i.e. x^n).
//
// Example 1:
//   Input: x = 2.00000, n = 10
//   Output : 1024.00000
// Example 2:
//   Input : x = 2.10000, n = 3
//   Output : 9.26100
// Example 3:
//   Input : x = 2.00000, n = -2
//   Output : 0.25000
//   Explanation : 2 - 2 = 1 / 22 = 1 / 4 = 0.25
// Constraints:
//    -100.0 < x < 100.0
//    - 231 <= n <= 231 - 1
//    - 104 <= xn <= 104

// Time:
// Space:
// Pattern:

#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//          / x ^ n/2 * x ^ n/2 if n is even
// x ^ n = <  x * x ^ n-1 if n is odd
//          | 1 if n = 0

double myPowInternal(double x, int n) { // 2 -2
    if (n == 0)
        return 1;
    else if (n % 2 == 0) {
        double y = myPowInternal(x, n / 2); // 2 -1, 
        return y * y;
    }
    else
        return x * myPowInternal(x, n - 1);
}

double myPow(double x, int n) {
    int m = abs(n);
    // abs() for INT_MIN performs neg 0x80000000, which overflows with carry flag 
    // and the result is again the same negative value, so this edge case needs the fix:
    // additionally, absolute value of INT_MIN is 1 bigger than INT_MAX
    if (n == INT_MIN) { 
        m = -m;
        m -= 1;
    }

    double res = myPowInternal(x, m);

    if (n == INT_MIN && res < 0)
        res = -res;

    return n < 0 ? 1 / res : res;
}

void testMyPow() {
    assert(8 == myPow(2, 3));
    assert(0 == myPow(2.00000, -2147483648));
    assert(0 == myPow(-22.00000, -2147483648)); // INT_MIN
    assert(0 == myPow(-22.00000, -2147483647));
    assert(std::isinf(myPow(-22.00000, 2147483647))); // INT_MAX
    assert(std::isinf(myPow(15.00000, 2147483647)));
}

int main() {

    testMyPow();

    return 0;
}
#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

                                        // lo:       v
vector<int> sortedSquares(vector<int>&& A) { //-4,-1, 0, 3,10 -> 0, 1, 9, 16, 100
    int lo = 0;                         // hi:       ^
    int hi = A.size() - 1;
    int highestIndex = hi;
    vector<int> res(A.size());              // 0, 1, 9,16,100
    while (lo <= hi) {         // highestIndex:   ^
        int squareLo = A[lo] * A[lo]; // 1
        int squareHi = A[hi] * A[hi]; // 0
        if (squareLo <= squareHi) { // 1 <= 0
            res[highestIndex--] = squareHi;
            hi--;
        }
        else {
            res[highestIndex--] = squareLo; // 1
            lo++;
        }
    }
    return res;
}

void testSortedSquares() {
    vector<int> v1 = { 0, 1, 9, 16, 100 };
    vector<int> res1 = sortedSquares({ -4, -1, 0, 3, 10 });
    assert(v1 == res1);

    vector<int> v2 = { 4, 9, 9, 49, 121 };
    vector<int> res2 = sortedSquares({ -7, -3, 2, 3, 11 });
    assert(v2 == res2);
}

int main() {

    testSortedSquares();

	return 0;
}

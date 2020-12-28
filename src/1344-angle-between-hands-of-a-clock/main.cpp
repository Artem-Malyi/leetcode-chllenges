// https://leetcode.com/problems/angle-between-hands-of-a-clock/
// 1344. Angle Between Hands of a Clock

// Given two numbers, hourand minutes.Return the smaller angle(in degrees) formed between the hourand the minute hand.

#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

double angleClock(int hour, int minutes) {
    // 1 minute: 360 / 60 = 6 degrees
    // 1 hour: 360 / 12 = 30 degrees
    // hour-related 1 minute: 30 / 60 = 0.5 degrees

    double hourOffset = minutes * 0.5;
    double startPoint = (hour % 12) * 30 + hourOffset;
    double endPoint = minutes * 6;
    double result = 360 - abs(endPoint - startPoint);
    return min(360 - result, result);
}

void testAngleClock() {
    assert(165 == angleClock(12, 30));
    assert(75 == angleClock(3, 30));
    assert(7.5 == angleClock(3, 15));
    assert(155 == angleClock(4, 50));
    assert(0 == angleClock(12, 0));
}

int main() {

    testAngleClock();

    return 0;
}
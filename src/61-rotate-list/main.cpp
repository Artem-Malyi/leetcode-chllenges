// https://leetcode.com/problems/rotate-list/
// 61. Rotate List

// Given the head of a linked list, rotate the list to the right by k places.
//
// Example 1:
//     Input:  [1, 2, 3, 4, 5], k = 2
//     Output: [4, 5, 1, 2, 3]
// Example 2: 
//     Input:  [1, 2, 3, 4, 5], k = 8
//     Output: [3, 4, 5, 1, 2]
// Example 3: 
//     Input:  [1, 2, 3, 4, 5, 6], k = 3
//     Output: [4, 5, 6, 1, 2, 3]
// Example 4: 
//     Input:  [0, 1, 2], k = 4
//     Output: [2, 0, 1]

// Time:  O(n)
// Space: O(1)
// Pattern: In-place reversal of a linked list

#include <Windows.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

ListNode* rotateRight(ListNode* head, int k) {
    if (!head || k < 1)
        return head;

    // find the last node and list length
    ListNode* lastNode = head;
    int listLength = 1;
    while (lastNode->next) {
        ++listLength;
        lastNode = lastNode->next;
    }

    lastNode->next = head; // connect last node with the head to make it a circular list
    k = k % listLength; // no need to do rotations more than the length of the list
    int skipLength = listLength - k;
    ListNode* lastNodeOfRotatedList = head;
    for (int i = 0; i < skipLength - 1; i++)
        lastNodeOfRotatedList = lastNodeOfRotatedList->next;

    // 'lastNodeOfRotatedList.next' is pointing to the sub-list of 'k' ending nodes
    head = lastNodeOfRotatedList->next;
    lastNodeOfRotatedList->next = nullptr;
    return head;
}

string toString(ListNode* n) {
    string s;
    while (n) {
        s.append(to_string(n->val));
        n = n->next;
    }
    return s;
}

void testReverseRight() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    assert("12345" == toString(head = rotateRight(head, 0)));

    assert("45123" == toString(head = rotateRight(head, 2)));
    assert("12345" == toString(head = rotateRight(head, 3)));

    assert("34512" == toString(head = rotateRight(head, 8)));
    assert("12345" == toString(head = rotateRight(head, 2)));

    head->next->next->next->next->next = new ListNode(6);
    assert("456123" == toString(head = rotateRight(head, 3)));
    assert("123456" == toString(head = rotateRight(head, 3)));

    head->val = 0;
    head->next->val = 1;
    head->next->next->val = 2;
    head->next->next->next = nullptr;
    assert("120" == toString(head = rotateRight(head, 125)));
    assert("012" == toString(head = rotateRight(head, 1)));
}

int main() {

    testReverseRight();

    return 0;
}

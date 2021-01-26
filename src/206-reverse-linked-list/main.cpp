// https://leetcode.com/problems/reverse-linked-list/
// 206. Reverse Linked List

// Reverse a singly linked list.
// Example:
//    Input: 1->2->3->4->5->NULL
//    Output : 5->4->3->2->1->NULL
// Follow up:
//    A linked list can be reversed either iteratively or recursively. Could you implement both ?

// Time:  O(n)
// Space: O(1)
// Pattern: Reversal of a linked list

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
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* reverseList(ListNode* head) {
    if (!head || !head->next)              // head:           v
        return head;                       //       3 -> 2 -> 5 -> 7 -> x
    ListNode* n = reverseList(head->next); // n:                   ^
    head->next->next = head;
    head->next = nullptr;
    return n;
}

ListNode* reverseList2(ListNode* head) {
    ListNode* previous = nullptr;
    ListNode* current = head;
    while (current) {
        ListNode* tmp = current->next; // remember the pointer to the next node
        current->next = previous; // redirect the current node's link to the previous node
        previous = current; // update previous
        current = tmp; // update current
    }
    return previous;
}

string toString(ListNode* n) {
    string s;
    while (n) {
        s.append(to_string(n->val));
        n = n->next;
    }
    return s;
}

void testReverseList() {
    // iterative approach
    assert("" == toString(reverseList(nullptr)));

    ListNode* head = new ListNode(1);
    assert("1" == toString(reverseList(head)));

    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    assert("54321" == toString(reverseList(head)));

    // recursive approach
    assert("" == toString(reverseList2(nullptr)));

    ListNode* head2 = new ListNode(7);
    assert("7" == toString(reverseList2(head2)));

    head2->next = new ListNode(8);
    head2->next->next = new ListNode(9);
    head2->next->next->next = new ListNode(10);
    head2->next->next->next->next = new ListNode(11);
    assert("1110987" == toString(reverseList2(head2)));
}

int main() {

    testReverseList();

    return 0;
}

// Didn't find on LeetCode
// Reverse Every K-length Sub-list

// Given the head of a LinkedListand a number 'k', reverse every 'k' sized sub-list starting from the head.
// If, in the end, you are left with a sub-list with less than 'k' elements, reverse it too.
//
// Example:
//    Input:  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> x, 3
//    Output: 3 -> 2 -> 1 -> 6 -> 5 -> 4 -> 8 -> 7 -> x
//            \____k____/    \____k____/    \__<k__

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
    ListNode(int v): val(v), next(nullptr) {}
};

// head:                          v
// lastInSublist:                                     v
// lastInFirstPart:                                   v
// prev:                                                   v
// curr:                                                        v
// temp:                                                        v
//                                      /------------------v
// in:             x    1 <- 2 <- 3    4 <- 5 <- 6    7 <- 8    x, 3
//                       \_______________________^    |
//                                                    \_________^
// out:                 3 -> 2 -> 1 -> 6 -> 5 -> 4 -> 8 -> 7 -> x
ListNode* reverse(ListNode* head, int k) {
    if (k <= 1 || head == nullptr)
        return head;

    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        // remember the current and previous node in the k-length sublist
        // first part -> sublist to reverse -> last part
        ListNode* lastInFirstPart = prev;
        ListNode* lastInSublist = curr;
        // reverse k-1 links in-place
        for (int i = 0; i < k && curr; i++) { // 2 < 3 && nullptr
            ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        // connect remembered previous node with the k - 1-th node
        if (lastInFirstPart)
            lastInFirstPart->next = prev;
        else
            head = prev;
        // connect remembered current node with the k-th node
        lastInSublist->next = curr;
        // prepare for the next sub-list
        prev = lastInSublist;
    }
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

void testReverse() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);
    head->next->next->next->next->next->next = new ListNode(7);
    head->next->next->next->next->next->next->next = new ListNode(8);

    assert("12345678" == toString(head = reverse(head, 0)));

    assert("32165487" == toString(head = reverse(head, 3)));
    assert("12345678" == toString(head = reverse(head, 3)));

    assert("21436587" == toString(head = reverse(head, 2)));
    assert("12345678" == toString(head = reverse(head, 2)));

    assert("76543218" == toString(head = reverse(head, 7)));
    assert("12345678" == toString(head = reverse(head, 7)));

    assert("87654321" == toString(head = reverse(head, 15)));
    assert("12345678" == toString(head = reverse(head, 15)));
}

int main() {

    testReverse();

    return 0;
}

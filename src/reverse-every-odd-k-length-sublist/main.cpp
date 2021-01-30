// Didn't find on LeetCode
// Reverse Every Odd K-length Sub-list

// Given the head of a LinkedListand a number 'k', reverse every alternating 'k' sized sub-list starting from the head.
// If, in the end, you are left with a sub-list with less than 'k' elements, reverse it too.

// Example:
//    Input:  1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> x, 2
//    Output: 2 -> 1 -> 3 -> 4 -> 6 -> 5 -> 7 -> 8 -> x
//            \_k__/    \_k__/    \_k__/    \_k__/

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

// head:                              v
// lastInFirst:                                      v
// lastInSublist:                                              v
// prev:                                                            v
// curr:                                                                 v
// temp:                                                       
//                                               /--------v 
// input:                   x    1 <- 2    3 -> 4    5 <- 6    7 -> 8 -> x, 2
//                                \________^          \________^     
//                                            
// output:                       2 -> 1 -> 3 -> 4 -> 6 -> 5 -> 7 -> 8 -> x
ListNode* reverse(ListNode* head, int k) {
    if (!head || k <= 1)
        return head;
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        // remember previous pointer and current pointer to connect them later with the next sublist
        ListNode* lastInFirst = prev;
        ListNode* lastInSublist = curr;

        // reverse 'k' nodes
        for (int i = 0; i < k && curr; i++) { // 2 < 2
            ListNode* temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }

        // connect the remembered previous node to the k - 1-th node
        if (lastInFirst)
            lastInFirst->next = prev;
        else
            head = prev; // this means we are changing the first node (head) of the LinkedList
        lastInSublist->next = curr; // connect the remembered current node to the  k-th node

        // skip 'k' nodes
        for (int i = 0; i < k && curr; i++) {
            prev = curr;
            curr = curr->next;
        }
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

    assert("32145687" == toString(head = reverse(head, 3)));
    assert("12345678" == toString(head = reverse(head, 3)));

    assert("21346578" == toString(head = reverse(head, 2)));
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

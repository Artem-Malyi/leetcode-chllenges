// https://leetcode.com/problems/reverse-linked-list-ii/
// 92. Reverse Linked List II

// Reverse a linked list from position m to n. Do it in one-pass.
// Note: 1 <= m <= n <= length of list.
//
// Example :
//    Input : 1->2->3->4->5->NULL, m = 2, n = 4
//    Output : 1->4->3->2->5->NULL

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

// lastNodeOfSublist:      v  
// lastNodeOfFirst:   v
// prev:                                       v 
// curr:                                            v
// temp:                                            v
//                          
//                    x <- 1 <- 2 <- 3 <- 4 <- 5    x, 0, 4 ---> 5 -> 4 -> 3 -> 2 -> 1 -> x
// head:                                       ^             
ListNode* reverseBetween(ListNode* head, int m, int n) { // 1 2 3 4 5, 2,4 ---> 1 4 3 2 5
    // 1. skip m-1 nodes
    ListNode* prev = nullptr;
    ListNode* curr = head;
    for (int i = 0; i < m - 1 && curr; i++) {
        prev = curr;
        curr = curr->next;
    }

    // 2. remember m - 1-th and m-th nodes
    // (first part -> reversed sublist -> last part)
    ListNode* lastInFirst = prev; // m-1-th node - it will be connected later with the head of reversed sublist
    ListNode* lastInSublist = curr; // m-th node - it will becode the last in reversed sublist, 

    // 3. reverse the sublist between n - m + 1 nodes
    for (int i = 0; i < n - m + 1 && curr; i++) {
        ListNode* temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }

    // 4. connect m-1-th node to the head of reversed list
    if (!lastInFirst)
        head = prev;
    else
        lastInFirst->next = prev;

    lastInSublist->next = curr; // connect m-th node with the rest of the list

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

void testReverseBetween() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    assert("12345" == toString(head = reverseBetween(head, 0, 0)));

    assert("14325" == toString(head = reverseBetween(head, 2, 4)));
    assert("12345" == toString(head = reverseBetween(head, 2, 4)));

    assert("54321" == toString(head = reverseBetween(head, 0, 4)));
    assert("12345" == toString(head = reverseBetween(head, 0, 4)));

    assert("21345" == toString(head = reverseBetween(head, 0, 1)));
}

int main() {

    testReverseBetween();

    return 0;
}

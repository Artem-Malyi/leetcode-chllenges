#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* detectCycleStart(ListNode* head) {
    // 1. detect the cycle if any
    ListNode* slow = head;
    ListNode* fast = head;
    bool found = false;
    while (slow && fast) {
        fast = fast && fast->next ? fast->next->next : nullptr;
        slow = slow->next;
        if (slow == fast && slow) {
            found = true;
            break;
        }
    }
    if (!found)
        return nullptr;

    // 2. find the cycle length
    ListNode* it = slow->next;
    int cycleLength = 1;
    while (slow != it) {
        cycleLength++;
        it = it->next;
    }

    // 3. search for first node of the cycle
    slow = head;
    fast = head;
    while (cycleLength--) {
        fast = fast->next;
    }

    ListNode* prev = head;
    while (!(prev && prev == fast)) {
        slow = slow->next;
        fast = fast->next;
        prev = slow;
    }

    return prev;
}

void testDetectCycleStart() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = new ListNode(6);

    //       v-----------\
    // 1->2->3->4->-5->6-/
    head->next->next->next->next->next = head->next->next;
    assert(3 == detectCycleStart(head)->val);

    //          v--------\
    // 1->2->3->4->-5->6-/
    head->next->next->next->next->next = head->next->next->next;
    assert(4 == detectCycleStart(head)->val);

    // v-----------------\
    // 1->2->3->4->-5->6-/
    head->next->next->next->next->next = head;
    assert(1 == detectCycleStart(head)->val);
}

int main() {

    testDetectCycleStart();

    return 0;
}

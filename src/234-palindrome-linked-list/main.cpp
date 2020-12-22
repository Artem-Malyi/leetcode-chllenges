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
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* reverseList(ListNode* head);


// Time:  O(n)
// Space: O(1)

                              // slow:                v
bool isPalindrome(ListNode* head) { // 1 -> 2 -> 4 -> 6 -> 4 -> 2 -> 1 -> nullptr
    if (!head || !head->next) // fast:                               ^
        return true; // empty or single node list is a palindrome

      // 1. find the middle node
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 2. reverse the second half of the list
    ListNode* headSecondHalf = reverseList(slow); // 1 -> 2 -> 4 -> 6
    ListNode* copyHeadSecondHalf = headSecondHalf;

    // 3. compare the sub-lists
    while (head && headSecondHalf) {
        if (head->val != headSecondHalf->val)
            break; // not a palindrome, break now and either slow or headSecondHalf will remain non-null
        head = head->next;
        headSecondHalf = headSecondHalf->next;
    }

    // 4. reverse the second half-list back
    reverseList(copyHeadSecondHalf);
    if (!slow || !headSecondHalf) // we're reached the list end during comparison
        return true;

    return false;
}

ListNode* reverseList(ListNode* head) { // 6 -> 4 -> 2 -> 1 -> nullptr
    ListNode* prev = nullptr;
    while (head) {
        ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

void testIsPalindrome() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(2);
    head->next->next->next->next = new ListNode(1);
    assert(true == isPalindrome(head)); // 1 2 3 2 1

    ListNode* tmpNode = head->next->next->next;
    head->next->next->next = new ListNode(3);
    head->next->next->next->next = tmpNode;
    assert(true == isPalindrome(head)); // 1 2 3 3 2 1

    head->next->next->next->next->next->next = new ListNode(5);
    assert(false == isPalindrome(head));

    assert(true == isPalindrome(nullptr));

    ListNode* newList = new ListNode(10);
    assert(true == isPalindrome(newList));
}

int main() {

    testIsPalindrome();

    return 0;
}

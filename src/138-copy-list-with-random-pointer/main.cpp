#include <Windows.h>

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

Node* copyRandomList(Node* head) {
    unordered_map<Node*, Node*> orig2new;

    Node* it1 = head;
    while (it1) {
        Node* it2 = new Node(it1->val);
        orig2new[it1] = it2;
        it1 = it1->next;
    }

    it1 = head;
    while (it1) {
        orig2new[it1]->next = orig2new[it1->next];
        orig2new[it1]->random = orig2new[it1->random];
        it1 = it1->next;
    }

    return orig2new[head];
}

void testCopyRandomList() {
    // [[7,null],[13,0],[11,4],[10,2],[1,0]]
    Node* n0 = new Node(7);
    Node* n1 = new Node(13);
    n0->next = n1;
    Node* n2 = new Node(11);
    n1->next = n2;
    Node* n3 = new Node(10);
    n2->next = n3;
    Node* n4 = new Node(1);
    n3->next = n4;

    n1->random = n0;
    n2->random = n4;
    n3->random = n2;
    n4->random = n0;

    Node* l0 = copyRandomList(n0);

    Node* l1 = l0->next;
    Node* l2 = l1->next;
    Node* l3 = l2->next;
    Node* l4 = l3->next;

    assert(l0->val == n0->val && l1->val == n1->val && l2->val == n2->val && l3->val == n3->val && l4->val == n4->val &&
        l1->random->val == n1->random->val && l2->random->val == n2->random->val &&
        l3->random->val == n3->random->val && l4->random->val == n4->random->val);
}

int main() {

    testCopyRandomList();

	return 0;
}

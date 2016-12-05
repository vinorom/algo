/**
 * Problem:
 *      Cracking the Coding Interview: Linked Lists: Detect a Cycle
 *
 * Links:
 *      https://www.hackerrank.com/challenges/ctci-linked-list-cycle
 */

#include <bits/stdc++.h>

struct Node
{
    int data;
    Node* next;
};

bool has_cycle(Node* head)
{
    auto* slow = head;
    auto* fast = head;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

int main()
{
    return 0;
}


#include "ListNode.h"
#include <iostream>


// Constructor (don't change this)
ListNode::ListNode(int x) : val(x), next(nullptr) {}

ListNode* reverseList(ListNode* head) {
    // YOUR CODE GOES HERE
    // HINT: You may want to use three pointers for this problem: prev, curr, and next
    ListNode* curr = head;
    ListNode *nxt;
    ListNode *prev = nullptr;
    while (curr)
    {
        //std::cout << curr->val << std::endl;
        nxt = curr->next;
        curr->next = prev;
        prev = curr;
        
        //if(nxt->next)
        //nxt = nxt->next;
        
        curr = nxt;
    }
    head = prev;
    return head;
}
#include <iostream>
#include "ListNode.h"

using namespace std;

int main() {
    // Create a linked list with 5 nodes
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    cout << "Original linked list: ";
    ListNode *temp = head;
    while (temp != nullptr) {
        if (temp->next == nullptr) {
            cout << temp->val;
            break;
        }
        cout << temp->val << "->";
        temp = temp->next;
    }
    
    ListNode *reversed = reverseList(head);
    cout << endl << "Reversed linked list: ";
    // Print reversed list with -> symbols
    while (reversed != nullptr) {
        if (reversed->next == nullptr) {
            cout << reversed->val;
            break;
        }
        cout << reversed->val << "->";
        reversed = reversed->next;
    }
    cout << '\n';
    return 0;
}
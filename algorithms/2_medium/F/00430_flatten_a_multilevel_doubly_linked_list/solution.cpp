/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

class Solution {
public:
    Node* flatten(Node* head) {
        Node* curr = head;

        while (curr != nullptr) {
            if (curr->child != nullptr) {
                Node* next = curr->next;
                flatten(curr->child);
                curr->next = curr->child;
                curr->child = nullptr;
                curr->next->prev = curr;
                while (curr->next != nullptr) {
                    curr = curr->next;
                }

                if (next != nullptr) {
                    curr->next = next;
                    next->prev = curr;
                }
            }

            curr = curr->next;;
        }

        return head;
    }
};

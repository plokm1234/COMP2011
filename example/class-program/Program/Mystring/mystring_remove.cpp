#include "mystring.h"   /* File: mystring_remove.cpp */
// To remove the character c from the linked list.
// Do nothing if the character cannot be found.
void mystring::remove(char c)
{
    ll_cnode* previous = nullptr; // Point to previous ll_cnode
    ll_cnode* current = head;  // Point to current ll_cnode
    // STEP 1: Find the item to be removed
    while (current != nullptr && current->data != c)
    {
        previous = current;    // Advance both pointers
        current = current->next;
    }
    
    if (current != nullptr)       // Data is found
    {
        // STEP 2: Bypass the found item
        if (current == head)   // Special case: Remove the first item
            head = head->next;
        else
            previous->next = current->next;
        // STEP 3: Free up the memory of the removed item
        delete current; 
    }
}

#include "mystring.h"   /* File: mystring_destructor.cpp */

mystring::~mystring() 
{
    if (head == nullptr) // No need to do destruction for empty mystring
        return;
    
    ll_cnode* current;  // Point to current ll_cnode
    ll_cnode* next;     // Point to next ll_cnode
    
    // Go through the linked list and delete one node at a time
    for (current = head; current != nullptr; current = next)
    {
        next = current->next;
        delete current; // Free up the memory of each ll_cnode
    }
}

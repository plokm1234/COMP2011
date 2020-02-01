#include "mystring.h"   /* File: mystring_constructors.cpp */

mystring::mystring() { head = nullptr; } // Default constructor

mystring::mystring(char c) { head = new ll_cnode(c); }

mystring::mystring(const char s[]) 
{
    if (s[0] == NULL_CHAR) // Empty linked list due to empty C string
    {
        head = nullptr; return;
    }
    
    // First copy s[0] to the first node of mystring
    ll_cnode* p = head = new ll_cnode(s[0]); 

    // Add a new ll_cnode for each char in the char array s[]
    for (int j = 1; s[j] != NULL_CHAR; j++, p = p->next)
        p->next = new ll_cnode(s[j]); 
    p->next = nullptr;  // Set the last ll_cnode to point to NOTHING
}

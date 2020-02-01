#include <iostream>     /* File: ll_cnode.h */
using namespace std;
const char NULL_CHAR = '\0';

class ll_cnode
{
  public:
    char data;      // Single character node
    ll_cnode* next; // The link to the next character node

   // CONSTRUCTOR
    ll_cnode(char c = NULL_CHAR) { data = c; next = nullptr; }
};

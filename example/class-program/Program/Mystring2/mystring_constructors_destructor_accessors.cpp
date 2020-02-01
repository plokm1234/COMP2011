/* File: mystring_constructors_destructor_accessors.cpp */
#include "mystring.h"
// Constructors
mystring::mystring() { data[0] = NULL_CHAR; }
mystring::mystring(char c) { data[0] = c; data[1] = NULL_CHAR; }
mystring::mystring(const char s[]) 
{ 
    if (strlen(s) > MAX_STR_LEN)
    {
        cerr << "mystring::mystring --- Only a max. of "
             << MAX_STR_LEN << " characters are allowed!" << endl;
        exit(1);
    }
    strcpy(data, s); 
}
    
// Destructor
mystring::~mystring() { }

// ACCESSOR member functions
int mystring::length() const { return strlen(data); }
void mystring::print() const { cout << data << endl; }

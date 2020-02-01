#include "mystring.h"   /* File: mystring_remove.cpp */

void mystring::remove(char c)
{
    int j;
    int mystring_length = length();
    
    for (j = 0; j < mystring_length; j++)
    {
        if (data[j] == c)
            break;
    }
    
    if (j < mystring_length)    // c is found
    {
        for (; j < mystring_length; j++)
            data[j] = data[j+1];
    }
}

#include "mystring.h"   /* File: mystring_insert.cpp */

void mystring::insert(char c, unsigned n)
{   
    int length = strlen(data);
    if (length == MAX_STR_LEN)
    {
        cerr << "mystring::insert --- string is already full!" << endl;
        exit(1);
    }

    int insert_position = (n >= length) ? length : n;

    for (int j = length; j != insert_position; j--) 
        data[j] = data[j-1];
    
    data[insert_position] =  c;
    data[length+1] = NULL_CHAR;
}

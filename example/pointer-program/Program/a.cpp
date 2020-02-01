#include <iostream>     /* File: array-by-another-pointer.cpp */
using namespace std;	

int main()	
{
    int x[] = { 11, 22, 33, 44 };
    cout << &x << endl;
    cout << x << endl;
    cout << *x << endl;
    cout << *&x << endl;
    return 0;
}

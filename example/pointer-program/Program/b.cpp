#include <iostream>     /* File: nullptr.cpp */
using namespace std;	


int main()	
{
    int x[3] = { 1, 2, 3 };
    x = x + 1;

    for (int k = 0; k < 2; k++)
        cout << x[k] << endl;
    
    return 0;
}

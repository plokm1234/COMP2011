#include <iostream>     /* File : a.cpp */
using namespace std;	

int main()	
{
    int x = 666;
    char t = x;
    char y {6666};
    char z {x};

    const int NUM = 6;
    char w {NUM};

    cout << x << endl;
    cout << t << endl;
    cout << y << endl;
    cout << z << endl;
    cout << w << endl;

    return 0;
}


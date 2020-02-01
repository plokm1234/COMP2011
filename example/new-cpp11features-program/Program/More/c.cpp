#include <iostream>     /* File : a.cpp */
using namespace std;	

int main()	
{
    int x = 2;
    double t = x;
    double y {2};
    double z {x};

    const int NUM = 6;
    double w {NUM};

    cout << x << endl;
    cout << t << endl;
    cout << y << endl;
    cout << z << endl;
    cout << w << endl;

    return 0;
}


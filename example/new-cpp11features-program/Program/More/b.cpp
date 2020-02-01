#include <iostream>     /* File : b.cpp */
using namespace std;	

int main()	
{
    double x = 6.7;
    int t = 6.7;
    int y {6.7};
    int z {x};

    const double NUM = 6.7;
    int w {NUM};

    cout << x << endl;
    cout << t << endl;
    cout << y << endl;
    cout << z << endl;
    cout << w << endl;

    return 0;
}


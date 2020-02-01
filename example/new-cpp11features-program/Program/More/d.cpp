#include <iostream>     /* File : d.cpp */
#include <typeinfo> 
using namespace std;	

int main()	
{
    cout << "Part 1" << endl;
    double arr[3][2] = {1, 2, 3, 4, 5, 6};
    for (double (&b)[2]: arr)
        for (double c: b)
            cout << c << endl;

    
    cout << "Part 2" << endl;
    double x[3][2];
    for (double (&b)[2]: x)
        for (double &c: b)
            c = 8;

    for (double (&b)[2]: x)
        for (double c: b)
            cout << c << endl;

    cout << "Part 3" << endl;
    int y[3][2] = {1, 2, 3, 4, 5, 6};
    int (&p)[2] = y[1];

    for (int k = 0; k < 2; ++k)
        cout << p[k] << endl;
    cout << typeid(decltype(p)).name() << endl;

    cout << "Part 4" << endl;
    int (*q)[2] = &y[1];
    cout << (*q)[0] << endl;
    cout << (*q)[1] << endl;
    cout << typeid(decltype(q)).name() << endl;
            
    return 0;
}

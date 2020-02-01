#include <iostream>     /* File: complex-test2.cpp */
using namespace std;
#include "complex.h"

void f(Complex a) { a.print(); }   // Complex a  = x
void g(Complex* a) { a->print(); } // Complex* a = &x
void h(Complex& a) { a.print(); }  // Complex& a = x

int main()
{
    // Check the parameter passing methods
    Complex x(1, 1); f(x); g(&x); h(x);
    
    // Check the parameter returning methods
    Complex y(10, 10); cout << endl << endl;
    (x.add1(y)).print();           // Complex  temp = *this = x
    (x.add2(y))->print();          // Complex* temp =  this = &x
    (x.add3(y)).print();           // Complex& temp = *this = x

    cout << endl << endl;          // What is the output now?
    x.add1(y).add1(y).print(); x.print();
    x.add2(y)->add2(y)->print(); x.print();
    x.add3(y).add3(y).print(); x.print();
    return 0;
}

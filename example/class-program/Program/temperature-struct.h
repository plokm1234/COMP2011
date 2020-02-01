#include <iostream>     /* File: temperature-struct.h */
using namespace std;
const char KELVIN = 'K', CELSIUS = 'C', FAHRENHEIT = 'F';

struct temperature
{
    double degree;      // Internally it is always saved in Kelvin
    temperature();      // Default constructor
    temperature(double d, char s);
    double kelvin() const;      // Read temperature in Kelvin
    double celsius() const;     // Read temperature in Fahrenheit
    double fahrenheit() const;  // Read temperature in Celsius
    void set(double d, char s);
};

#include <iostream>     /* File: mystring.h */
#include <cstring>
#include <cstdlib>
using namespace std;
const int MAX_STR_LEN = 1024; const char NULL_CHAR = '\0';

class mystring
{
  private:
    char data[MAX_STR_LEN+1];

  public:
    // CONSTRUCTOR member functions
    mystring();              // Construct an emtry string
    mystring(char);          // Construct from a single char
    mystring(const char[]); // Construct from a C-string
    // DESTRUCTOR member function
    ~mystring();
    // ACCESSOR member functions: Again declared const
    int length() const;
    void print() const;
    // MUTATOR member functions
    void insert(char c, unsigned n); // Insert char c at position n
    void remove(char c);       // Delete the first occurrence of char c
};

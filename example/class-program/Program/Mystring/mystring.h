#include "ll_cnode.h"   /* File: mystring.h */

class mystring
{
  private:
    ll_cnode* head;

  public:
    // CONSTRUCTOR member functions
    mystring();         // Default constructor from an emtry string
    mystring(char);     // Construct from a single char
    mystring(const char[]); // Construct from a C-string

    // DESTRUCTOR member function
    ~mystring();
    
    // ACCESSOR member functions: declared const
    int length() const;
    void print() const;

    // MUTATOR member functions
    void insert(char c, unsigned n); // Insert char c at position n
    void remove(char c); // Delete the first occurrence of char c
};

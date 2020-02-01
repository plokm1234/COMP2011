#include <iostream>
using namespace std;

/*
 * Class definition written by the class developers
 *
 */

class Book
{
  private:
    char* title;
    char* author;
    int num_pages;

  public:

    Book(int n = 100)
    {
        title = author = nullptr;
        num_pages = n;
    }
    
    Book(const char t[], const char a[], int n = 5)
    {
        set(t, a, n);
    }
    
    void set(const char t[], const char a[], int n = 5)
    {
        title = new char [strlen(t)+1];
        strcpy(title, t);

        author = new char [strlen(a)+1];
        strcpy(author, a);

        num_pages = n;
    }

    ~Book()
    {
        cout << "deleting book title \"" << title << "\"" << endl;
        delete [ ] title;
        delete [ ] author;
    }
};


/*
 * Apps written by application programmers
 *
 */

void f()
{
    Book* p = new Book [3]; 
    Book y("love", "hkust", 1);

    p[0].set("book1", "author1", 1);
    p[1].set("book2", "author2", 2);
    p[2].set("book3", "author3", 3);

    delete [ ] p;
    return;
}

int main()
{
    Book x("war", "hitler", 1000);
    Book* z = new Book("hate", "hkust", 1);
    
    f();
    delete z;
    return 0;
}



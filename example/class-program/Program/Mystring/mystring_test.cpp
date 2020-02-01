#include "mystring.h" /* File: mystring_test.cpp */

int main() 
{
    mystring s1, s2('A'), s3("met");
    cout << "length of s1 = " << s1.length() << endl;
    cout << "length of s2 = " << s2.length() << endl;
    cout << "length of s3 = " << s3.length() << endl;

    cout << endl << "After inserting 'a' at position 2 to s3" << endl;
    s3.insert('a', 2); s3.print();
    cout << endl << "After removing 'e' from s3" << endl;
    s3.remove('e'); s3.print();
    cout << endl << "After removing 'm' from s3" << endl;
    s3.remove('m'); s3.print();
    cout << endl << "After inserting 'e' at position 9 to s3" << endl;
    s3.insert('e', 9); s3.print();
    cout << endl << "After removing 't' from s3" << endl;
    s3.remove('t'); s3.print();
    cout << endl << "After removing 'e' from s3" << endl;
    s3.remove('e'); s3.print();
    cout << endl << "After removing 'a' from s3" << endl;
    s3.remove('a'); s3.print();

    cout << endl << "After removing 'z' from s3" << endl;
    s3.remove('z'); s3.print();
    cout << endl << "After inserting 'h' at position 9 to s3" << endl;
    s3.insert('h', 9); s3.print();
    cout << endl << "After inserting 'o' at position 0 to s3" << endl;
    s3.insert('o', 0); s3.print();
    return 0;
}

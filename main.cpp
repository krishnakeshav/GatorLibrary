#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include "gator_library.hpp"

#include "gl_input.cpp"

using namespace std;

int main(int argc, char** argv)
{
    cout << "Hello World!" << endl;
    //GatorLibrary library;
    // library.InsertBook(1, "Book1", "Author1", "Yes");
    // library.PrintBook(1);
    // library.InsertBook(2, "Book2", "Author2", "Yes");
    // library.InsertBook(3, "Book3", "Author3", "Yes");
    // cout << "added" << endl;
    // for (size_t i = 1; i <= 3; i++)
    // {
    //     library.PrintBook(i);
    // }
    // library.BorrowBook(1, 1, 1);
    // library.BorrowBook(2, 1, 2);
    // library.PrintBook(1);
    // library.ReturnBook(1, 1);
    // library.ReturnBook(1, 4);
    // library.PrintBook(1);
    // library.ReturnBook(10, 1);
    // library.ReturnBook(2, 1);
    // library.PrintBook(1);
    // library.BorrowBook(3, 1, 3);
    // library.DeleteBook(3);
    // library.PrintBook(1);
    // library.PrintBook(2);
    // library.BorrowBook(1, 1, 1);
    // library.BorrowBook(2, 1, 2);
    // library.BorrowBook(3, 1, 3);
    // library.ReturnBook(1, 1);
    // library.BorrowBook(3, 1, 1);
    // library.DeleteBook(1);
    // library.InsertBook(1, "Book1", "Author1", "Yes");
    // library.PrintBook(1);
    // library.BorrowBook(101, 1, 1);
    // library.InsertBook(2, "Book2", "Author2", "Yes");
    // library.BorrowBook(102, 1, 2);
    // library.PrintBooks(1, 2);
    // library.ReturnBook(101, 1);
    gl_input gl;
    gl.runwith_file(argv[1]);

    return 0;
}

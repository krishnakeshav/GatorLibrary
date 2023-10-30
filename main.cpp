#include <iostream>

#include "GatorLibrary.hpp"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    GatorLibrary library;
    library.InsertBook(1, "Book1", "Author1", "Yes");
    library.PrintBook(1);
    library.InsertBook(2, "Book2", "Author2", "Yes");
    library.InsertBook(3, "Book3", "Author3", "Yes");
    cout << "added" << endl;
    for (size_t i = 1; i <= 3; i++)
    {
        library.PrintBook(i);
    }
    cout << "root ->" << library.rbtBooks.root->value.BookId << endl;
    library.BorrowBook(1, 1, 1);
    library.BorrowBook(2, 1, 2);
    library.PrintBook(1);
    library.ReturnBook(1, 1);
    library.ReturnBook(1, 4);
    library.PrintBook(1);
    library.ReturnBook(10, 1);
    library.ReturnBook(2, 1);
    library.PrintBook(1);

    return 0;
}
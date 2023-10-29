#include <iostream>

#include "GatorLibrary.hpp"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    GatorLibrary library;
    library.InsertBook(1, "Book1", "Author1", false, 0);
    library.InsertBook(2, "Book2", "Author2", false, 0);
    cout << "added" << endl;
    for (size_t i = 1; i <= 2; i++)
    {
        library.PrintBook(i);
    }

    return 0;
}
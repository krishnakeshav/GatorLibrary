#include "GatorLibrary.hpp"

using namespace std;

void GatorLibrary::PrintBook(int bookID)
{
    rbtnode* bookToPrint = rbtBooks.find(bookID);
    if (bookToPrint == nullptr)
    {
        cout << "BookID " << bookID << " not found in library" << endl;
        return;
    }
    bookToPrint->value.PrintBook();
}

void GatorLibrary::PrintBooks(int bookID1, int bookID2)
{
    for (size_t bookId = bookID1; bookId <= bookID2; bookId++)
    {
        PrintBook(bookId);
    }
}

void GatorLibrary::InsertBook(int bookID, string bookName, string authorName, bool availabilityStatus, int borrowedBy)
{
    book newBook(bookID, bookName, authorName);
    rbtBooks.add(newBook);
}

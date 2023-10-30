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

void GatorLibrary::InsertBook(int bookID, string bookName, string authorName, string availabilityStatus)
{
    book newBook(bookID, bookName, authorName, availabilityStatus);
    rbtBooks.add(newBook);
}

void GatorLibrary::BorrowBook(int patronID, int bookID, int patronPriority)
{
    rbtnode* bookToBorrow = rbtBooks.find(bookID);
    if (bookToBorrow == nullptr)
    {
        cout << "BookID " << bookID << " not found in library" << endl;
        return;
    }
    if (bookToBorrow->value.BorrowedBy == patronID)
    {
        cout << "BookID " << bookID << " is already borrowed by PatronID " << patronID << endl;
        return;
    }
    if (bookToBorrow->value.AvailabilityStatus == YES)
    {
        bookToBorrow->value.AvailabilityStatus = NO;
        bookToBorrow->value.BorrowedBy = patronID;
    }
    else
    {
        reservation newReservation(patronID, patronPriority);
        bookToBorrow->value.AddReservation(newReservation);
    }
}

void GatorLibrary::ReturnBook(int patronID, int bookID)
{
    rbtnode* bookToReturn = rbtBooks.find(bookID);
    if (bookToReturn == nullptr)
    {
        cout << "BookID " << bookID << " not found in library" << endl;
        return;
    }
    if (bookToReturn->value.AvailabilityStatus == NO)
    {
        bookToReturn->value.AvailabilityStatus = YES;
        bookToReturn->value.BorrowedBy = 0;
        if (!bookToReturn->value.ReservationHeap.empty())
        {
            reservation nextReservation = bookToReturn->value.ReservationHeap.top();
            bookToReturn->value.ReservationHeap.pop();
            BorrowBook(nextReservation.PatronId, bookID, nextReservation.PriorityNumber);
        }
    }
    else
    {
        cout << "BookID " << bookID << " is not borrowed" << endl;
    }
}
